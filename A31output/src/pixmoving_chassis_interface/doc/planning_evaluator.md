# Autoware Planning Evaluator 功能包说明

## 概述

`autoware_planning_evaluator` 是 Autoware 中用于**实时评估规划质量**的核心模块。它通过计算多维度指标来量化评估自动驾驶系统的规划性能，包括舒适性、稳定性、安全性等方面。

## 核心功能

### 1. 实时指标发布
- 订阅规划轨迹和相关传感器数据
- 实时计算各类评估指标
- 通过 `/planning/planning_evaluator/metrics` 话题发布 `MetricArray` 消息
- 供其他模块（如 HMI、监控系统）订阅使用

### 2. 离线数据记录
- 节点关闭时将统计数据保存为 JSON 文件
- 文件路径：`<ros2_logging_directory>/autoware_metrics/<node_name>-<time_stamp>.json`
- 用于离线分析和性能优化

## 指标分类体系

### 按数据类型分类

#### 1. 统计型指标 (Statistics-based)
使用 `autoware_utils::Accumulator` 计算统计值：
- `/mean`: 平均值
- `/min`: 最小值
- `/max`: 最大值
- `/count`: 计数

#### 2. 数值型指标 (Value-based)
单一数值指标：
- `/value`: 当前值

#### 3. 计数型指标 (Count-based)
事件计数指标：
- `/count`: 总计数
- `/count_in_duration`: 时间窗口内计数

### 按功能分类

## 详细指标说明

### 一、轨迹指标 (Trajectory Metrics)

评估当前规划轨迹 `T(0)` 本身的质量。

#### 1. `curvature` - 曲率
- **含义**: 轨迹各点的曲率统计
- **单位**: 1/m
- **用途**: 评估轨迹弯曲程度，曲率过大可能导致车辆难以跟踪
- **子指标**: `/mean`, `/min`, `/max`

#### 2. `velocity` - 速度
- **含义**: 轨迹各点的速度统计
- **单位**: m/s
- **用途**: 评估速度规划的合理性
- **子指标**: `/mean`, `/min`, `/max`

#### 3. `acceleration` - 加速度
- **含义**: 轨迹各点的加速度统计
- **单位**: m/s²
- **用途**: 评估加速度变化，影响乘坐舒适性
- **舒适性标准**: 
  - 正常加速: < 2.0 m/s²
  - 正常减速: > -2.0 m/s²
  - 紧急制动: -3.0 ~ -5.0 m/s²
- **子指标**: `/mean`, `/min`, `/max`

#### 4. `jerk` - 急动度（加加速度）
- **含义**: 轨迹各点的急动度统计（加速度的变化率）
- **单位**: m/s³
- **用途**: **舒适性的关键指标**，jerk 越小越舒适
- **舒适性标准**:
  - 优秀: < 0.5 m/s³
  - 良好: 0.5 ~ 1.0 m/s³
  - 可接受: 1.0 ~ 2.0 m/s³
  - 不舒适: > 2.0 m/s³
- **子指标**: `/mean`, `/min`, `/max`

#### 5. `length` - 轨迹长度
- **含义**: 规划轨迹的总长度
- **单位**: m
- **用途**: 评估规划范围

#### 6. `duration` - 预计行驶时间
- **含义**: 按规划速度行驶完轨迹所需时间
- **单位**: s
- **用途**: 评估时间效率

#### 7. `point_interval` - 点间距
- **含义**: 轨迹相邻点之间的距离统计
- **单位**: m
- **用途**: 评估轨迹分辨率

#### 8. `relative_angle` - 相对角度
- **含义**: 轨迹相邻点之间的角度变化
- **单位**: rad
- **用途**: 评估轨迹平滑度

### 二、轨迹偏差指标 (Trajectory Deviation Metrics)

通过对比当前轨迹 `T(0)` 与参考轨迹，评估规划偏差。

#### 1. `lateral_deviation` - 横向偏差
- **含义**: 当前轨迹点与参考轨迹最近点的横向距离
- **单位**: m
- **用途**: 评估轨迹是否偏离参考路径
- **子指标**: `/mean`, `/min`, `/max`

#### 2. `yaw_deviation` - 航向偏差
- **含义**: 当前轨迹点与参考轨迹最近点的航向角差异
- **单位**: rad
- **用途**: 评估车辆朝向是否与参考一致
- **子指标**: `/mean`, `/min`, `/max`

#### 3. `velocity_deviation` - 速度偏差
- **含义**: 当前轨迹点与参考轨迹最近点的速度差异
- **单位**: m/s
- **用途**: 评估速度规划是否符合参考
- **子指标**: `/mean`, `/min`, `/max`

### 三、轨迹稳定性指标 (Trajectory Stability Metrics) ⭐

**这是检测轨迹突变的核心指标组**，通过对比当前轨迹 `T(0)` 与上一帧轨迹 `T(-1)` 来评估规划稳定性。

#### 1. `stability` - 轨迹稳定性（横向偏差）
- **含义**: 在前瞻距离/时间内，`T(0)` 与 `T(-1)` 之间的横向偏差统计
- **单位**: m
- **用途**: **检测轨迹突变的主要指标**
- **判断标准**:
  - 稳定: < 0.1 m
  - 轻微抖动: 0.1 ~ 0.3 m
  - 明显突变: 0.3 ~ 0.5 m
  - 严重突变: > 0.5 m
- **参数**:
  - `trajectory.lookahead.max_time_s`: 前瞻时间
  - `trajectory.lookahead.max_dist_m`: 前瞻距离
- **子指标**: `/mean`, `/min`, `/max`

#### 2. `stability_frechet` - Frechet 距离
- **含义**: 使用 Frechet 距离算法衡量 `T(0)` 与 `T(-1)` 两条曲线的相似度
- **单位**: m
- **用途**: **检测轨迹形状变化**，比简单的点对点距离更能反映整体轨迹变化
- **判断标准**:
  - 稳定: < 0.2 m
  - 轻微变化: 0.2 ~ 0.5 m
  - 明显变化: 0.5 ~ 1.0 m
  - 剧烈变化: > 1.0 m
- **子指标**: `/mean`, `/min`, `/max`

#### 3. `lateral_trajectory_displacement_local` - 局部横向位移
- **含义**: 在车辆当前位置，`T(0)` 与 `T(-1)` 的横向位移
- **单位**: m
- **用途**: **检测当前位置的轨迹突变**
- **判断标准**:
  - 稳定: < 0.05 m
  - 可接受: 0.05 ~ 0.15 m
  - 突变: > 0.15 m
- **子指标**: `/mean`, `/min`, `/max`

#### 4. `lateral_trajectory_displacement_lookahead` - 前瞻横向位移
- **含义**: 在前瞻时间内，`T(0)` 与 `T(-1)` 的横向位移统计
- **单位**: m
- **用途**: **检测未来轨迹的突变趋势**
- **参数**: `trajectory.evaluation_time_s` (前瞻评估时间)
- **子指标**: `/mean`, `/max`

### 四、障碍物安全指标 (Trajectory Obstacle Metrics)

评估规划轨迹相对于障碍物的安全性。

#### 1. `obstacle_distance` - 障碍物距离
- **含义**: 各障碍物质心到最近轨迹点的距离统计
- **单位**: m
- **用途**: 评估与障碍物的安全距离
- **子指标**: `/mean`, `/min`, `/max`

#### 2. `obstacle_ttc` - 碰撞时间 (Time-To-Collision)
- **含义**: 对于接近轨迹的障碍物，计算预计碰撞时间
- **单位**: s
- **用途**: 评估碰撞风险
- **参数**: `obstacle.dist_thr_m` (距离阈值，判断障碍物是否接近轨迹)
- **子指标**: `/mean`, `/min`, `/max`

### 五、目标点偏差指标 (Modified Goal Metrics)

评估修正后的目标点与车辆当前位置的偏差。

#### 1. `modified_goal_longitudinal_deviation` - 纵向偏差
- **单位**: m
- **子指标**: `/mean`, `/min`, `/max`

#### 2. `modified_goal_lateral_deviation` - 横向偏差
- **单位**: m
- **子指标**: `/mean`, `/min`, `/max`

#### 3. `modified_goal_yaw_deviation` - 航向偏差
- **单位**: rad
- **子指标**: `/mean`, `/min`, `/max`

### 六、规划因子指标 (Planning Factor Metrics)

评估各规划模块的行为决策。

#### 1. `stop_decision` - 停车决策
- **含义**: 监控各模块的停车决策行为
- **参数**:
  - `stop_decision.time_count_threshold_s`: 时间阈值
  - `stop_decision.dist_count_threshold_m`: 距离阈值
  - `stop_decision.module_list`: 要监控的模块列表
- **子指标**:
  - `/{module_name}/keep_duration`: 当前停车决策持续时间
  - `/{module_name}/distance_to_stop`: 到停止线的距离
  - `/{module_name}/count`: 停车决策次数

#### 2. `abnormal_stop_decision` - 异常停车决策
- **含义**: 检测无法以最大减速度安全停车的异常决策
- **参数**: `stop_decision.abnormal_deceleration_threshold_mps2` (最大减速度阈值)

### 七、转向灯指标 (Blinker Metrics)

#### `blinker_change_count` - 转向灯切换次数
- **含义**: 统计转向灯状态变化次数
- **参数**: `blinker_change_count.window_duration_s` (统计时间窗口)
- **子指标**: `/count_in_duration`, `/count`

### 八、方向盘指标 (Steering Metrics)

#### `steer_change_count` - 方向盘转向变化次数
- **含义**: 统计方向盘转向率变化次数（正负切换）
- **参数**:
  - `steer_change_count.window_duration_s`: 统计时间窗口
  - `steer_change_count.steer_rate_margin`: 转向率零值容差
- **子指标**: `/count_in_duration`, `/count`

### 九、运动状态信息 (Kinematic State)

#### `kinematic_state` - 当前运动状态
实时车辆运动状态：
- `/velocity`: 当前速度 (m/s)
- `/acceleration`: 当前加速度 (m/s²)
- `/jerk`: 当前急动度 (m/s³)

### 十、车道信息 (Ego Lane Info)

#### `ego_lane_info` - 车道信息
- `/lanelet_id`: 当前所在车道 ID
- `/s`: 车辆在车道中的纵向位置（弧长）
- `/t`: 车辆在车道中的横向偏移

## 输入话题

| 话题名称 | 消息类型 | 说明 |
|---------|---------|------|
| `~/input/trajectory` | `Trajectory` | 待评估的主轨迹 |
| `~/input/reference_trajectory` | `Trajectory` | 参考轨迹 |
| `~/input/objects` | `PredictedObjects` | 障碍物信息 |
| `~/input/modified_goal` | `PoseWithUuidStamped` | 修正后的目标点 |
| `~/input/odometry` | `Odometry` | 车辆里程计 |
| `~/input/route` | `LaneletRoute` | 路由信息 |
| `~/input/vector_map` | `LaneletMapBin` | 矢量地图 |
| `~/input/acceleration` | `AccelWithCovarianceStamped` | 车辆加速度 |
| `~/input/steering_status` | `SteeringReport` | 方向盘状态 |
| `~/input/turn_indicators_status` | `TurnIndicatorsReport` | 转向灯状态 |

## 输出话题

| 话题名称 | 消息类型 | 说明 |
|---------|---------|------|
| `~/metrics` | `MetricArray` | 所有评估指标 |
| `~/debug/processing_time_ms` | `Float64Stamped` | 节点处理时间 |

## 如何判断轨迹突变和舒适性

### 轨迹突变判断逻辑

轨迹突变主要通过**轨迹稳定性指标**来检测：

```
1. stability (横向偏差)
   - 计算 T(0) 与 T(-1) 在前瞻范围内的横向偏差
   - 偏差大 → 轨迹突变
   
2. stability_frechet (Frechet 距离)
   - 衡量两条轨迹曲线的整体相似度
   - 距离大 → 轨迹形状变化大
   
3. lateral_displacement_local (局部横向位移)
   - 检测当前位置的轨迹偏移
   - 突然的大幅偏移 → 立即突变
   
4. lateral_displacement_lookahead (前瞻横向位移)
   - 检测未来轨迹的偏移趋势
   - 最大值大 → 未来可能突变
```

**突变检测示例**：
```cpp
// 伪代码示例
if (stability_mean > 0.3 || 
    stability_frechet_mean > 0.5 || 
    lateral_displacement_local > 0.15) {
    // 检测到轨迹突变
    trigger_warning();
}
```

### 舒适性判断逻辑

舒适性主要通过**轨迹指标**中的运动学参数来评估：

```
1. jerk (急动度) - 最关键指标
   - 加速度变化率
   - jerk 越小 → 越舒适
   - 标准: < 0.5 m/s³ 优秀, > 2.0 m/s³ 不舒适
   
2. acceleration (加速度)
   - 加减速的平稳性
   - 标准: -2.0 ~ 2.0 m/s² 舒适范围
   
3. velocity (速度)
   - 速度变化的平稳性
   - 频繁加减速 → 不舒适
```

**舒适性评估示例**：
```cpp
// 伪代码示例
double comfort_score = 100.0;

// jerk 惩罚（权重最高）
if (jerk_mean > 2.0) comfort_score -= 40;
else if (jerk_mean > 1.0) comfort_score -= 20;
else if (jerk_mean > 0.5) comfort_score -= 10;

// acceleration 惩罚
if (abs(acceleration_max) > 3.0) comfort_score -= 20;
else if (abs(acceleration_max) > 2.0) comfort_score -= 10;

// 最终评级
if (comfort_score >= 90) return "优秀";
else if (comfort_score >= 70) return "良好";
else if (comfort_score >= 50) return "可接受";
else return "不舒适";
```

## 实际应用场景

### 1. 实时监控
```bash
# 查看实时指标
ros2 topic echo /planning/planning_evaluator/metrics
```

### 2. 舒适性监控
监控 `jerk`, `acceleration` 的 mean 和 max 值，确保在舒适范围内。

### 3. 轨迹稳定性监控
监控 `stability`, `stability_frechet`, `lateral_displacement_*` 指标，检测规划抖动。

### 4. 安全性监控
监控 `obstacle_distance`, `obstacle_ttc` 指标，确保与障碍物保持安全距离。

### 5. 离线分析
节点关闭后分析 JSON 文件，进行性能优化和参数调优。

## 注意事项

1. **时序假设**: 假设接收到轨迹 `T(0)` 时，它是基于最新的参考轨迹和障碍物信息生成的。如果在生成过程中有新的数据发布，可能导致评估不准确。

2. **精度限制**: 评估精度受轨迹分辨率限制。可以通过插值提高精度，但会显著增加计算开销。

3. **参数调优**: 各指标的阈值需要根据实际车辆特性和应用场景进行调优。

## 与 PlanningMetricsMonitor 的关系

`PlanningMetricsMonitor` 类（在 `pixmoving_chassis_interface` 中）是这个功能包的**消费者**：

- **Planning Evaluator**: 计算并发布指标
- **PlanningMetricsMonitor**: 订阅、提取、展示指标

```
[Planning Evaluator] --发布--> /planning/planning_evaluator/metrics
                                         ↓
                              [PlanningMetricsMonitor] --展示--> HMI/日志
```

## 参考资料

- 指标定义: `include/autoware/planning_evaluator/metrics/metric.hpp`
- 输出指标: `include/autoware/planning_evaluator/metrics/output_metric.hpp`
- 配置文件: `autoware_planning_evaluator.schema.json`
