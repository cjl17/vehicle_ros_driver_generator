## 驾驶模式说明（结合 `drive_mode.drawio`）

本文档面向使用和维护 Pixmoving 底盘接口的开发者。
目标是把 `drive_mode.drawio` 当前这一页的运营语义，以及当前代码实现真值之间的关系讲清楚。

阅读时遵循以下原则：

1. 运营语义、流程理解，优先看 `drive_mode.drawio` 的 `运营语义图` 页面。
2. 代码真值、精确转移条件，优先看 `drive_mode_state_machine.hpp` / `pixmoving_drive_mode.cpp`。

补充说明：

- 如果你在排查“同目标站重规划为什么不再被当成新任务”，请同时参考 `task_replanning_station_semantic.md`
- 本文档重点讲驾驶模式如何切换，不展开任务语义锁存细节

---

## 1. 图纸与代码的关系

### 1.1 运营语义图在表达什么

`drive_mode.drawio` 的 `运营语义图` 页面把状态机拆成两条运营域：

- `ManualDomain`
- `AutoDomain`

其中最关键的设计意图有 4 点：

1. 把 `Manual` 和 `Auto` 作为两个大类来看，不再只盯着单个实现状态。
2. 急停在运营语义上拆成两条链：
   - `ManualEmergencyStop`
   - `AutoEmergencyStop`
3. 完成态、取消态都只是短暂收尾态，不是长期停留态。
4. 收尾结束后，统一按 `decentralization`（是否放权）决定回 `AutoStandby` 还是 `ManualControl`。

### 1.2 当前代码如何对应图纸

当前代码已经按图纸语义拆成两个内部急停状态：

- `ManualEmergencyStop`
- `AutoEmergencyStop`

但两者对外都映射到同一个 `DriveMode::EMERGENCY_STOP (mode=3)`。

另外，图上的虚线“恢复 `last_auto_substate`”目前仍是预留方案，代码还没有实现。

---

## 2. 运营语义图状态总览

下表按 `运营语义图` 的表达方式说明每个状态在运营中的含义。

| 状态名 | mode | 运营语义 |
|---|---:|---|
| `ManualControl` | 1 | 手动控制态，车辆由遥控/人工直接控制 |
| `RemoteNetwork` | 2 | 远程网络态，当前预留 |
| `ManualEmergencyStop` | — | 手动域中的急停态，强调“车当前不在自动任务链里” |
| `AutoStandby` | 4 | 已放权，等待 Autoware 进入 `DRIVING` |
| `AutoExecuting` | 5 | 自动驾驶执行中 |
| `AutoTakeoverManual` | 6 | 遥控接管态，自动任务还没彻底结束，但控制已被人工抢占 |
| `AutoTakeoverBrake` | 7 | 刹车接管态，更偏安全制动过渡态 |
| `AutoDoneNormal` | 8 | 正常到站完成，短暂发布后回落 |
| `AutoDoneNear` | 9 | 附近完成，就近停车收尾，hold 3s 后回落 |
| `AutoCancelTakeover` | 10 | 接管超时取消，任务收尾后回手动 |
| `AutoCancelNewTask` | 11 | 新任务打断旧任务，cancel 收尾后回落 |
| `AutoDoneEstopNear` | 12 | 终点附近急停完成，先进入一个短暂收尾态，再按急停/放权状态回落 |
| `AutoEmergencyStop` | — | 自动任务链中的急停态，强调“车是在自动任务过程中被急停打断” |

> 说明：
>
> - `运营语义图` 先从运营语义角度强调“手动域急停”和“自动域急停”的区别。
> - 当前代码已经把这两个急停态拆成独立内部状态，但对外仍统一反馈 `mode=3`。

---

## 3. 当前实现状态总览

当前 SML 实现里，真正存在于代码中的核心状态如下。
注意：内部状态数比对外 `DriveMode` 枚举多 1 个，因为两个急停内部状态共享同一个对外 mode。

| 实现状态 | mode | 说明 |
|---|---:|---|
| `ManualControl` | 1 | 手动控制 |
| `RemoteNetwork` | 2 | 远程网络，预留 |
| `ManualEmergencyStop` | 3 | 手动域急停内部状态，对外反馈 `mode=3` |
| `AutoStandby` | 4 | 自动待命 |
| `AutoExecuting` | 5 | 自动执行 |
| `AutoTakeoverManual` | 6 | 遥控接管 |
| `AutoTakeoverBrake` | 7 | 刹车接管 |
| `AutoDoneNormal` | 8 | 正常完成 |
| `AutoDoneNear` | 9 | 附近完成 |
| `AutoCancelTakeover` | 10 | 接管超时取消 |
| `AutoCancelNewTask` | 11 | 新任务取消旧任务 |
| `AutoDoneEstopNear` | 12 | 附近急停完成 |
| `AutoEmergencyStop` | 3 | 自动域急停内部状态，对外反馈 `mode=3` |

> 注意：对外发布到 `/drive_mode/state_machine` 和 `vehicle_info.mode` 的，仍然只有 12 个 `DriveMode` 枚举值；`ManualEmergencyStop` / `AutoEmergencyStop` 都映射到 `EMERGENCY_STOP(3)`。

---

## 4. 上下文与事件

### 4.1 `DriveModeContext`

`DriveModeContext` 承载状态机决策所需的上下文，核心字段如下：

- `autoware_state`
  当前 Autoware 高层状态，例如 `DRIVING`、`WAITING_FOR_ENGAGE`
- `vcu_brake_pedal_triggered`
  当前刹车踏板是否被踩下
- `vehicle_speed_kmh`
  当前车速
- `target_distance_m`
  当前距离目标点/站点的距离
- `has_active_task`
  当前是否存在活动任务
- `decentralization`
  是否已放权给自动驾驶
- `is_estop`
  当前是否处于急停
- `current_time`
  当前时间戳
- `auto_last_time`
  最近一次进入自动驾驶的时间，用于计算接管持续时间
- `resend_cancel_count`
  新任务取消旧任务时的 cancel 重发计数
- `near_done_hold_until_sec`
  `AutoDoneNear` 的 hold 结束时间
- `estop_done_hold_until_sec`
  `AutoDoneEstopNear` 的 hold 结束时间
- `auto_done_normal_pending_publish`
  `AutoDoneNormal` 是否还需要保留 1 个发布周期

### 4.2 `DriveModeEvents`

核心事件如下：

| 事件 | 含义 |
|---|---|
| `AutowareDriving` | Autoware 进入 `DRIVING` |
| `AutowareWaitingForEngage` | Autoware 等待接管/等待 Engage |
| `AutowareArrivedGoal` | Autoware 到达目标点 |
| `BrakePedalPressed` / `BrakePedalReleased` | 刹车踩下 / 松开 |
| `RemoteTakeover` / `RemoteRelease` | 遥控接管 / 放权；事件在状态机定义中已存在，但当前 `update()` 路径未直接 `process_event` |
| `TakeoverTimeout` | 接管时长超过 300s |
| `TakeoverCancelTimeout` | 接管取消收尾超过 303s |
| `NewTaskReceived` | 收到新任务 |
| `NearStationStopped` | 在站点附近停车，满足附近完成条件 |
| `EmergencyNearGoalTriggered` | 在终点附近接管态下触发急停，满足附近急停完成条件 |
| `EmergencyTriggered` / `EmergencyCleared` | 急停触发 / 急停解除；根据当前所在域进入 `ManualEmergencyStop` 或 `AutoEmergencyStop` |
| `CancelCountTick` | cancel 计数器自减 |
| `Update` | 周期性收尾/守卫检查 |

其中两个“附近完成”相关事件需要特别区分：

- `NearStationStopped`
  业务语义是“附近完成”，通常对应 `AutoTakeoverManual -> AutoDoneNear`
- `EmergencyNearGoalTriggered`
  业务语义是“附近急停完成”，对应接管态下已在终点附近、已基本停稳、且触发急停

---

## 5. 运营语义图主流程分析

这一节按 `运营语义图` 来读，不追求把每个实现 guard 展开到代码级，而是强调运营链路是否顺。

### 5.1 手动域到自动域

主链如下：

1. `Start -> ManualControl`
2. `ManualControl --[放权 + !is_estop]--> AutoStandby`
3. `AutoStandby --[AutowareDriving]--> AutoExecuting`

这条链的运营含义是：

- 默认先落在手动态
- 放权后进入自动待命
- 只有当 Autoware 明确进入 `DRIVING`，才真正进入自动执行

这个设计是合理的，因为它把“放权”和“开始执行任务”拆成了两个阶段：

- `AutoStandby` 表示控制权已交给自动系统
- `AutoExecuting` 表示自动任务真的开始跑了

### 5.2 自动执行到接管

自动执行时有两种典型打断路径：

1. `AutoExecuting --[RemoteTakeover]--> AutoTakeoverManual`
2. `AutoExecuting --[BrakePedalPressed]--> AutoTakeoverBrake`

这也符合运营直觉：

- 遥控器抢权，进入“人工接管语义”更强的 `AutoTakeoverManual`
- 踩刹车，先进入安全优先的 `AutoTakeoverBrake`

刹车接管之后有两个恢复方向：

- `BrakeReleased + autoware_state == DRIVING -> AutoExecuting`
- `BrakeReleased + autoware_state != DRIVING -> AutoTakeoverManual`

也就是说，`AutoTakeoverBrake` 不是稳定的长期运营态，而是一个过渡态：

- 条件恢复充分，回自动执行
- 条件恢复不充分，退到普通接管态

### 5.3 完成态与取消态

`运营语义图` 把收尾态统一放在“完成 / 收尾类”区域，表达很清楚：

- `AutoExecuting --[ArrivedGoal]--> AutoDoneNormal`
- `AutoTakeoverManual --[NearStationStopped]--> AutoDoneNear`
- `AutoTakeoverManual --[TakeoverTimeout]--> AutoCancelTakeover`
- `AutoExecuting / AutoTakeoverManual / AutoTakeoverBrake --[NewTaskReceived]--> AutoCancelNewTask`

这些状态的共性是：

1. 都不是长期稳定态
2. 都要经过短暂收尾
3. 收尾后再决定回 `AutoStandby` 还是 `ManualControl`

其中：

- `AutoDoneNormal`
  保持 1 个发布周期，保证外部能稳定看到一次 `mode=8`
- `AutoDoneNear`
  hold 3s，强调“已就近停车完成”
- `AutoCancelTakeover`
  等待 `TakeoverCancelTimeout` 后直接回手动
- `AutoCancelNewTask`
  等待 cancel 计数归零后，再按放权状态回落

### 5.4 急停链

`运营语义图` 最重要的变化，是把急停按运营来源分成两条链：

#### 手动域急停

- `ManualControl --[EmergencyTriggered]--> ManualEmergencyStop`
- `ManualEmergencyStop --[EmergencyCleared]--> ManualControl`

它表达的是：车本来就在手动域里，急停解除后也仍然回到手动域。

#### 自动域急停

自动域中，以下状态都可能被急停打断并进入 `AutoEmergencyStop`：

- `AutoStandby`
- `AutoExecuting`
- `AutoTakeoverManual`
- `AutoTakeoverBrake`
- `AutoDoneNormal`
- `AutoDoneNear`
- `AutoCancelTakeover`
- `AutoCancelNewTask`
- `AutoDoneEstopNear`

急停解除后的当前实现策略是：

- `EmergencyCleared + decentralization -> AutoStandby`
- `EmergencyCleared + !decentralization -> ManualControl`

这说明当前实现是“按是否放权恢复域”，而不是“恢复到急停前的具体子状态”。

> `运营语义图` 上的虚线 `恢复 last_auto_substate` 是预留设计，不是当前代码行为。

### 5.5 附近完成与附近急停完成

这两条链在 `运营语义图` 里已经区分得比较清楚：

#### 附近完成

- `AutoTakeoverManual --[NearStationStopped]--> AutoDoneNear`

它表达的是：

1. 车已经从纯自动执行切到接管态
2. 车辆在目标附近停住
3. 不再追求“严格到目标点完成”，而是按“就近完成”收尾

#### 附近急停完成

- `AutoTakeoverManual --[附近急停完成]--> AutoDoneEstopNear`
- `AutoTakeoverBrake --[EmergencyNearGoalTriggered]--> AutoDoneEstopNear`

从运营语义看，这条链表达的是：

1. 车已经进入接管链
2. 车辆已经在终点附近，且基本停住
3. 此时触发急停
4. 不直接按普通 `AutoEmergencyStop` 处理，而是先进入一个“附近急停完成”的短暂收尾态

这和普通急停的差别在于：

- 普通急停：强调任务被中断
- 附近急停完成：强调任务虽然以急停结束，但车辆已经在终点附近，可按“接近完成”逻辑收尾

---

## 6. 当前实现真值（SML 定义 + 当前运行路径）

如果要落到代码层面，需要区分两件事：

1. 状态机定义里写了什么
2. `DriveModeManager::update()` 当前实际会派发哪些事件

下面先写“当前运行路径下会实际发生的实现逻辑”，再单独列出“状态机定义已存在、但当前 `update()` 路径未直接派发”的转移。

### 6.1 自动主链

| 当前状态 | 事件 | 条件 | 下一个状态 |
|---|---|---|---|
| `ManualControl` | `Update` | `decentralization && !is_estop` | `AutoStandby` |
| `AutoStandby` | `AutowareDriving` | — | `AutoExecuting` |
| `AutoStandby` | `EmergencyTriggered` | — | `AutoEmergencyStop` |
| `AutoExecuting` | `AutowareArrivedGoal` | — | `AutoDoneNormal` |
| `AutoExecuting` | `BrakePedalPressed` | — | `AutoTakeoverBrake` |
| `AutoExecuting` | `EmergencyTriggered` | — | `AutoEmergencyStop` |

### 6.2 接管与恢复

| 当前状态 | 事件 | 条件 | 下一个状态 |
|---|---|---|---|
| `AutoTakeoverManual` | `AutowareDriving` | — | `AutoExecuting` |
| `AutoTakeoverManual` | `TakeoverTimeout` | — | `AutoCancelTakeover` |
| `AutoTakeoverManual` | `NearStationStopped` | — | `AutoDoneNear` |
| `AutoTakeoverManual` | `EmergencyNearGoalTriggered` | — | `AutoDoneEstopNear` |
| `AutoTakeoverManual` | `EmergencyTriggered` | — | `AutoEmergencyStop` |
| `AutoTakeoverBrake` | `BrakePedalReleased` | `autoware_state == DRIVING` | `AutoExecuting` |
| `AutoTakeoverBrake` | `BrakePedalReleased` | `autoware_state != DRIVING` | `AutoTakeoverManual` |
| `AutoTakeoverBrake` | `AutowareWaitingForEngage` | — | `AutoTakeoverManual` |
| `AutoTakeoverBrake` | `EmergencyNearGoalTriggered` | — | `AutoDoneEstopNear` |
| `AutoTakeoverBrake` | `EmergencyTriggered` | — | `AutoEmergencyStop` |

### 6.3 新任务与取消

| 当前状态 | 事件 | 条件 | 下一个状态 |
|---|---|---|---|
| `AutoExecuting` | `NewTaskReceived` | — | `AutoCancelNewTask` |
| `AutoTakeoverManual` | `NewTaskReceived` | — | `AutoCancelNewTask` |
| `AutoTakeoverBrake` | `NewTaskReceived` | — | `AutoCancelNewTask` |
| `AutoCancelNewTask` | `CancelCountTick` | — | `AutoCancelNewTask` |
| `AutoCancelNewTask` | `Update` | `resend_cancel_count == 0 && decentralization` | `AutoStandby` |
| `AutoCancelNewTask` | `Update` | `resend_cancel_count == 0 && !decentralization` | `ManualControl` |
| `AutoCancelNewTask` | `EmergencyTriggered` | — | `AutoEmergencyStop` |
| `AutoCancelTakeover` | `EmergencyTriggered` | — | `AutoEmergencyStop` |
| `AutoCancelTakeover` | `TakeoverCancelTimeout` | — | `ManualControl` |

### 6.4 完成态回落

| 当前状态 | 事件 | 条件 | 下一个状态 |
|---|---|---|---|
| `AutoDoneNormal` | `Update` | `decentralization` | `AutoStandby` |
| `AutoDoneNormal` | `Update` | `!decentralization` | `ManualControl` |
| `AutoDoneNormal` | `EmergencyTriggered` | — | `AutoEmergencyStop` |
| `AutoDoneNear` | `Update` | `current_time >= near_done_hold_until && decentralization` | `AutoStandby` |
| `AutoDoneNear` | `Update` | `current_time >= near_done_hold_until && !decentralization` | `ManualControl` |
| `AutoDoneNear` | `EmergencyTriggered` | — | `AutoEmergencyStop` |
| `AutoDoneEstopNear` | `Update` | `current_time >= estop_done_hold_until && is_estop` | `AutoEmergencyStop` |
| `AutoDoneEstopNear` | `Update` | `current_time >= estop_done_hold_until && !is_estop && decentralization` | `AutoStandby` |
| `AutoDoneEstopNear` | `Update` | `current_time >= estop_done_hold_until && !is_estop && !decentralization` | `ManualControl` |

### 6.5 当前实现里的急停恢复

| 当前状态 | 事件 | 条件 | 下一个状态 |
|---|---|---|---|
| `ManualEmergencyStop` | `EmergencyCleared` | — | `ManualControl` |
| `AutoEmergencyStop` | `EmergencyCleared` | `decentralization` | `AutoStandby` |
| `AutoEmergencyStop` | `EmergencyCleared` | `!decentralization` | `ManualControl` |

> 当前实现没有 `last_auto_substate` 记忆恢复。
> 急停解除后如果想重新回到 `AutoExecuting`，需要等待 Autoware 重新发出 `DRIVING`。

### 6.6 已定义但当前 `update()` 路径未直接派发的转移

下列转移已经写在状态机定义里，但当前 `DriveModeManager::update()` 的运行路径没有直接 `process_event`：

| 当前状态 | 事件 | 下一个状态 | 说明 |
|---|---|---|---|
| `ManualControl` | `RemoteRelease` | `AutoStandby` | 语义存在，但当前主要由 `Update + decentralization` 进入 `AutoStandby` |
| `AutoStandby` | `RemoteTakeover` | `ManualControl` | 语义存在，但当前主要由 `Update + !decentralization` 回手动 |
| `AutoExecuting` | `RemoteTakeover` | `AutoTakeoverManual` | `运营语义图` 保留这条运营语义，但当前 `update()` 路径未直接派发该事件 |
| `ManualControl` | `AutowareOther` | `RemoteNetwork` | 预留占位，guard 为恒 false，不会实际进入 |

---

## 7. 事件触发来源

所有事件统一由 `DriveModeManager::update()` 内部派发。

### 7.1 Autoware 事件

由 `processAutowareState()` 触发：

- `AutowareDriving`
- `AutowareWaitingForEngage`
- `AutowareArrivedGoal`
- 其他辅助 Autoware 事件

### 7.2 时间事件

由 `checkTimeEvents()` 触发：

- 接管超过 300s -> `TakeoverTimeout`
- 接管取消收尾超过 303s -> `TakeoverCancelTimeout`

### 7.3 车辆事件

由 `checkVehicleEvents()` 触发：

- 踩刹车 / 松刹车 -> `BrakePedalPressed` / `BrakePedalReleased`
- 站点附近停车 -> `NearStationStopped`
- cancel 计数递减 -> `CancelCountTick`

当前 `checkVehicleEvents()` 没有直接派发：

- `RemoteTakeover`
- `RemoteRelease`

### 7.4 顶层优先处理事件

`update()` 一开始会优先处理：

- `EmergencyTriggered`
- `EmergencyCleared`
- `EmergencyNearGoalTriggered`

这意味着急停相关逻辑优先级最高。

---

## 8. 典型场景

### 8.1 正常自动驾驶任务

1. `ManualControl -> AutoStandby`
2. `AutoStandby -> AutoExecuting`
3. `AutoExecuting -> AutoDoneNormal`
4. `AutoDoneNormal` 保持 1 个发布周期
5. 再按放权状态回 `AutoStandby` 或 `ManualControl`

### 8.2 刹车接管再恢复

1. `AutoExecuting -> AutoTakeoverBrake`
2. 如果松刹车时 `autoware_state == DRIVING`，回 `AutoExecuting`
3. 如果松刹车时 `autoware_state != DRIVING`，转 `AutoTakeoverManual`

### 8.3 接管后就近完成

1. `AutoExecuting -> AutoTakeoverManual`
2. 在站点附近停车，触发 `NearStationStopped`
3. `AutoTakeoverManual -> AutoDoneNear`
4. hold 3s 后按放权状态回落

### 8.4 接管后终点附近急停完成

1. 车辆已经进入接管链：`AutoTakeoverManual` 或 `AutoTakeoverBrake`
2. 车辆已在终点附近，且基本停住
3. 触发急停，进入 `AutoDoneEstopNear`
4. hold 结束后：
   - 急停仍在 -> `AutoEmergencyStop`（对外仍反馈 `mode=3`）
   - 急停解除且已放权 -> `AutoStandby`
   - 急停解除且未放权 -> `ManualControl`

### 8.5 新任务打断旧任务

1. `AutoExecuting` / `AutoTakeoverManual` / `AutoTakeoverBrake -> AutoCancelNewTask`
2. cancel 计数器逐步归零
3. 归零后按放权状态回 `AutoStandby` 或 `ManualControl`

---

## 9. 当前已知限制

| 限制 | 当前行为 | 后续方向 |
|---|---|---|
| 急停恢复不记忆来源子状态 | 急停解除后只按当前域和 `decentralization` 回 `ManualControl` / `AutoStandby` | 如有需要，可扩展 `last_auto_substate` 恢复 |
| 两个内部急停态共享一个对外 mode | `ManualEmergencyStop` / `AutoEmergencyStop` 都反馈 `mode=3` | 继续用 `getCurrentStateName()` 区分内部状态、用 `mode` 对外兼容 |
| `AutoDoneNear` hold 固定 3s | 由逻辑固定写入 | 可参数化 |
| `AutoDoneEstopNear` hold 固定 0.5s | 由 `estop_done_hold_sec` 控制 | 已参数化，可继续调优 |
| 接管与取消超时固定 300s / 303s | 当前实现已写死在逻辑里 | 如运营需要，可进一步参数化 |

---

## 10. 维护建议

当状态机继续演进时，建议按下面顺序同步：

1. 先改 `drive_mode.drawio` 的 `运营语义图` 页面，统一运营语义
2. 再改代码，统一实现真值
3. 最后更新本文件，明确“图在讲什么，代码实际怎么做”

这样可以避免出现“图讲运营语义，文档讲代码实现，但两者没有说明关系”的问题。

---

如需继续往下看代码，可参考：

- `include/pixmoving_chassis_interface/drive_mode_state_machine.hpp`
- `src/pixmoving_drive_mode.cpp`
- `doc/drive_mode.drawio`
