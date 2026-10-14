## 任务语义与重规划说明

本文档说明 `pixmoving_chassis_interface` 中新增的“任务语义锁存”逻辑，重点回答以下问题：

- 为什么运行中不断收到同目标 `goal/route` 时，不能直接把当前 route 起点当成任务起点
- 当前版本如何区分“新任务”和“同任务重规划”
- 这套逻辑如何和驾驶模式状态机联动

---

## 1. 背景问题

在固定线路运营场景中，车辆运行过程中会不断收到新的 `LaneletRoute`。

如果每次收到 route 都直接把：

- `route.start_pose` 推断出的站点当成任务起点
- `route.goal_pose` 推断出的站点当成任务终点

那么原始任务：

```text
A -> B -> C -> D -> E -> F
```

在车辆已经跑到 `C / D` 区间时，一旦又收到同样目标站 `F` 的 route，就会被错误地展示成：

```text
C -> F
```

而业务真正想展示的仍然是：

```text
A -> F
```

---

## 2. 当前业务规则

当前版本采用如下规则：

1. 运行中，如果新来的 route 对应的目标站还是同一个目标站，则一律当作“重规划”。
2. 只有目标站发生变化时，才当作“新任务”。
3. 如果上一任务已经结束，则下一次即使目标站相同，也当作“新任务”。

这里的“结束”当前至少包括：

- `ARRIVED_GOAL`
- 状态机进入 `AUTO_DONE_NORMAL`
- 状态机进入 `AUTO_DONE_NEAR`
- 状态机进入 `AUTO_CANCEL_TAKEOVER`

> 注意：在当前输入条件下，系统并没有 `task_id`，因此这里的“新任务”不是云端任务语义上的绝对真值，而是车端约定的业务规则。

---

## 3. 设计原则

为了避免“route 拓扑语义”和“任务展示语义”互相覆盖，当前实现做了职责拆分：

- `goal`：
  - 只表示“有新的规划意图到来”
  - 不直接改变展示站点
- `route + route station service`：
  - 负责推断这条规划对应的当前站和目标站
- `task semantic context`：
  - 负责保存“当前任务真正的起点站/目标站”
  - 只有在判定为“新任务”时才更新
- `drive mode state machine`：
  - 只消费“是否发生了新任务切换”这一事件
  - 不再自行根据 `goal` 距离猜测是不是新任务

---

## 4. 核心数据结构

本次改动在节点内部新增了一组任务语义相关成员：

- `task_semantic_mutex_`
  - 保护任务语义上下文，避免 `goal`、`route`、状态机回调并发读写
- `has_task_semantic_`
  - 是否已经有锁存的任务语义
- `task_terminal_`
  - 当前锁存任务是否已经进入终态
- `pending_new_task_event_`
  - 是否需要向驾驶模式状态机发送一次 `NewTaskReceived`
- `semantic_origin_station_index_`
  - 当前任务锁存的起点站（0-based yaml index）
- `semantic_target_station_index_`
  - 当前任务锁存的目标站（0-based yaml index）

同时保留原有：

- `task_station_info_temp_`

但其用途调整为：

- 存放“当前已锁存任务”的展示缓存
- 不再用于任务语义判定

---

## 5. 新任务 / 重规划判定逻辑

判定集中在 `onLaneletRoute()` 中完成。

### 5.1 判定输入

优先使用 route station service 的推断结果：

- `current_station_index`
- `target_station_index`

若服务失败，再回退到本地 pose 匹配。

### 5.2 判定规则

对于一条新的 route，如果推断出目标站为 `route_target_station_index`，则：

```cpp
if (!has_task_semantic_ || task_terminal_) {
  // 新任务
} else if (route_target_station_index != semantic_target_station_index_) {
  // 新任务
} else {
  // 重规划
}
```

也就是说：

- 没有历史任务语义：新任务
- 上一任务已结束：新任务
- 目标站变了：新任务
- 其余全部：重规划

---

## 6. 新任务时会发生什么

当 route 被判定为“新任务”时：

1. 锁存新的任务语义：
   - `semantic_origin_station_index_ = inferred current station`
   - `semantic_target_station_index_ = inferred target station`
2. 更新 `task_station_info_temp_`
3. 重置：
   - `travel_distance_ = 0`
   - `plan_status_ = true`
4. 重新计算整条任务的总长度：
   - `task_distance = route_length`
   - `target_distance = route_length`
5. 如果旧任务还处于可取消状态：
   - 置 `pending_new_task_event_ = true`

这里“可取消状态”当前定义为：

- `AUTO_EXECUTING`
- `AUTO_TAKEOVER_MANUAL`
- `AUTO_TAKEOVER_BRAKE`

---

## 7. 重规划时会发生什么

当 route 被判定为“重规划”时：

1. 不修改：
   - `semantic_origin_station_index_`
   - `semantic_target_station_index_`
   - `task_station_info_temp_`
2. 展示继续使用锁存的任务起终点
3. 不重置 `travel_distance_`
4. 不重置 `task_distance`
5. 只更新：
   - `target_distance`
   - `estimate_time`
6. 不向状态机发送 `NewTaskReceived`

这样一来，即使车辆已经从 `A` 跑到 `C`，只要目标站仍然是 `F`，展示仍然保持为 `A -> F`。

---

## 8. 状态机联动方式

### 8.1 旧问题

原先 `onAutowareStateWithStateMachine()` 中还保留了一套旧逻辑：

- 比较 `current_target_station_` 和 `last_current_target_station_` 的几何距离
- 距离大于 5 米就当成“新任务”

这套逻辑的问题是：

- 只看 `goal pose`
- 不看目标站语义
- 可能和 `pixmoving_task.cpp` 的任务判定打架

### 8.2 新方案

当前版本把“新任务事件”变成显式输入：

- `pixmoving_task.cpp`
  - 负责决定是否需要切换任务
- `pixmoving_autoware_state_machine.cpp`
  - 只读取 `pending_new_task_event_`
  - 将其写入 `DriveModeContext::new_task_received`
- `DriveModeManager`
  - 真正把 `new_task_received` 转成 `DriveModeEvents::NewTaskReceived`

状态机新增/启用了这些迁移：

- `AutoExecuting + NewTaskReceived -> AutoCancelNewTask`
- `AutoTakeoverManual + NewTaskReceived -> AutoCancelNewTask`
- `AutoTakeoverBrake + NewTaskReceived -> AutoCancelNewTask`

这样驾驶模式状态机只负责“接到明确新任务后如何切模式”，不再负责猜测。

---

## 9. 关键实现位置

### 9.1 任务语义与 route 判定

- `src/pixmoving_task.cpp`
  - `populateStationMsgFromYamlIndex()`
  - `latchTaskSemantic()`
  - `applyLatchedTaskStationsToDisplay()`
  - `shouldTreatAsNewTask()`
  - `markTaskTerminal()`
  - `onLaneletRoute()`

### 9.2 状态机输入

- `include/pixmoving_chassis_interface/drive_mode_state_machine.hpp`
  - `DriveModeContext::new_task_received`
  - `NewTaskReceived` 对应的状态迁移

- `src/pixmoving_drive_mode.cpp`
  - `DriveModeManager::update()`
  - 将 `new_task_received` 转成 `DriveModeEvents::NewTaskReceived`

### 9.3 状态机消费与终态标记

- `src/pixmoving_autoware_state_machine.cpp`
  - 读取 `pending_new_task_event_`
  - 在任务完成时调用 `markTaskTerminal()`

---

## 10. 现场 FAE 调试话题

为了方便现场快速判断“当前到底是新任务还是重规划”，当前版本新增了一个独立调试话题：

```text
/app/display/debug/task_semantic_status
```

消息类型：

```text
pixmoving_hmi_msgs/msg/TaskSemanticStatus
```

这个话题不会替代原有的：

```text
/app/display/current_station_info
```

而是专门给调试和现场排障使用。

### 10.1 这个话题会直接展示什么

- `lifecycle`
  - 当前任务生命周期：`idle / active / terminal`
- `last_route_decision`
  - 最近一条 route 被判定成：
    - `new_task`
    - `replan`
    - `inference_failed`
- `last_station_source`
  - 最近一次站点推断来自：
    - `route_station_service`
    - `pose_matching_fallback`
- `semantic_origin_station_*`
  - 当前锁存的任务起点站
- `semantic_target_station_*`
  - 当前锁存的任务目标站
- `inferred_current_station_*`
  - 最近一条 route 推断出来的当前站
- `inferred_target_station_*`
  - 最近一条 route 推断出来的目标站
- `last_triggered_new_task_event`
  - 最近一次 route 是否真的向状态机触发了 `NewTaskReceived`
- `drive_mode`
  - 当前驾驶模式
- `autoware_state`
  - 当前 Autoware 状态
- `task_distance`
  - 当前锁存任务总距离
- `target_distance`
  - 当前剩余距离
- `summary`
  - 面向现场的汇总字符串

### 10.2 现场排查建议

### 10.2 字段对照表

| 字段 | 典型值 | 代表含义 | 现场怎么看 |
|------|--------|----------|------------|
| `lifecycle` | `idle` | 当前没有有效任务语义 | 车辆还没接到任务，或任务语义尚未建立 |
| `lifecycle` | `active` | 当前有正在生效的任务语义 | 当前展示的起终点就是锁存任务 |
| `lifecycle` | `terminal` | 上一任务已经结束 | 下一次即使目标站相同，也会按新任务处理 |
| `last_route_decision` | `new_task` | 最近一条 route 被判成新任务 | 会锁存新的起终点，必要时触发状态机切任务 |
| `last_route_decision` | `replan` | 最近一条 route 被判成重规划 | 不改任务起点，只更新剩余距离和时间 |
| `last_route_decision` | `inference_failed` | 最近一次 route/pose 推断失败 | 先检查 route station service、站点文件和 pose 匹配 |
| `last_station_source` | `route_station_service` | 站点来自 route 推断服务 | 这是优先路径，通常更可信 |
| `last_station_source` | `pose_matching_fallback` | 服务失败后回退到本地 pose 匹配 | 现场如果频繁出现，优先查服务或地图数据 |
| `has_task_semantic` | `true` | 已经锁存过任务语义 | 系统知道“当前任务真正的起终点” |
| `task_terminal` | `true` | 当前锁存任务已进入终态 | 说明上一任务已经完成/退出 |
| `last_triggered_new_task_event` | `true` | 最近一次 route 确实向状态机发了 `NewTaskReceived` | 说明这次不是单纯重规划，而是触发了任务切换流程 |
| `semantic_origin_station_index/name` | `A` 站 | 当前锁存任务起点 | FAE 判断“展示为什么还是 A”时先看它 |
| `semantic_target_station_index/name` | `F` 站 | 当前锁存任务目标站 | 用它判断当前任务本来是去哪里 |
| `inferred_current_station_index/name` | `C` 站 | 最近一条 route 推断出的当前站 | 用来对比车辆 route 当前落点 |
| `inferred_target_station_index/name` | `F` 站 | 最近一条 route 推断出的目标站 | 用来判断这次是同目标重规划还是换目标新任务 |
| `drive_mode` | `5/6/7/8/9/11` | 当前驾驶模式枚举值 | 结合模式表看是否在执行、接管、附近完成或新任务取消 |
| `autoware_state` | `DRIVING / WAITING_FOR_ENGAGE / ARRIVED_GOAL` | 当前 Autoware 高层状态 | 用来判断系统当前处于执行、接管还是到站阶段 |
| `task_distance` | 例如 `1200` | 当前锁存任务总距离 | 新任务时会更新，重规划时保持不变 |
| `target_distance` | 例如 `180` | 当前剩余距离 | 会随着执行/接管继续变化 |
| `near_done_active` | `true` | 当前已经进入 `AUTO_DONE_NEAR` | 说明系统已经判定为“附近完成” |
| `near_done_condition_met` | `true` | 当前满足“附近完成触发条件” | 条件是接管中、低速、剩余距离小于等于 50m |
| `near_done_hold_until_sec` | 时间戳 | 附近完成保持到的系统时间 | 用于判断什么时候会退出附近完成 |
| `near_done_remaining_sec` | 例如 `2.4` | 距离退出附近完成还剩多少秒 | 现场最直观的倒计时字段 |
| `summary` | 一整段字符串 | 面向现场的快速摘要 | 不想逐字段看时直接看这一行 |

### 10.3 现场排查建议

如果现场遇到“为什么没有切新任务”或者“为什么中途没把起点刷成当前位置”，可以直接看：

1. `last_route_decision`
2. `semantic_origin_station_name`
3. `semantic_target_station_name`
4. `inferred_current_station_name`
5. `inferred_target_station_name`
6. `last_triggered_new_task_event`

常见判断方式：

- 如果 `last_route_decision = replan`
  - 说明系统认为这次仍然是同一目标站的重规划
- 如果 `semantic_origin_station_name = A`
  - `inferred_current_station_name = C`
  - 说明车辆当前 route 已经落到 `C` 附近，但任务展示仍然锁存在 `A -> ...`
- 如果 `last_triggered_new_task_event = true`
  - 说明这次 route 不只是改展示，还真正触发了状态机里的“新任务切换”
- 如果 `near_done_condition_met = true` 但 `near_done_active = false`
  - 说明条件刚满足，但状态机还没切进 `AUTO_DONE_NEAR`，需要结合当前 `drive_mode` 和状态回调节奏一起看
- 如果 `near_done_active = true`
  - 再看 `near_done_remaining_sec`
  - 可以直接判断这个附近完成状态还会保持多久

---

## 11. 现场建议

现场最推荐直接观察这一条命令：

```bash
ros2 topic echo /app/display/debug/task_semantic_status
```

如果只想抓重点字段，可以优先盯这几组：

1. 任务切换：
   - `last_route_decision`
   - `last_triggered_new_task_event`
2. 锁存任务：
   - `semantic_origin_station_name`
   - `semantic_target_station_name`
3. 当前 route 推断：
   - `inferred_current_station_name`
   - `inferred_target_station_name`
4. 附近完成：
   - `near_done_active`
   - `near_done_condition_met`
   - `near_done_remaining_sec`

---

## 12. 当前约束与限制

当前设计的前提是：

- 只有 `goal`、`route`、Autoware 状态等本地信号
- 没有云端 `task_id`

因此需要接受一个事实：

- 系统能保证“按当前业务规则稳定处理”
- 不能保证“完全还原外部发布者真正的业务意图”

例如：

- 如果任务正在执行中，外部又下发了一个“目标站相同但业务上其实是全新的一单任务”
- 当前车端仍会把它识别成“重规划”

这是在没有 `task_id` 的条件下无法彻底避免的。

---

## 13. 后续可扩展方向

如果后面可以拿到更强的任务标识，可以继续升级：

1. 优先使用 `task_id` 判断新任务/重规划
2. `target_station_index` 退化成没有 `task_id` 时的备用规则
3. 把“已完成 / 已取消 / 已中止”进一步和云端任务状态对齐

这样可以从“车端业务约定”升级为“任务级严格语义”。
