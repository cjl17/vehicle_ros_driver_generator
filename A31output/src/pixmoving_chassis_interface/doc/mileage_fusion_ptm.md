## 小计里程 `ptm` 融合说明

本文档说明 `pixmoving_chassis_interface` 中新增的 **1m 级小计里程 `ptm` 融合发布** 逻辑，重点回答以下问题：

- 为什么原有 `ptm` 精度只有 10m 左右
- 当前版本如何实现 `NDT -> GNSS -> 底盘车速` 三层回退
- `ptm` 的上电语义、切源规则和参数如何理解

---

## 1. 背景

原始实现中，`/app/cloud_control_platform/vehicle_info.ptm` 直接来自底盘反馈：

- 底盘消息：`/pix_robobus/va_chassis_odo_fb`
- 字段：`vcu_vehicle_trip`
- 单位：`km`
- 精度：`0.01 km`

也就是说，原始小计里程本质上只有 **10m 级** 精度。

这会导致：

- 接管里程、任务统计等业务侧无法拿到更细的里程变化
- 车辆低速、短距离移动时，`ptm` 更新不够平滑

因此本次改动的目标是：

- 不改对外协议
- 保持 `ptm` 含义不变
- 将 `ptm` 的计算来源从“仅底盘 trip”升级为“多源融合累计”

---

## 2. 对外语义保持不变

本次改动 **没有修改 `VehicleInfo.msg` 协议语义**。

- `tm`
  - 仍表示总里程
  - 继续由底盘总里程直接提供
- `ptm`
  - 仍表示“小计里程 / 本次上电累计里程”
  - 单位仍为 `m`
  - 对外 topic 仍为：
    - `/app/cloud_control_platform/vehicle_info`

因此，下游使用 `ptm` 的模块不需要改订阅协议，只会感知到它的精度和连续性提升。

---

## 3. 当前实现总览

当前版本新增了一套独立于任务距离 `travel_distance_` 的里程融合状态：

- `fused_power_on_mileage_m_`
  - 当前融合后的小计里程，单位 `m`
- `MileageSource`
  - 当前使用的里程源
  - 枚举值：
    - `NONE`
    - `NDT`
    - `GNSS`
    - `CHASSIS_SPEED`

融合主入口：

- `updateFusedPowerOnMileage()`

该函数会在定时器发布前调用，完成：

1. 上电周期同步
2. 当前源选择
3. 增量累计
4. `vehicle_info_msg_.ptm` 回写

---

## 4. 三层里程源优先级

当前优先级固定为：

1. `NDT`
2. `GNSS`
3. `CHASSIS_SPEED`

### 4.1 NDT 层

使用：

- `/localization/pose_twist_fusion_filter/pose`
- `/localization/pose_estimator/nearest_voxel_transformation_likelihood`

累计方式：

- 取相邻 `PoseStamped`
- 计算平面距离 `sqrt(dx^2 + dy^2)`
- 通过后累加到 `fused_power_on_mileage_m_`

可靠性判定：

- pose 必须存在
- pose 新鲜度不能超时
- `nearest_voxel_transformation_likelihood` 必须在阈值内

注意：

- 当前实现把 **数值越小视为越可靠**
- 默认阈值参考了 NDT 参数默认值：`2.3`

### 4.2 GNSS 层

当 NDT 不可靠时，回退到：

- `/sensing/gnss/fix`

累计方式：

- 使用相邻两帧 `NavSatFix`
- 通过 haversine 公式计算地表距离
- 通过后累加到 `fused_power_on_mileage_m_`

可靠性判定：

- `status.status >= STATUS_FIX`
- 经纬高不能全为 0
- 数据新鲜度不能超时
- 需要连续若干帧有效后才开始累计

### 4.3 底盘车速层

当 NDT 和 GNSS 都不可靠时，回退到底盘速度积分：

- 数据来源：`VaDriveStaFb.vcu_chassis_speed_fb`

累计方式：

- `delta_m = speed_mps * delta_time_s`

可靠性判定：

- 最近收到过底盘速度
- 数据未超时
- 速度值有效

---

## 5. 切源规则

切源由 `chooseMileageSource()` 统一完成：

- `NDT` 可用时，一律优先 `NDT`
- 否则，如果 `GNSS` 可用，则切到 `GNSS`
- 否则，如果底盘速度可用，则切到 `CHASSIS_SPEED`
- 否则为 `NONE`

### 5.1 为什么只做“增量累计”

每一层数据源都只负责提供 **增量 `delta_m`**，不会直接覆盖总值。

这样做的目的：

- 避免切换数据源时 `ptm` 跳变
- 避免 NDT / GNSS 直接把历史累计值拉回去

### 5.2 切源时做什么

当 source 变化时：

1. 只重置目标 source 的锚点
2. 不清空 `fused_power_on_mileage_m_`
3. 下一帧从新的锚点继续累计

这样可以保证：

- `ptm` 单调递增
- 切源不会突然归零或跳大值

---

## 6. 防漂移 / 防跳变策略

为了避免 GNSS 漂移、NDT 抖动或时间戳异常导致里程乱跳，当前实现加入了统一门控：

### 6.1 静止门控

如果底盘速度低于阈值：

- 默认 `0.2 m/s`

则：

- NDT / GNSS 的位移增量会被严格限制
- 避免车辆静止时因为定位漂移导致 `ptm` 缓慢增长

### 6.2 跳变门控

单帧位移过大时直接丢弃：

- `NDT` 默认阈值：`5.0 m`
- `GNSS` 默认阈值：`20.0 m`

### 6.3 速度一致性门控

如果底盘速度可用，则还会比较：

- 实际位移 `delta_m`
- 速度积分预测上限 `speed * dt * max_delta_ratio + margin`

默认：

- `max_delta_ratio = 2.5`

如果位移明显大于速度预测范围，则认为是异常跳点，不计入里程。

---

## 7. 上电语义与重启恢复

`ptm` 的业务语义仍然是：

- **本次上电累计里程**

但节点本身支持 respawn，如果简单地“节点重启即清零”，会导致：

- 车辆未下电时，`ptm` 断崖式回到 0

因此当前实现增加了两层处理：

### 7.1 snapshot 恢复

节点启动时会尝试从 snapshot 恢复：

- `tm`
- `ptm`
- 同步恢复 `fused_power_on_mileage_m_`

这样，单纯节点重启时不会立即丢掉当前上电里程。

### 7.2 raw trip 同步

底盘原始 `trip` 仍被保留为：

- 上电周期参考值
- 启动后的对齐依据

逻辑如下：

- 如果启动后发现底盘 raw trip 明显小于 snapshot 中的融合 `ptm`
  - 判定为车辆已经重新上电
  - 将融合 `ptm` 重置到 raw trip
- 如果运行中 raw trip 出现明显回落
  - 判定为新的上电周期
  - 重新开始累计

这保证了：

- 车辆真下电再上电时，`ptm` 仍然能从 0 附近重新开始
- 只是节点 respawn 时，`ptm` 不会误清零

---

## 8. 与现有任务距离逻辑的关系

当前版本**明确没有复用** `travel_distance_`。

原因：

- `travel_distance_` 是任务距离语义
- 新任务或重规划时可能重置
- 不适合拿来表达“本次上电累计里程”

因此：

- `travel_distance_` 继续只服务任务/站点距离逻辑
- `fused_power_on_mileage_m_` 只服务 `VehicleInfo.ptm`

二者互不耦合

---

## 9. 主要改动文件

### 9.1 新增文件

- `src/pixmoving_mileage.cpp`
  - 里程融合核心实现

### 9.2 修改文件

- `include/pixmoving_chassis_interface/pixmoving_chassis_interface.hpp`
  - 新增融合状态、参数、函数声明
- `src/pixmoving_chassis_interface.cpp`
  - 新增参数读取、snapshot 恢复、定时器接入融合逻辑
- `src/pixmoving_chassis.cpp`
  - 缓存底盘速度和 raw trip
  - 启用融合时不再直接用底盘 trip 覆盖 `ptm`
- `src/pixmoving_sensor.cpp`
  - 缓存有效 GNSS fix
- `src/pixmoving_autoware.cpp`
  - 缓存 NDT 质量值
- `config/chassis_interface.yml`
  - 新增里程融合参数
- `CMakeLists.txt`
  - 将 `pixmoving_mileage.cpp` 加入编译

---

## 10. 主要参数

当前版本新增参数如下：

- `enable_fused_ptm`
  - 是否启用融合 `ptm`
- `ndt_pos_q_threshold`
  - NDT 可靠性阈值
- `ndt_timeout_sec`
  - NDT 数据超时阈值
- `gnss_timeout_sec`
  - GNSS 数据超时阈值
- `chassis_speed_timeout_sec`
  - 底盘速度数据超时阈值
- `standstill_speed_threshold_mps`
  - 静止速度阈值
- `ndt_jump_reject_threshold_m`
  - NDT 单帧跳变丢弃阈值
- `gnss_jump_reject_threshold_m`
  - GNSS 单帧跳变丢弃阈值
- `max_delta_ratio`
  - 位移和速度预测的一致性放宽倍数
- `raw_trip_sync_threshold_m`
  - raw trip 与融合里程的同步/重置判定阈值
- `gnss_warmup_frames`
  - GNSS 连续有效预热帧数

### 10.1 参数调节方向

下面说明每个参数“调大”和“调小”的影响，便于实车联调时快速判断。

#### `enable_fused_ptm`

- `true`
  - 启用 `NDT -> GNSS -> 底盘车速` 融合
- `false`
  - 完全回退到底盘原始 `trip`
  - 适合排查“问题到底来自融合还是来自原始底盘数据”

#### `ndt_pos_q_threshold`

当前实现中，**数值越小表示 NDT 越可靠**，因此：

- 调大
  - 更容易判定 NDT 可用
  - 更少切到 GNSS / 底盘速度
  - 但有可能把质量一般的 NDT 也放进来，增加漂移风险
- 调小
  - 更严格
  - 更容易切到 GNSS / 底盘速度
  - 适合 NDT 抖动、静止漂移明显时使用

#### `ndt_timeout_sec`

- 调大
  - 对短时 NDT 断流更宽容
  - 不容易频繁切源
  - 但可能拿到过期 pose
- 调小
  - 更快放弃 NDT
  - 切源更积极
  - 但容易在边界场景频繁切到 GNSS

#### `gnss_timeout_sec`

- 调大
  - 对短时 GNSS 抖动更宽容
  - 不容易从 GNSS 再掉到底盘速度
- 调小
  - 对 GNSS 新鲜度要求更高
  - 更容易切到底盘速度

#### `chassis_speed_timeout_sec`

- 调大
  - 更容易继续使用底盘速度积分
  - 在速度消息偶发丢帧时更稳定
- 调小
  - 更严格依赖实时速度
  - 可避免用过期速度继续积分

#### `standstill_speed_threshold_mps`

- 调大
  - 更强地抑制静止漂移
  - 适合停车时 `ptm` 还在慢慢涨的场景
  - 但低速蠕行时可能不计里程
- 调小
  - 对低速移动更敏感
  - 但静止时更容易累计漂移

#### `ndt_jump_reject_threshold_m`

- 调大
  - 更容易接受 NDT 单帧大位移
  - 对高速场景更宽松
  - 但可能放进异常跳点
- 调小
  - 更严格地抑制 NDT 跳点
  - 但可能丢掉真实快速位移

#### `gnss_jump_reject_threshold_m`

- 调大
  - 更容易接受 GNSS 单帧变化
  - 切到 GNSS 后累计更连续
  - 但更容易把 GNSS 跳点记进 `ptm`
- 调小
  - 更严格
  - 适合 GNSS 漂移、突然跳点明显的车

#### `max_delta_ratio`

- 调大
  - 放宽“定位位移 vs 速度积分预测”的一致性检查
  - 不容易误杀真实位移
  - 但异常跳点更容易漏过
- 调小
  - 更严格校验
  - 更能抑制异常点
  - 但可能在加减速或速度抖动时误丢正常位移

#### `raw_trip_sync_threshold_m`

- 调大
  - 更不容易因为 raw trip 波动而触发“重新上电/重置”判定
  - 适合底盘原始 trip 抖动较大的情况
- 调小
  - 更敏感
  - 更容易识别真实下电重上电
  - 但也更容易误判重置

#### `gnss_warmup_frames`

- 调大
  - GNSS 切入更稳
  - 不容易刚切进 GNSS 就被异常点影响
  - 但 NDT 失效后切到 GNSS 会更慢
- 调小
  - GNSS 切入更快
  - 但更容易把 GNSS 初始不稳定帧记入里程

### 10.2 建议调参顺序

建议按下面顺序调，而不是一次同时改很多参数：

1. 先确认 `NDT` 能否稳定工作
   - 先看 source 是否长期停在 `NDT`
   - 如果总是过早切走，优先调 `ndt_pos_q_threshold`、`ndt_timeout_sec`
2. 再压静止漂移
   - 停车观察 `ptm` 是否还在增长
   - 优先调 `standstill_speed_threshold_mps`
   - 再看是否需要调小 `ndt_jump_reject_threshold_m` / `gnss_jump_reject_threshold_m`
3. 再调 GNSS 接管体验
   - NDT 失效后观察切到 GNSS 是否太慢或太抖
   - 重点调 `gnss_warmup_frames`、`gnss_timeout_sec`
4. 最后调上电同步
   - 验证节点 respawn、车辆真下电/上电
   - 根据表现调 `raw_trip_sync_threshold_m`

### 10.3 常见现象与建议

#### 现象 1：车辆静止时 `ptm` 仍在慢慢涨

优先尝试：

- 调大 `standstill_speed_threshold_mps`
- 调小 `ndt_pos_q_threshold`
- 调小 `gnss_jump_reject_threshold_m`
- 调小 `max_delta_ratio`

说明：

- 这通常表示静止时 NDT 或 GNSS 漂移被当成真实位移记入了累计里程

#### 现象 2：明明 NDT 正常，但 source 经常掉到 GNSS

优先尝试：

- 调大 `ndt_pos_q_threshold`
- 调大 `ndt_timeout_sec`

说明：

- 这通常表示 NDT 可靠性门槛过严，或者 NDT 数据时间边界过紧

#### 现象 3：NDT 失效后，切到 GNSS 太慢

优先尝试：

- 调小 `gnss_warmup_frames`
- 调大 `gnss_timeout_sec`

说明：

- 这通常表示 GNSS 预热帧数偏大，或者 GNSS 被判定为“新鲜度不足”

#### 现象 4：切到 GNSS 后 `ptm` 会突然跳一大段

优先尝试：

- 调小 `gnss_jump_reject_threshold_m`
- 调小 `max_delta_ratio`
- 适当调大 `gnss_warmup_frames`

说明：

- 这通常表示 GNSS 初始锚点附近存在异常跳点，或者切入过快

#### 现象 5：低速蠕行时里程记少了

优先尝试：

- 调小 `standstill_speed_threshold_mps`

说明：

- 这通常表示静止门槛过高，把低速真实移动也当成静止抑制掉了

#### 现象 6：车辆重启上电后，`ptm` 没有从 0 附近重新开始

优先尝试：

- 调小 `raw_trip_sync_threshold_m`

说明：

- 这通常表示“raw trip 回落”判定太宽松，没有及时识别新上电周期

#### 现象 7：只是节点 respawn，`ptm` 却被误清零

优先尝试：

- 调大 `raw_trip_sync_threshold_m`

说明：

- 这通常表示启动时 snapshot 与 raw trip 的差值被过于敏感地判成“新上电”

---

## 11. 当前限制

当前版本仍有以下限制：

1. GNSS 层只使用了 `/sensing/gnss/fix`
   - 还没有接入更强的组合导航状态门控
2. GNSS 距离采用 haversine
   - 对短距离小计里程已足够
   - 但不是更完整的 ENU / UTM 融合方案
3. NDT 可靠性只使用了 `nearest_voxel_transformation_likelihood`
   - 未结合更多定位状态做综合判定

因此这版更适合作为：

- 第一阶段可运行版本
- 先解决 `ptm` 精度不足问题
- 后续再按实车数据继续收阈值

---

## 12. 联调建议

建议重点观察以下内容：

- `Mileage source switched: ...`
  - 确认是否按预期在 `NDT / GNSS / CHASSIS_SPEED` 间切换
- `VehicleInfo.ptm`
  - 是否保持单调递增
- 静止时 `ptm`
  - 是否基本不增长
- NDT 失效、GNSS 恢复、底盘速度回退时
  - 是否无明显跳变
- 车辆重启上电后
  - `ptm` 是否回到 0 附近重新开始

建议实车验证至少覆盖：

1. 正常 NDT 场景
2. 人工屏蔽 NDT、保留 GNSS
3. 同时屏蔽 NDT + GNSS，仅留底盘速度
4. 节点 respawn
5. 车辆真实下电再上电

---

## 13. 结论

当前版本已经将 `ptm` 从“底盘 10m 级小计里程”升级为：

- `NDT -> GNSS -> 底盘车速` 三层回退
- 面向上电周期的独立融合累计
- 保持原协议不变

这版的重点不是“做最复杂的定位融合”，而是：

- 先把 `ptm` 的可用性、连续性和精度提升起来
- 给后续接管里程、统计里程等业务提供更靠谱的基础量
