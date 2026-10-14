// 使用 SML 状态机的 Autoware 状态处理
// 本文件提供了基于状态机的驾驶模式管理，作为原有实现的替代方案

#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"
#include "pixmoving_chassis_interface/drive_mode_state_machine.hpp"
#include <std_msgs/msg/int8.hpp>

namespace pixmoving
{
namespace chassis
{
namespace interface
{

bool PixmovingChassisInterfaceNode::shouldRefreshRemainingDistanceForMode(DriveMode mode) const
{
  return mode == DriveMode::AUTO_EXECUTING ||
         mode == DriveMode::AUTO_TAKEOVER_MANUAL ||
         mode == DriveMode::AUTO_TAKEOVER_BRAKE;
}

void PixmovingChassisInterfaceNode::updateRemainingDistanceAndEstimateTime()
{
  const double time_since_last_update =
      (this->now() - mission_remaining_distance_time_received_time_).seconds();

  if (time_since_last_update < 5.0)
  {
    v2d_current_station_info_msg_.target_distance = std::round(mission_remaining_distance_);
    v2d_current_station_info_msg_.estimate_time = std::round(mission_remaining_time_);

    if (v2d_current_station_info_msg_.target_distance < 0)
      v2d_current_station_info_msg_.target_distance = 0;
    if (v2d_current_station_info_msg_.estimate_time < 0)
      v2d_current_station_info_msg_.estimate_time = 0;

    if (0 < v2d_current_station_info_msg_.estimate_time &&
        v2d_current_station_info_msg_.estimate_time < 1)
    {
      v2d_current_station_info_msg_.estimate_time = 1;
    }
    return;
  }

  RCLCPP_WARN_THROTTLE(
      this->get_logger(), *this->get_clock(), 10000,
      "Mission remaining data timeout (%.1fs), using fallback calculation",
      time_since_last_update);

  v2d_current_station_info_msg_.target_distance =
      v2d_current_station_info_msg_.task_distance - travel_distance_;

  if (v2d_current_station_info_msg_.target_distance <= 0)
    v2d_current_station_info_msg_.target_distance = 0;

  auto estimate_time = (v2d_current_station_info_msg_.target_distance / planning_speed_mph_);
  if (0 < estimate_time && estimate_time < 1)
  {
    v2d_current_station_info_msg_.estimate_time = 1;
  }
  else
  {
    v2d_current_station_info_msg_.estimate_time = std::round(estimate_time);
  }
}

/**
 * @brief 使用状态机的 Autoware 状态回调函数
 * @param msg Autoware 状态消息
 * 
 * 特点：
 * 1. 使用 SML 状态机管理状态转换
 * 2. 状态转换逻辑清晰，不会出现状态覆盖问题
 * 3. 易于维护和扩展
 * 4. 发布独立的驾驶模式话题
 */
void PixmovingChassisInterfaceNode::onAutowareStateWithStateMachine(
  const autoware_system_msgs::msg::AutowareState::SharedPtr msg)
{
  autoware_state_ = msg->state;
  double now_time = rclcpp::Clock(RCL_SYSTEM_TIME).now().seconds();

  // 准备状态机上下文
  DriveModeContext context;
  context.autoware_state = autoware_state_;
  context.vcu_brake_pedal_triggered = vcu_brake_pedal_req_fb_;
  context.vehicle_speed_kmh = vehicle_info_msg_.spd;
  context.target_distance_m = v2d_current_station_info_msg_.target_distance;
  context.autonomous_driving = autonomous_driving_;
  context.decentralization = decentralization_;
  context.is_estop = is_estop_;
  context.current_time = now_time;
  context.auto_last_time = auto_last_time_;
  context.station_distance = ChassisInterfaceUtils::calculateDistance(
    current_target_station_, last_current_target_station_);
  {
    std::lock_guard<std::mutex> lock(task_semantic_mutex_);
    context.has_active_task = has_task_semantic_ && !task_terminal_;
    context.new_task_received = pending_new_task_event_;
    pending_new_task_event_ = false;
  }
  context.resend_cancel_count = resend_cancle_count_;
  context.near_done_hold_until_sec = near_done_hold_until_sec_;
  context.estop_done_hold_until_sec = estop_done_hold_until_sec_;
  context.estop_done_distance_threshold_m = estop_done_distance_threshold_m_;
  context.estop_done_hold_sec = estop_done_hold_sec_;
  // DriveModeManager 内部会使用自身持有的 logger_；这里不保存 Node logger 指针，避免悬空引用
  context.logger = nullptr;

  // 特殊情况：规划状态下遥控器有速度，判断为接管
  if (autoware_state_ == msg->WAITING_FOR_ENGAGE)
  {
    if (plan_status_ && (vehicle_info_msg_.spd >= 1))
    {
      RCLCPP_INFO(this->get_logger(), 
        "Manual takeover detected: planning active but vehicle moving (speed=%.1f km/h)",
        static_cast<double>(vehicle_info_msg_.spd));
      auto_last_time_ = now_time;
      autonomous_driving_ = true;
      plan_status_ = false;
      context.autonomous_driving = true;
      context.auto_last_time = now_time;
    }
  }

  // ========== 第二阶段：使用状态机计算驾驶模式 ==========
  
  DriveMode new_mode = drive_mode_manager_->update(autoware_state_, context);
  
  // 更新成员变量（从状态机同步回来）
  autonomous_driving_ = context.autonomous_driving;
  auto_last_time_ = context.auto_last_time;
  resend_cancle_count_ = context.resend_cancel_count;
  near_done_hold_until_sec_ = context.near_done_hold_until_sec;
  estop_done_hold_until_sec_ = context.estop_done_hold_until_sec;
  
  // 设置驾驶模式
  vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(new_mode);

  // ========== 第三阶段：状态变化日志和发布 ==========
  
  // 记录 Autoware 状态变化
  if (last_autoware_mode_ != autoware_state_)
  {
    RCLCPP_INFO(this->get_logger(), "Autoware state changed to %d", autoware_state_);
    last_autoware_mode_ = autoware_state_;
  }

  // 记录驾驶模式变化并发布相关消息
  if (last_pixmoving_mode_ != vehicle_info_msg_.mode)
  {
    RCLCPP_INFO(this->get_logger(), "Drive mode changed: %s -> %s (StateMachine: %s)",
                ChassisInterfaceUtils::driveModeToString(last_pixmoving_mode_).c_str(),
                ChassisInterfaceUtils::driveModeToString(vehicle_info_msg_.mode).c_str(),
                drive_mode_manager_->getCurrentStateName().c_str());
    
    // 发布附近完成状态
    std_msgs::msg::UInt8 msg_near;
    if (vehicle_info_msg_.mode == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_NEAR))
    {
      msg_near.data = 1;  // 触发附近完成
    }
    else
    {
      msg_near.data = 0;  // 取消附近完成
    }
    nearby_finish_pub_->publish(msg_near);
    
    last_pixmoving_mode_ = vehicle_info_msg_.mode;
  }

  if (new_mode == DriveMode::AUTO_DONE_NORMAL ||
      new_mode == DriveMode::AUTO_DONE_NEAR ||
      new_mode == DriveMode::AUTO_CANCEL_TAKEOVER ||
      new_mode == DriveMode::AUTO_DONE_ESTOP_NEAR)
  {
    markTaskTerminal();
  }

  // ========== 第四阶段：更新 Autoware 信息和任务距离/时间（保持原有逻辑） ==========
  
  // 更新定位状态
  if (autoware_state_ == msg->INITIALIZING)
  {
    autoware_info_msg_.ad_located = false;
    autoware_info_msg_.ipc_to_ch = false;
  }
  else
  {
    autoware_info_msg_.ad_located = true;
    autoware_info_msg_.ipc_to_ch = true;
  }

  // 更新任务剩余距离和时间
  if (shouldRefreshRemainingDistanceForMode(new_mode))
  {
    updateRemainingDistanceAndEstimateTime();
    
    // 更新自动驾驶时间戳
    if (new_mode == DriveMode::AUTO_EXECUTING)
    {
      auto_last_time_ = now_time;
      autonomous_driving_ = true;
      plan_status_ = false;
    }
  }
  else if (autoware_state_ == msg->ARRIVED_GOAL)
  {
    // 到达终点时清零
    v2d_current_station_info_msg_.estimate_time = 0;
    v2d_current_station_info_msg_.target_distance = 0;
    v2d_current_station_info_msg_.task_distance = 0;
  }

  // 发布当前站点信息
  if (autoware_state_ == msg->DRIVING || 
      autoware_state_ == msg->ARRIVED_GOAL ||
      autoware_state_ == msg->WAITING_FOR_ENGAGE || 
      autoware_state_ == msg->PLANNING)
  {
    current_station_info_pub_->publish(v2d_current_station_info_msg_);
  }
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
