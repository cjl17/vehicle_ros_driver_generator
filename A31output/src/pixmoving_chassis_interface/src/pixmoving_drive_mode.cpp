// 基于 boost-ext/sml 的驾驶模式状态机实现
// 本文件实现了完整的驾驶模式状态转换逻辑，使用 SML 的转移表确保转换的正确性和可维护性

#include "pixmoving_chassis_interface/drive_mode_state_machine.hpp"
#include <autoware_system_msgs/msg/autoware_state.hpp>

namespace pixmoving
{
namespace chassis
{
namespace interface
{

namespace sml = boost::ext::sml;

// ==================== DriveModeManager 实现 ====================

DriveModeManager::DriveModeManager(rclcpp::Logger logger)
  : current_mode_(DriveMode::UNKNOWN),
    logger_(logger)
{
  context_.logger = &logger_;
  sm_ = std::make_unique<Sm>(DriveModeStateMachine::SmDef{context_});
  RCLCPP_INFO(logger_, "DriveModeManager initialized with boost-ext/sml state machine");
}

DriveMode DriveModeManager::update(uint8_t autoware_state, DriveModeContext& new_context)
{
  syncContextFromInput(autoware_state, new_context);
  
  // 计算接管时长
  context_.takeover_duration_sec = context_.current_time - context_.auto_last_time;

  const bool should_emit_estop_done_near =
    context_.is_estop &&
    context_.has_active_task &&
    context_.vehicle_speed_kmh <= 1.0 &&
    context_.target_distance_m <= context_.estop_done_distance_threshold_m &&
    (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverManual>) ||
     sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverBrake>));

  // 处理紧急停止（最高优先级），但对“终点附近急停结束”保留一个短暂收尾态。
  if (should_emit_estop_done_near && !sm_->is(sml::state<DriveModeStateMachine::AutoDoneEstopNear>) &&
      !isEmergencyStopState())
  {
    sm_->process_event(DriveModeEvents::EmergencyNearGoalTriggered{});
  }
  else if (context_.is_estop &&
           !isEmergencyStopState() &&
           !sm_->is(sml::state<DriveModeStateMachine::AutoDoneEstopNear>))
  {
    sm_->process_event(DriveModeEvents::EmergencyTriggered{});
  }
  else if (!context_.is_estop && isEmergencyStopState())
  {
    sm_->process_event(DriveModeEvents::EmergencyCleared{});
  }
  
  // 处理 Autoware 状态事件
  processAutowareState(autoware_state);
  
  // 检查时间相关事件
  checkTimeEvents();
  
  // 检查车辆状态事件
  checkVehicleEvents();

  // 任务切换事件放在车辆事件之后，避免新任务进入取消态的同一周期就扣减计数器。
  if (context_.new_task_received)
  {
    sm_->process_event(DriveModeEvents::NewTaskReceived{});
  }
  
  // 到站正常完成时，先稳定保留一个发布周期的 8: 正常完成，
  // 下一次 update() 再根据是否放权回落到 1/4。
  const bool defer_auto_done_normal_exit =
    sm_->is(sml::state<DriveModeStateMachine::AutoDoneNormal>) &&
    context_.auto_done_normal_pending_publish;

  // 触发一次 Update，用于处理“持续条件检查”（原 HFSM2 的 update/changeTo）
  if (!defer_auto_done_normal_exit)
  {
    sm_->process_event(DriveModeEvents::Update{});
  }
  
  if (defer_auto_done_normal_exit)
  {
    context_.auto_done_normal_pending_publish = false;
  }
  refreshCurrentMode();
  syncContextToOutput(new_context);
  
  return current_mode_;
}

DriveMode DriveModeManager::processRemoteReleaseForTest(DriveModeContext& context)
{
  syncContextFromInput(context.autoware_state, context);
  sm_->process_event(DriveModeEvents::RemoteRelease{});
  refreshCurrentMode();
  syncContextToOutput(context);
  return current_mode_;
}

DriveMode DriveModeManager::processRemoteTakeoverForTest(DriveModeContext& context)
{
  syncContextFromInput(context.autoware_state, context);
  sm_->process_event(DriveModeEvents::RemoteTakeover{});
  refreshCurrentMode();
  syncContextToOutput(context);
  return current_mode_;
}

void DriveModeManager::processAutowareState(uint8_t autoware_state)
{
  using AutowareState = autoware_system_msgs::msg::AutowareState;
  
  if (autoware_state == AutowareState::DRIVING)
  {
    sm_->process_event(DriveModeEvents::AutowareDriving{});
  }
  else if (autoware_state == AutowareState::WAITING_FOR_ENGAGE)
  {
    sm_->process_event(DriveModeEvents::AutowareWaitingForEngage{});
  }
  else if (autoware_state == AutowareState::ARRIVED_GOAL)
  {
    sm_->process_event(DriveModeEvents::AutowareArrivedGoal{});
  }
  else if (autoware_state == AutowareState::PLANNING)
  {
    sm_->process_event(DriveModeEvents::AutowarePlanning{});
  }
  else if (autoware_state == AutowareState::INITIALIZING)
  {
    sm_->process_event(DriveModeEvents::AutowareInitializing{});
  }
}

void DriveModeManager::checkTimeEvents()
{
  // 检查接管超时
  if (context_.takeover_duration_sec > 300.0 && context_.takeover_duration_sec <= 303.0)
  {
    if (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverManual>))
    {
      sm_->process_event(DriveModeEvents::TakeoverTimeout{});
    }
  }
  else if (context_.takeover_duration_sec > 303.0)
  {
    if (sm_->is(sml::state<DriveModeStateMachine::AutoCancelTakeover>))
    {
      sm_->process_event(DriveModeEvents::TakeoverCancelTimeout{});
    }
  }
}

void DriveModeManager::checkVehicleEvents()
{
  // 检查刹车踏板
  if (context_.vcu_brake_pedal_triggered)
  {
    if (sm_->is(sml::state<DriveModeStateMachine::AutoExecuting>))
    {
      sm_->process_event(DriveModeEvents::BrakePedalPressed{});
    }
  }
  else
  {
    if (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverBrake>))
    {
      sm_->process_event(DriveModeEvents::BrakePedalReleased{});
    }
  }
  
  // 检查附近完成条件
  if (context_.vehicle_speed_kmh <= 1.0 && 
      context_.target_distance_m <= 50.0 &&
      sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverManual>))
  {
    sm_->process_event(DriveModeEvents::NearStationStopped{});
  }
  
  // 检查计数器
  if (context_.resend_cancel_count > 0)
  {
    if (sm_->is(sml::state<DriveModeStateMachine::AutoCancelNewTask>))
    {
      sm_->process_event(DriveModeEvents::CancelCountTick{});
    }
  }
  
}

DriveMode DriveModeManager::getMode() const
{
  if (sm_->is(sml::state<DriveModeStateMachine::RemoteNetwork>))
    return DriveMode::REMOTE_NETWORK;
  else if (sm_->is(sml::state<DriveModeStateMachine::ManualControl>))
    return DriveMode::MANUAL_CONTROL;
  else if (isEmergencyStopState())
    return DriveMode::EMERGENCY_STOP;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoStandby>))
    return DriveMode::AUTO_STANDBY;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoExecuting>))
    return DriveMode::AUTO_EXECUTING;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverManual>))
    return DriveMode::AUTO_TAKEOVER_MANUAL;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverBrake>))
    return DriveMode::AUTO_TAKEOVER_BRAKE;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoDoneNormal>))
    return DriveMode::AUTO_DONE_NORMAL;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoDoneNear>))
    return DriveMode::AUTO_DONE_NEAR;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoDoneEstopNear>))
    return DriveMode::AUTO_DONE_ESTOP_NEAR;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoCancelTakeover>))
    return DriveMode::AUTO_CANCEL_TAKEOVER;
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoCancelNewTask>))
    return DriveMode::AUTO_CANCEL_NEW_TASK;
  else
    return DriveMode::UNKNOWN;
}

void DriveModeManager::syncContextFromInput(uint8_t autoware_state, const DriveModeContext& new_context)
{
  context_.autoware_state = autoware_state;
  context_.vcu_brake_pedal_triggered = new_context.vcu_brake_pedal_triggered;
  context_.vehicle_speed_kmh = new_context.vehicle_speed_kmh;
  context_.target_distance_m = new_context.target_distance_m;
  context_.has_active_task = new_context.has_active_task;
  context_.autonomous_driving = new_context.autonomous_driving;
  context_.decentralization = new_context.decentralization;
  context_.is_estop = new_context.is_estop;
  context_.current_time = new_context.current_time;
  context_.auto_last_time = new_context.auto_last_time;
  context_.station_distance = new_context.station_distance;
  context_.new_task_received = new_context.new_task_received;
  context_.resend_cancel_count = new_context.resend_cancel_count;
  context_.near_done_hold_until_sec = new_context.near_done_hold_until_sec;
  context_.estop_done_hold_until_sec = new_context.estop_done_hold_until_sec;
  context_.estop_done_distance_threshold_m = new_context.estop_done_distance_threshold_m;
  context_.estop_done_hold_sec = new_context.estop_done_hold_sec;
}

void DriveModeManager::syncContextToOutput(DriveModeContext& context) const
{
  context.autonomous_driving = context_.autonomous_driving;
  context.auto_last_time = context_.auto_last_time;
  context.resend_cancel_count = context_.resend_cancel_count;
  context.near_done_hold_until_sec = context_.near_done_hold_until_sec;
  context.estop_done_hold_until_sec = context_.estop_done_hold_until_sec;
  context.auto_done_normal_pending_publish = context_.auto_done_normal_pending_publish;
  context.last_mode = current_mode_;
}

void DriveModeManager::refreshCurrentMode()
{
  const DriveMode new_mode = getMode();
  if (new_mode != current_mode_)
  {
    RCLCPP_INFO(logger_, "Drive mode changed: %s -> %s (State: %s)",
                ChassisInterfaceUtils::driveModeToString(static_cast<int8_t>(current_mode_)).c_str(),
                ChassisInterfaceUtils::driveModeToString(static_cast<int8_t>(new_mode)).c_str(),
                getCurrentStateName().c_str());
    context_.last_mode = current_mode_;
    current_mode_ = new_mode;
  }
}

bool DriveModeManager::isManualEmergencyStopState() const
{
  return sm_->is(sml::state<DriveModeStateMachine::ManualEmergencyStop>);
}

bool DriveModeManager::isAutoEmergencyStopState() const
{
  return sm_->is(sml::state<DriveModeStateMachine::AutoEmergencyStop>);
}

bool DriveModeManager::isEmergencyStopState() const
{
  return isManualEmergencyStopState() || isAutoEmergencyStopState();
}

std::string DriveModeManager::getCurrentStateName() const
{
  if (sm_->is(sml::state<DriveModeStateMachine::RemoteNetwork>))
    return "RemoteNetwork";
  else if (sm_->is(sml::state<DriveModeStateMachine::ManualControl>))
    return "ManualControl";
  else if (sm_->is(sml::state<DriveModeStateMachine::ManualEmergencyStop>))
    return "ManualEmergencyStop";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoEmergencyStop>))
    return "AutoEmergencyStop";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoStandby>))
    return "AutoStandby";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoExecuting>))
    return "AutoExecuting";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverManual>))
    return "AutoTakeoverManual";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoTakeoverBrake>))
    return "AutoTakeoverBrake";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoDoneNormal>))
    return "AutoDoneNormal";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoDoneNear>))
    return "AutoDoneNear";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoDoneEstopNear>))
    return "AutoDoneEstopNear";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoCancelTakeover>))
    return "AutoCancelTakeover";
  else if (sm_->is(sml::state<DriveModeStateMachine::AutoCancelNewTask>))
    return "AutoCancelNewTask";
  else
    return "Unknown";
}

void DriveModeManager::reset()
{
  // 重置到初始状态
  current_mode_ = DriveMode::MANUAL_CONTROL;
  context_.auto_done_normal_pending_publish = false;
  context_.near_done_hold_until_sec = 0.0;
  context_.estop_done_hold_until_sec = 0.0;
  sm_ = std::make_unique<Sm>(DriveModeStateMachine::SmDef{context_});
  RCLCPP_INFO(logger_, "DriveModeManager reset to ManualControl");
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
