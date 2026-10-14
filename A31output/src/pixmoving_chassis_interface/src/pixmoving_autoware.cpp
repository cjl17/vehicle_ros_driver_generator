#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

namespace pixmoving
{
namespace chassis
{
namespace interface
{

void PixmovingChassisInterfaceNode::onAutowareState(const autoware_system_msgs::msg::AutowareState::SharedPtr msg)
{
  autoware_state_ = msg->state;
  double now_time = rclcpp::Clock(RCL_SYSTEM_TIME).now().seconds();

  /**
   * 车辆驾驶模式:
   * 1:手动模式, 2:远程模式; 3:紧急停止状态; -1:未知;
   * 4:自驾模式 - 待命状态(遥控器放权，自驾等待执行)
   * 5:自驾模式 - 执行状态;
   * 6:自驾模式 - 遥控接管; 7:自驾模式 - 刹车接管;
   * 8:自驾模式 - 正常完成; 9:自驾模式 - 附近完成;
   * 10:自驾模式 - 接管取消; 11:自驾模式 - 新任务取消;
   * 12:自驾模式 - 终点附近急停结束;
   */
  if (autoware_state_ == msg->DRIVING)
  {
    // 如果触发刹车踏板且上一个模式是执行状态，则切换到刹车接管模式
    if (vcu_brake_pedal_req_fb_ &&
        last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_EXECUTING))
    {
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_BRAKE);
    }
    else
    {
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_EXECUTING);
    }
    auto_last_time_ = now_time;
    autonomous_driving_ = true;
    plan_status_ = false;
  }
  else if (autoware_state_ == msg->WAITING_FOR_ROUTE || autoware_state_ == msg->PLANNING ||
           autoware_state_ == msg->INITIALIZING)
  {
    // 站点重复发情况处理
    if (ChassisInterfaceUtils::calculateDistance(current_target_station_, last_current_target_station_) > 5.0)
    {
      if (last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_EXECUTING) ||
          last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_MANUAL) ||
          last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_BRAKE))
      {
        // 10-自驾模式-新任务取消: 上一个状态是自驾接管或自驾运行, 且下发的站点不是同一个
        autonomous_driving_ = false;
        resend_cancle_count_ = 3;
      }
    }
    else
    {
      if (last_staion_name != v2d_current_station_info_msg_.current_station.name)
      {
        RCLCPP_INFO(this->get_logger(), "下发重复的任务: [%f]-[%s] ",
                    ChassisInterfaceUtils::calculateDistance(current_target_station_, last_current_target_station_),
                    v2d_current_station_info_msg_.current_station.name.c_str());
      }
    }
  }
  else if (autoware_state_ == msg->WAITING_FOR_ENGAGE)
  {
    if (plan_status_ && (vehicle_info_msg_.spd >= 1))
    {
      // 下发规划为执行，但是遥控有速度: 判断进入自动驾驶接管模式
      auto_last_time_ = now_time;
      autonomous_driving_ = true;
      plan_status_ = false;
    }

    if (autonomous_driving_ && (now_time - auto_last_time_ <= 300.0))
    {
      // 自动驾驶状态: 遥控接管状态
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_MANUAL);
    }

    if (autonomous_driving_ && (now_time - auto_last_time_ > 300.0))
    {
      // 自动驾驶-接管时间过长, 接管取消
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_CANCEL_TAKEOVER);
    }

    // 自动驾驶-接管时间过长,变成遥控驾驶
    if (autonomous_driving_ && (now_time - auto_last_time_ > 300.5))
    {
      autonomous_driving_ = false;
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::MANUAL_CONTROL);
    }

    // 站点附近完成任务=遥控接管模式+离站点距离<50m+车速为0
    if (autonomous_driving_ &&
        vehicle_info_msg_.mode == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_MANUAL) &&
        vehicle_info_msg_.spd <= 1 && v2d_current_station_info_msg_.target_distance <= 50)
    {
      autonomous_driving_ = false;
      near_done_count_ = 3;
    }
  }
  else if (autoware_state_ == msg->ARRIVED_GOAL)
  {  // 到达站点
    // 8:自驾模式 - 完成;
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_NORMAL);
  }
  else
  {
    autonomous_driving_ = false;
  }

  // 处理刹车接管模式：仅当上一个驾驶模式为 5:自驾模式-执行状态，且 vcu_brake_pedal_req_fb 触发为 1 时，
  // 才切换为 7:自驾模式-刹车接管（在非 DRIVING 状态下也检查）
  if (autoware_state_ != msg->DRIVING && 
      vcu_brake_pedal_req_fb_ &&
      last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_EXECUTING))
  {
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_BRAKE);
  }

  // 如果当前模式是刹车接管模式，则不应被覆盖
  const int8_t current_mode = vehicle_info_msg_.mode;
  const int8_t brake_takeover_mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_BRAKE);
  const bool is_brake_takeover = (current_mode == brake_takeover_mode);
  bool has_active_task = false;
  {
    std::lock_guard<std::mutex> lock(task_semantic_mutex_);
    has_active_task = has_task_semantic_ && !task_terminal_;
  }
  const bool should_emit_estop_done_near =
      is_estop_ &&
      has_active_task &&
      vehicle_info_msg_.spd <= 1 &&
      v2d_current_station_info_msg_.target_distance <= estop_done_distance_threshold_m_ &&
      (current_mode == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_MANUAL) ||
       is_brake_takeover);
  if (should_emit_estop_done_near && estop_done_count_ == 0 &&
      last_pixmoving_mode_ != ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_ESTOP_NEAR))
  {
    estop_done_count_ = 3;
  }

  // 遥控器没有放权，也不是自动驾驶状态 - 遥控模式
  if (!autonomous_driving_ && !decentralization_ && !is_brake_takeover)
  {
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::MANUAL_CONTROL);
  }
  // 遥控器放权，也不是自动驾驶状态 - 自驾模式 - 待命状态
  if (!autonomous_driving_ && decentralization_ && !is_brake_takeover)
  {
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_STANDBY);
  }

  // 紧急状态
  if (is_estop_)
  {
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::EMERGENCY_STOP);
  }

  if (resend_cancle_count_ > 0)
  {
    // 10:自驾模式-新任务取消
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_CANCEL_NEW_TASK);
    resend_cancle_count_--;
  }

  if (near_done_count_ > 0)
  {
    // 9:自驾模式 - 附近完成
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_NEAR);
    near_done_count_--;
  }

  if (estop_done_count_ > 0)
  {
    // 12:自驾模式 - 终点附近急停结束
    vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_ESTOP_NEAR);
    estop_done_count_--;
  }

  // 防止模式保持为 -1（未知状态），如果仍然是 -1，根据当前状态设置默认模式
  if (vehicle_info_msg_.mode == -1)
  {
    if (is_estop_)
    {
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::EMERGENCY_STOP);
    }
    else if (!decentralization_)
    {
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::MANUAL_CONTROL);
    }
    else
    {
      vehicle_info_msg_.mode = ChassisInterfaceUtils::toInt8(DriveMode::AUTO_STANDBY);
    }
  }

  if (last_autoware_mode_ != autoware_state_)
  {
    RCLCPP_INFO(this->get_logger(), "Autoware state changed to %d ", autoware_state_);
    last_autoware_mode_ = autoware_state_;
  }

  if (last_pixmoving_mode_ != vehicle_info_msg_.mode)
  {
    RCLCPP_INFO(this->get_logger(), "Pixmoving state changed to %s",
                ChassisInterfaceUtils::driveModeToString(vehicle_info_msg_.mode).c_str());
    if (vehicle_info_msg_.mode == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_NEAR))
    {
      std_msgs::msg::UInt8 msg_near;
      msg_near.data = 1;  // 触发附近完成
      nearby_finish_pub_->publish(msg_near);
    }
    else
    {
      std_msgs::msg::UInt8 msg_near;
      msg_near.data = 0;  // 取消附近完成
      nearby_finish_pub_->publish(msg_near);
    }
    last_pixmoving_mode_ = vehicle_info_msg_.mode;
  }

  // 等待下发站点 -> 等待engage -> 运动中 -> 到达终点 -> 等待下发站点
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

  if (autoware_state_ == msg->DRIVING)
  {  // 运动中
    // 使用从 /planning/mission_remaining_distance_time 话题接收的数据
    // 检查数据是否有效（在5秒内接收到的数据认为是有效的）
    const double time_since_last_update =
        (this->now() - mission_remaining_distance_time_received_time_).seconds();
    
    if (time_since_last_update < 5.0)
    {
      // 使用订阅到的剩余距离和时间
      v2d_current_station_info_msg_.target_distance = std::round(mission_remaining_distance_);
      v2d_current_station_info_msg_.estimate_time = std::round(mission_remaining_time_);
      
      // 确保值不为负数
      if (v2d_current_station_info_msg_.target_distance < 0)
        v2d_current_station_info_msg_.target_distance = 0;
      if (v2d_current_station_info_msg_.estimate_time < 0)
        v2d_current_station_info_msg_.estimate_time = 0;
      
      // 快到时，默认1分钟
      if (0 < v2d_current_station_info_msg_.estimate_time && v2d_current_station_info_msg_.estimate_time < 1)
      {
        v2d_current_station_info_msg_.estimate_time = 1;
      }
    }
    else
    {
      // 数据过期，回退到原来的计算方式
      v2d_current_station_info_msg_.target_distance =
          v2d_current_station_info_msg_.task_distance - travel_distance_;  // 到达目标的剩余距离

      if (v2d_current_station_info_msg_.target_distance <= 0)
        v2d_current_station_info_msg_.target_distance = 0;

      auto estimate_time = (v2d_current_station_info_msg_.target_distance / planning_speed_mph_);

      // 快到时，默认1分钟
      if (0 < estimate_time && estimate_time < 1)
      {
        v2d_current_station_info_msg_.estimate_time = 1;
      }
      else
      {
        v2d_current_station_info_msg_.estimate_time = std::round(estimate_time);  // 到达目标的剩余时间
      }
    }
  }
  else if (autoware_state_ == msg->ARRIVED_GOAL)  // 到达站点
  {
    // 到达终点时
    v2d_current_station_info_msg_.estimate_time = 0;
    v2d_current_station_info_msg_.target_distance = 0;
    v2d_current_station_info_msg_.task_distance = 0;
  }

  if (autoware_state_ == msg->DRIVING || autoware_state_ == msg->ARRIVED_GOAL ||
      autoware_state_ == msg->WAITING_FOR_ENGAGE || autoware_state_ == msg->PLANNING)
  {
    current_station_info_pub_->publish(v2d_current_station_info_msg_);
  }
}

void PixmovingChassisInterfaceNode::onVelocityLimit(
    const autoware_internal_planning_msgs::msg::VelocityLimit::SharedPtr msg)
{
  planning_speed_mph_ = msg->max_velocity;
  if (planning_speed_mph_ == 0.0)
    planning_speed_mph_ = 0.1;
}

void PixmovingChassisInterfaceNode::onMissionRemainingDistanceTime(
    const autoware_internal_msgs::msg::MissionRemainingDistanceTime::SharedPtr msg)
{
  mission_remaining_distance_ = msg->remaining_distance;
  mission_remaining_time_ = msg->remaining_time;
  mission_remaining_distance_time_received_time_ = this->now();

  if (!use_state_machine_drive_mode_)
  {
    return;
  }

  const int8_t current_mode = vehicle_info_msg_.mode;
  if (shouldRefreshRemainingDistanceForMode(static_cast<DriveMode>(current_mode)))
  {
    updateRemainingDistanceAndEstimateTime();

    if (autoware_state_ == autoware_system_msgs::msg::AutowareState::DRIVING ||
        autoware_state_ == autoware_system_msgs::msg::AutowareState::WAITING_FOR_ENGAGE)
    {
      current_station_info_pub_->publish(v2d_current_station_info_msg_);
    }
  }
}

void PixmovingChassisInterfaceNode::onVelocityReport(
    const autoware_vehicle_msgs::msg::VelocityReport::SharedPtr msg)
{
  // 处理速度报告的实现
  v2d_vehicle_info_msg_.vehicle_speed_km_per_h = std::round(msg->longitudinal_velocity * 3.6);
}

void PixmovingChassisInterfaceNode::onLocalTransformProbability(
    const autoware_internal_debug_msgs::msg::Float32Stamped::SharedPtr msg)
{
  latest_ndt_pos_q_ = msg->data;
  last_ndt_pos_q_time_ = this->now();
  autoware_info_msg_.pos_q = msg->data;
}

void PixmovingChassisInterfaceNode::onEmergency(const tier4_external_api_msgs::msg::Emergency::SharedPtr msg)
{
  // 处理紧急报告的代码
  emergency_report_ptr_ = msg;
  emergency_report_received_time_ = this->now();
}

void PixmovingChassisInterfaceNode::onOperationModeState(
    const autoware_adapi_v1_msgs::msg::OperationModeState::SharedPtr msg)
{
  // 处理操作模式状态的代码
  operation_mode_state_ptr_ = msg;
}

void PixmovingChassisInterfaceNode::onControlModeReport(
    const autoware_vehicle_msgs::msg::ControlModeReport::SharedPtr msg)
{
  // 处理控制模式报告的代码
  auto current_time = this->now();
  const double current_time_delta_time_s = (current_time - emergency_report_received_time_).seconds();

  if (emergency_report_ptr_ == nullptr || current_time_delta_time_s > 1)
  {
    // RCLCPP_ERROR(this->get_logger(), "current_time_delta_time_s timeout=%f", current_time_delta_time_s);
    RCLCPP_ERROR_THROTTLE(this->get_logger(), *this->get_clock(),
                          5000,  // 单位：毫秒
                          "current_time_delta_time_s timeout=%f", current_time_delta_time_s);
    return;
  }

  if (emergency_report_ptr_->emergency)
  {
    v2d_vehicle_info_msg_.driving_mode = v2d_vehicle_info_msg_.ENERGENCY;
    return;
  }

  if (msg->mode == msg->AUTONOMOUS)
  {
    decentralization_ = true;
  }
  else
  {
    decentralization_ = false;
  }

  if (msg->mode == msg->AUTONOMOUS || msg->mode == msg->AUTONOMOUS_STEER_ONLY ||
      msg->mode == msg->AUTONOMOUS_VELOCITY_ONLY)
  {
    if (operation_mode_state_ptr_->mode == autoware_adapi_v1_msgs::msg::OperationModeState::AUTONOMOUS)
    {
      v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::AUTOPILOT_TASK;
    }
    else if (operation_mode_state_ptr_->mode == autoware_adapi_v1_msgs::msg::OperationModeState::STOP)
    {
      v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::AUTOPILOT_PENDING;
    }
    else if (operation_mode_state_ptr_->mode == autoware_adapi_v1_msgs::msg::OperationModeState::LOCAL)
    {
      v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::REMOTE;
    }
    else if (operation_mode_state_ptr_->mode == autoware_adapi_v1_msgs::msg::OperationModeState::REMOTE)
    {
      v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::REMOTE;
    }
    else
    {
      v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::AUTOPILOT_PENDING;
    }
  }
  else if (msg->mode == msg->MANUAL || msg->mode == msg->DISENGAGED)
  {
    v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::MANUAL;
  }
  else
  {
    v2d_vehicle_info_msg_.driving_mode = pixmoving_hmi_msgs::msg::V2dVehicleInfo::AUTOPILOT_PENDING;
  }
}

void PixmovingChassisInterfaceNode::onLocalizationPose(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  localization_pose_ptr_ = msg;
  localization_pose_received_time_ = this->now();
  // 更新 NDT 定位位置信息
  autoware_info_msg_.ndt_pose = msg->pose;
  // isTaskGoal(); // 关闭按照定位显示当前站点（如需开启，可放开此调用）
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
