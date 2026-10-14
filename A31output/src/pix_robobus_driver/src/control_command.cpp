#include <pix_robobus_driver/control_command.hpp>

namespace pix_robobus_driver
{
namespace control_command
{
ControlCommand::ControlCommand(const rclcpp::NodeOptions & node_options) 
: Node("control_command", node_options),
updater_(this)
{
  // init delay_recording_init_list is_pix_interface_init_list
  av_aeb_ctrl_delay_.count_eorro = 0;
  av_aeb_ctrl_delay_.count_waring = 0;
  av_drive_ctrl_delay_.count_eorro = 0;
  av_drive_ctrl_delay_.count_waring = 0;
  av_brake_ctrl_delay_.count_eorro = 0;
  av_brake_ctrl_delay_.count_waring = 0;
  av_steer_ctrl_delay_.count_eorro = 0;
  av_steer_ctrl_delay_.count_waring = 0;
  av_vehicle_ctrl_delay_.count_eorro = 0;
  av_vehicle_ctrl_delay_.count_waring = 0;
  av_wheel_torque_ctrl_delay_.count_eorro = 0;
  av_wheel_torque_ctrl_delay_.count_waring = 0;
  av_manual_spd_limit_delay_.count_eorro = 0;
  av_manual_spd_limit_delay_.count_waring = 0;
  av_self_driving_work_st_delay_.count_eorro = 0;
  av_self_driving_work_st_delay_.count_waring = 0;
  auto_message_delay_.count_eorro = 0;
  auto_message_delay_.count_waring = 0;
  remote_message_delay_.count_eorro = 0;
  remote_message_delay_.count_waring = 0;
  acu_sys_time_delay_.count_eorro = 0;
  acu_sys_time_delay_.count_waring = 0;
  av_message1_delay_.count_eorro = 0;
  av_message1_delay_.count_waring = 0;
  av_message2_delay_.count_eorro = 0;
  av_message2_delay_.count_waring = 0;

  av_aeb_ctrl_issub_ = false;
  av_drive_ctrl_issub_ = false;
  av_brake_ctrl_issub_ = false;
  av_steer_ctrl_issub_ = false;
  av_vehicle_ctrl_issub_ = false;
  av_wheel_torque_ctrl_issub_ = false;
  av_manual_spd_limit_issub_ = false;
  av_self_driving_work_st_issub_ = false;
  auto_message_issub_ = false;
  remote_message_issub_ = false;
  acu_sys_time_issub_ = false;
  av_message1_issub_ = false;
  av_message2_issub_ = false;


  float pix_interface_driver_period_ms =
    declare_parameter("pix_interface_driver_period_ms", 50.0);
  param_.timeout_threshold_ms.pix_interface_driver_eorro  = pix_interface_driver_period_ms*ERROR_THRESHOLD;
  param_.timeout_threshold_ms.pix_interface_driver_warn  = pix_interface_driver_period_ms*WARNING_THRESHOLD;

  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  // initialize msg received time, make reservation of data size - msg_reveived_timestamp_instance_list
  av_aeb_ctrl_received_time_ = this->now();
  av_drive_ctrl_received_time_ = this->now();
  av_brake_ctrl_received_time_ = this->now();
  av_steer_ctrl_received_time_ = this->now();
  av_vehicle_ctrl_received_time_ = this->now();
  av_wheel_torque_ctrl_received_time_ = this->now();
  av_manual_spd_limit_received_time_ = this->now();
  av_self_driving_work_st_received_time_ = this->now();
  auto_message_received_time_ = this->now();
  remote_message_received_time_ = this->now();
  acu_sys_time_received_time_ = this->now();
  av_message1_received_time_ = this->now();
  av_message2_received_time_ = this->now();


  using std::placeholders::_1;

  // Diagnostics Updater
  updater_.setHardwareID("pix_robobus_driver-ControlCommand");
  updater_.add("delayed_alarm", this, &ControlCommand::onDelayedAlarm);

  /* subscriber */
  {
    // from robobus driver autoware interface - subscribe_instance_list
      av_aeb_ctrl_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvAebCtrl>("/pix_robobus/av_aeb_ctrl", 10, std::bind(&ControlCommand::callbackAvAebCtrl, this, _1));
    av_drive_ctrl_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvDriveCtrl>("/pix_robobus/av_drive_ctrl", 10, std::bind(&ControlCommand::callbackAvDriveCtrl, this, _1));
    av_brake_ctrl_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvBrakeCtrl>("/pix_robobus/av_brake_ctrl", 10, std::bind(&ControlCommand::callbackAvBrakeCtrl, this, _1));
    av_steer_ctrl_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvSteerCtrl>("/pix_robobus/av_steer_ctrl", 10, std::bind(&ControlCommand::callbackAvSteerCtrl, this, _1));
    av_vehicle_ctrl_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvVehicleCtrl>("/pix_robobus/av_vehicle_ctrl", 10, std::bind(&ControlCommand::callbackAvVehicleCtrl, this, _1));
    av_wheel_torque_ctrl_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvWheelTorqueCtrl>("/pix_robobus/av_wheel_torque_ctrl", 10, std::bind(&ControlCommand::callbackAvWheelTorqueCtrl, this, _1));
    av_manual_spd_limit_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvManualSpdLimit>("/pix_robobus/av_manual_spd_limit", 10, std::bind(&ControlCommand::callbackAvManualSpdLimit, this, _1));
    av_self_driving_work_st_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvSelfDrivingWorkSt>("/pix_robobus/av_self_driving_work_st", 10, std::bind(&ControlCommand::callbackAvSelfDrivingWorkSt, this, _1));
    auto_message_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AutoMessage>("/pix_robobus/auto_message", 10, std::bind(&ControlCommand::callbackAutoMessage, this, _1));
    remote_message_sub_ = create_subscription<pix_robobus_driver_msgs::msg::RemoteMessage>("/pix_robobus/remote_message", 10, std::bind(&ControlCommand::callbackRemoteMessage, this, _1));
    acu_sys_time_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AcuSysTime>("/pix_robobus/acu_sys_time", 10, std::bind(&ControlCommand::callbackAcuSysTime, this, _1));
    av_message1_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvMessage1>("/pix_robobus/av_message1", 10, std::bind(&ControlCommand::callbackAvMessage1, this, _1));
    av_message2_sub_ = create_subscription<pix_robobus_driver_msgs::msg::AvMessage2>("/pix_robobus/av_message2", 10, std::bind(&ControlCommand::callbackAvMessage2, this, _1));

  }

  /* publisher */
  {
    // to socketcan drivier
    can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("output/can_tx", rclcpp::QoS{500});
  }

  {
    // timer
    timer_ = rclcpp::create_timer(
      this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
      std::bind(&ControlCommand::timerCallback, this));
  }
}

// calback functions -- callback_functions_list


void ControlCommand::callbackAvAebCtrl(const pix_robobus_driver_msgs::msg::AvAebCtrl::ConstSharedPtr & msg)
{
  av_aeb_ctrl_issub_ = true;
  av_aeb_ctrl_received_time_ = this->now();
  av_aeb_ctrl_ptr_ = msg;
  av_aeb_ctrl_parse_.Reset();
  av_aeb_ctrl_parse_.UpdateData(msg->acu_aeb_work_sta, msg->acu_aeb_active_request, msg->acu_fcw_active_request, msg->acu_aeb_brake_en, msg->acu_aeb_brake_pedal_target, msg->acu_aeb_brake_life_sig, msg->acu_check_sum121);
  can_msgs::msg::Frame av_aeb_ctrl_can_msg;
  av_aeb_ctrl_can_msg.header.stamp = msg->header.stamp;
  av_aeb_ctrl_can_msg.dlc = 8;
  av_aeb_ctrl_can_msg.id = av_aeb_ctrl_parse_.ID;
  av_aeb_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_aeb_ctrl_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_aeb_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_aeb_ctrl_can_msg);
}

    

void ControlCommand::callbackAvDriveCtrl(const pix_robobus_driver_msgs::msg::AvDriveCtrl::ConstSharedPtr & msg)
{
  av_drive_ctrl_issub_ = true;
  av_drive_ctrl_received_time_ = this->now();
  av_drive_ctrl_ptr_ = msg;
  av_drive_ctrl_parse_.Reset();
  av_drive_ctrl_parse_.UpdateData(msg->acu_chassis_driver_en_ctrl, msg->acu_chassis_driver_mode_ctrl, msg->acu_chassis_gear_ctrl, msg->acu_chassis4_wd_mode_ctrl, msg->acu_chassis_speed_ctrl, msg->acu_chassis_throttle_pdl_target, msg->acu_drive_life_sig, msg->acu_check_sum130);
  can_msgs::msg::Frame av_drive_ctrl_can_msg;
  av_drive_ctrl_can_msg.header.stamp = msg->header.stamp;
  av_drive_ctrl_can_msg.dlc = 8;
  av_drive_ctrl_can_msg.id = av_drive_ctrl_parse_.ID;
  av_drive_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_drive_ctrl_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_drive_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_drive_ctrl_can_msg);
}

    

void ControlCommand::callbackAvBrakeCtrl(const pix_robobus_driver_msgs::msg::AvBrakeCtrl::ConstSharedPtr & msg)
{
  av_brake_ctrl_issub_ = true;
  av_brake_ctrl_received_time_ = this->now();
  av_brake_ctrl_ptr_ = msg;
  av_brake_ctrl_parse_.Reset();
  av_brake_ctrl_parse_.UpdateData(msg->acu_chassis_brake_en, msg->acu_chassis_brake_lamp_ctrl, msg->acu_chassis_aeb_ctrl, msg->acu_chassis_brake_pdl_target, msg->acu_chassis_epb_ctrl, msg->acu_brake_life_sig, msg->acu_check_sum131);
  can_msgs::msg::Frame av_brake_ctrl_can_msg;
  av_brake_ctrl_can_msg.header.stamp = msg->header.stamp;
  av_brake_ctrl_can_msg.dlc = 8;
  av_brake_ctrl_can_msg.id = av_brake_ctrl_parse_.ID;
  av_brake_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_brake_ctrl_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_brake_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_brake_ctrl_can_msg);
}

    

void ControlCommand::callbackAvSteerCtrl(const pix_robobus_driver_msgs::msg::AvSteerCtrl::ConstSharedPtr & msg)
{
  av_steer_ctrl_issub_ = true;
  av_steer_ctrl_received_time_ = this->now();
  av_steer_ctrl_ptr_ = msg;
  av_steer_ctrl_parse_.Reset();
  av_steer_ctrl_parse_.UpdateData(msg->acu_chassis_steer_en_ctrl, msg->acu_chassis_steer_mode_ctrl, msg->acu_chassis_steer_angle_target, msg->acu_chassis_steer_angle_rear_target, msg->acu_chassis_steer_angle_speed_ctrl, msg->acu_steer_life_sig, msg->acu_check_sum132);
  can_msgs::msg::Frame av_steer_ctrl_can_msg;
  av_steer_ctrl_can_msg.header.stamp = msg->header.stamp;
  av_steer_ctrl_can_msg.dlc = 8;
  av_steer_ctrl_can_msg.id = av_steer_ctrl_parse_.ID;
  av_steer_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_steer_ctrl_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_steer_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_steer_ctrl_can_msg);
}

    

void ControlCommand::callbackAvVehicleCtrl(const pix_robobus_driver_msgs::msg::AvVehicleCtrl::ConstSharedPtr & msg)
{
  av_vehicle_ctrl_issub_ = true;
  av_vehicle_ctrl_received_time_ = this->now();
  av_vehicle_ctrl_ptr_ = msg;
  av_vehicle_ctrl_parse_.Reset();
  av_vehicle_ctrl_parse_.UpdateData(msg->acu_vehicle_pos_lamp_ctrl, msg->acu_vehicle_head_lamp_ctrl, msg->acu_vehicle_left_lamp_ctrl, msg->acu_vehicle_right_lamp_ctrl, msg->acu_vehicle_high_beam_ctrl, msg->acu_vehicle_fog_lamp_ctrl, msg->acu_vehicle_body_light_ctrl, msg->acu_vehicle_read_light_ctrl, msg->acu_vehicle_voice, msg->acu_vehicle_wipers_ctrl, msg->acu_vehicle_door_ctrl, msg->acu_vehicle_window_ctrl, msg->acu_chassis_speed_limite_mode, msg->acu_vehicle_horn_ctrl, msg->acu_vehicle_spray_ctrl, msg->acu_chassis_speed_limite_val, msg->acu_check_sum_en);
  can_msgs::msg::Frame av_vehicle_ctrl_can_msg;
  av_vehicle_ctrl_can_msg.header.stamp = msg->header.stamp;
  av_vehicle_ctrl_can_msg.dlc = 8;
  av_vehicle_ctrl_can_msg.id = av_vehicle_ctrl_parse_.ID;
  av_vehicle_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_vehicle_ctrl_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_vehicle_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_vehicle_ctrl_can_msg);
}

    

void ControlCommand::callbackAvWheelTorqueCtrl(const pix_robobus_driver_msgs::msg::AvWheelTorqueCtrl::ConstSharedPtr & msg)
{
  av_wheel_torque_ctrl_issub_ = true;
  av_wheel_torque_ctrl_received_time_ = this->now();
  av_wheel_torque_ctrl_ptr_ = msg;
  av_wheel_torque_ctrl_parse_.Reset();
  av_wheel_torque_ctrl_parse_.UpdateData(msg->acu_motor_torque_lf_ctrl, msg->acu_motor_torque_rf_ctrl, msg->acu_motor_torque_lr_ctrl, msg->acu_motor_torque_rr_ctrl);
  can_msgs::msg::Frame av_wheel_torque_ctrl_can_msg;
  av_wheel_torque_ctrl_can_msg.header.stamp = msg->header.stamp;
  av_wheel_torque_ctrl_can_msg.dlc = 8;
  av_wheel_torque_ctrl_can_msg.id = av_wheel_torque_ctrl_parse_.ID;
  av_wheel_torque_ctrl_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_wheel_torque_ctrl_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_wheel_torque_ctrl_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_wheel_torque_ctrl_can_msg);
}

    

void ControlCommand::callbackAvManualSpdLimit(const pix_robobus_driver_msgs::msg::AvManualSpdLimit::ConstSharedPtr & msg)
{
  av_manual_spd_limit_issub_ = true;
  av_manual_spd_limit_received_time_ = this->now();
  av_manual_spd_limit_ptr_ = msg;
  av_manual_spd_limit_parse_.Reset();
  av_manual_spd_limit_parse_.UpdateData(msg->acu_aeb_usable_manual_limit, msg->acu_aeb_unusable_manual_limit, msg->acu_aeb_usable_manual_spd_set, msg->acu_aeb_unusable_manual_spd_set);
  can_msgs::msg::Frame av_manual_spd_limit_can_msg;
  av_manual_spd_limit_can_msg.header.stamp = msg->header.stamp;
  av_manual_spd_limit_can_msg.dlc = 8;
  av_manual_spd_limit_can_msg.id = av_manual_spd_limit_parse_.ID;
  av_manual_spd_limit_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_manual_spd_limit_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_manual_spd_limit_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_manual_spd_limit_can_msg);
}

    

void ControlCommand::callbackAvSelfDrivingWorkSt(const pix_robobus_driver_msgs::msg::AvSelfDrivingWorkSt::ConstSharedPtr & msg)
{
  av_self_driving_work_st_issub_ = true;
  av_self_driving_work_st_received_time_ = this->now();
  av_self_driving_work_st_ptr_ = msg;
  av_self_driving_work_st_parse_.Reset();
  av_self_driving_work_st_parse_.UpdateData(msg->acu_adcu1_sys_temp, msg->acu_adcu2_sys_temp, msg->acu_self_driving_run_st, msg->acu_remote_control_mode, msg->acu_calibration_mode);
  can_msgs::msg::Frame av_self_driving_work_st_can_msg;
  av_self_driving_work_st_can_msg.header.stamp = msg->header.stamp;
  av_self_driving_work_st_can_msg.dlc = 8;
  av_self_driving_work_st_can_msg.id = av_self_driving_work_st_parse_.ID;
  av_self_driving_work_st_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_self_driving_work_st_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_self_driving_work_st_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_self_driving_work_st_can_msg);
}

    

void ControlCommand::callbackAutoMessage(const pix_robobus_driver_msgs::msg::AutoMessage::ConstSharedPtr & msg)
{
  auto_message_issub_ = true;
  auto_message_received_time_ = this->now();
  auto_message_ptr_ = msg;
  auto_message_parse_.Reset();
  auto_message_parse_.UpdateData(msg->auto_drive_mode, msg->auto_heartbeat);
  can_msgs::msg::Frame auto_message_can_msg;
  auto_message_can_msg.header.stamp = msg->header.stamp;
  auto_message_can_msg.dlc = 8;
  auto_message_can_msg.id = auto_message_parse_.ID;
  auto_message_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = auto_message_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    auto_message_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(auto_message_can_msg);
}

    

void ControlCommand::callbackRemoteMessage(const pix_robobus_driver_msgs::msg::RemoteMessage::ConstSharedPtr & msg)
{
  remote_message_issub_ = true;
  remote_message_received_time_ = this->now();
  remote_message_ptr_ = msg;
  remote_message_parse_.Reset();
  remote_message_parse_.UpdateData(msg->remote_drive_mode, msg->remote_heartbeat);
  can_msgs::msg::Frame remote_message_can_msg;
  remote_message_can_msg.header.stamp = msg->header.stamp;
  remote_message_can_msg.dlc = 8;
  remote_message_can_msg.id = remote_message_parse_.ID;
  remote_message_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = remote_message_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    remote_message_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(remote_message_can_msg);
}

    

void ControlCommand::callbackAcuSysTime(const pix_robobus_driver_msgs::msg::AcuSysTime::ConstSharedPtr & msg)
{
  acu_sys_time_issub_ = true;
  acu_sys_time_received_time_ = this->now();
  acu_sys_time_ptr_ = msg;
  acu_sys_time_parse_.Reset();
  acu_sys_time_parse_.UpdateData(msg->sys_time_year, msg->sys_time_month, msg->sys_time_day, msg->sys_time_hour, msg->sys_time_minute, msg->sys_time_second);
  can_msgs::msg::Frame acu_sys_time_can_msg;
  acu_sys_time_can_msg.header.stamp = msg->header.stamp;
  acu_sys_time_can_msg.dlc = 8;
  acu_sys_time_can_msg.id = acu_sys_time_parse_.ID;
  acu_sys_time_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = acu_sys_time_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    acu_sys_time_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(acu_sys_time_can_msg);
}

    

void ControlCommand::callbackAvMessage1(const pix_robobus_driver_msgs::msg::AvMessage1::ConstSharedPtr & msg)
{
  av_message1_issub_ = true;
  av_message1_received_time_ = this->now();
  av_message1_ptr_ = msg;
  av_message1_parse_.Reset();
  av_message1_parse_.UpdateData(msg->defrost_ctrl, msg->air_cod_ctrl, msg->air_cod_gear_ctrl, msg->air_cod_mod_ctrl, msg->air_cod_temp_ctrl, msg->in_loop_mod_ctrl, msg->reserve);
  can_msgs::msg::Frame av_message1_can_msg;
  av_message1_can_msg.header.stamp = msg->header.stamp;
  av_message1_can_msg.dlc = 8;
  av_message1_can_msg.id = av_message1_parse_.ID;
  av_message1_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_message1_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_message1_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_message1_can_msg);
}

    

void ControlCommand::callbackAvMessage2(const pix_robobus_driver_msgs::msg::AvMessage2::ConstSharedPtr & msg)
{
  av_message2_issub_ = true;
  av_message2_received_time_ = this->now();
  av_message2_ptr_ = msg;
  av_message2_parse_.Reset();
  av_message2_parse_.UpdateData(msg->pwm_red_ctrl, msg->pwm_green_ctrl, msg->pwm_blue_ctrl, msg->atmospherelightbrightness_ctrl);
  can_msgs::msg::Frame av_message2_can_msg;
  av_message2_can_msg.header.stamp = msg->header.stamp;
  av_message2_can_msg.dlc = 8;
  av_message2_can_msg.id = av_message2_parse_.ID;
  av_message2_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = av_message2_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    av_message2_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(av_message2_can_msg);
}

    

void ControlCommand::onDelayedAlarm(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  const std::string error_msg = "[ReportConverter]: Timeout";
  const auto diag_level = diagnostic_msgs::msg::DiagnosticStatus::OK;
  stat.summary(diag_level, error_msg);
  // on_delayed_alarm_list
  
  stat.addf("av_aeb_ctrl count_eorro", "%%d", av_aeb_ctrl_delay_.count_eorro); 
  stat.addf("av_aeb_ctrl count_warn", "%%d", av_aeb_ctrl_delay_.count_waring);
    
  stat.addf("av_drive_ctrl count_eorro", "%%d", av_drive_ctrl_delay_.count_eorro); 
  stat.addf("av_drive_ctrl count_warn", "%%d", av_drive_ctrl_delay_.count_waring);
    
  stat.addf("av_brake_ctrl count_eorro", "%%d", av_brake_ctrl_delay_.count_eorro); 
  stat.addf("av_brake_ctrl count_warn", "%%d", av_brake_ctrl_delay_.count_waring);
    
  stat.addf("av_steer_ctrl count_eorro", "%%d", av_steer_ctrl_delay_.count_eorro); 
  stat.addf("av_steer_ctrl count_warn", "%%d", av_steer_ctrl_delay_.count_waring);
    
  stat.addf("av_vehicle_ctrl count_eorro", "%%d", av_vehicle_ctrl_delay_.count_eorro); 
  stat.addf("av_vehicle_ctrl count_warn", "%%d", av_vehicle_ctrl_delay_.count_waring);
    
  stat.addf("av_wheel_torque_ctrl count_eorro", "%%d", av_wheel_torque_ctrl_delay_.count_eorro); 
  stat.addf("av_wheel_torque_ctrl count_warn", "%%d", av_wheel_torque_ctrl_delay_.count_waring);
    
  stat.addf("av_manual_spd_limit count_eorro", "%%d", av_manual_spd_limit_delay_.count_eorro); 
  stat.addf("av_manual_spd_limit count_warn", "%%d", av_manual_spd_limit_delay_.count_waring);
    
  stat.addf("av_self_driving_work_st count_eorro", "%%d", av_self_driving_work_st_delay_.count_eorro); 
  stat.addf("av_self_driving_work_st count_warn", "%%d", av_self_driving_work_st_delay_.count_waring);
    
  stat.addf("auto_message count_eorro", "%%d", auto_message_delay_.count_eorro); 
  stat.addf("auto_message count_warn", "%%d", auto_message_delay_.count_waring);
    
  stat.addf("remote_message count_eorro", "%%d", remote_message_delay_.count_eorro); 
  stat.addf("remote_message count_warn", "%%d", remote_message_delay_.count_waring);
    
  stat.addf("acu_sys_time count_eorro", "%%d", acu_sys_time_delay_.count_eorro); 
  stat.addf("acu_sys_time count_warn", "%%d", acu_sys_time_delay_.count_waring);
    
  stat.addf("av_message1 count_eorro", "%%d", av_message1_delay_.count_eorro); 
  stat.addf("av_message1 count_warn", "%%d", av_message1_delay_.count_waring);
    
  stat.addf("av_message2 count_eorro", "%%d", av_message2_delay_.count_eorro); 
  stat.addf("av_message2 count_warn", "%%d", av_message2_delay_.count_waring);
    
}

void ControlCommand::timerCallback()
{

  // 如果存在一个为flase，表示初始化没有下发 - if_pix_interface_definition_list
  if(!av_aeb_ctrl_issub_) return;
  if(!av_drive_ctrl_issub_) return;
  if(!av_brake_ctrl_issub_) return;
  if(!av_steer_ctrl_issub_) return;
  if(!av_vehicle_ctrl_issub_) return;
  if(!av_wheel_torque_ctrl_issub_) return;
  if(!av_manual_spd_limit_issub_) return;
  if(!av_self_driving_work_st_issub_) return;
  if(!auto_message_issub_) return;
  if(!remote_message_issub_) return;
  if(!acu_sys_time_issub_) return;
  if(!av_message1_issub_) return;
  if(!av_message2_issub_) return;

  const rclcpp::Time current_time = this->now();
  // if_msg_received_timestamp_list


  const double av_aeb_ctrl_delta_time_ms =
    (current_time - av_aeb_ctrl_received_time_).seconds() * 1000.0;
  if(av_aeb_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_aeb_ctrl_delay_.count_eorro++;
  }else if (av_aeb_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_aeb_ctrl_delay_.count_waring++;
  }

  const double av_drive_ctrl_delta_time_ms =
    (current_time - av_drive_ctrl_received_time_).seconds() * 1000.0;
  if(av_drive_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_drive_ctrl_delay_.count_eorro++;
  }else if (av_drive_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_drive_ctrl_delay_.count_waring++;
  }

  const double av_brake_ctrl_delta_time_ms =
    (current_time - av_brake_ctrl_received_time_).seconds() * 1000.0;
  if(av_brake_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_brake_ctrl_delay_.count_eorro++;
  }else if (av_brake_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_brake_ctrl_delay_.count_waring++;
  }

  const double av_steer_ctrl_delta_time_ms =
    (current_time - av_steer_ctrl_received_time_).seconds() * 1000.0;
  if(av_steer_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_steer_ctrl_delay_.count_eorro++;
  }else if (av_steer_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_steer_ctrl_delay_.count_waring++;
  }

  const double av_vehicle_ctrl_delta_time_ms =
    (current_time - av_vehicle_ctrl_received_time_).seconds() * 1000.0;
  if(av_vehicle_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_vehicle_ctrl_delay_.count_eorro++;
  }else if (av_vehicle_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_vehicle_ctrl_delay_.count_waring++;
  }

  const double av_wheel_torque_ctrl_delta_time_ms =
    (current_time - av_wheel_torque_ctrl_received_time_).seconds() * 1000.0;
  if(av_wheel_torque_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_wheel_torque_ctrl_delay_.count_eorro++;
  }else if (av_wheel_torque_ctrl_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_wheel_torque_ctrl_delay_.count_waring++;
  }

  const double av_manual_spd_limit_delta_time_ms =
    (current_time - av_manual_spd_limit_received_time_).seconds() * 1000.0;
  if(av_manual_spd_limit_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_manual_spd_limit_delay_.count_eorro++;
  }else if (av_manual_spd_limit_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_manual_spd_limit_delay_.count_waring++;
  }

  const double av_self_driving_work_st_delta_time_ms =
    (current_time - av_self_driving_work_st_received_time_).seconds() * 1000.0;
  if(av_self_driving_work_st_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_self_driving_work_st_delay_.count_eorro++;
  }else if (av_self_driving_work_st_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_self_driving_work_st_delay_.count_waring++;
  }

  const double auto_message_delta_time_ms =
    (current_time - auto_message_received_time_).seconds() * 1000.0;
  if(auto_message_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    auto_message_delay_.count_eorro++;
  }else if (auto_message_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    auto_message_delay_.count_waring++;
  }

  const double remote_message_delta_time_ms =
    (current_time - remote_message_received_time_).seconds() * 1000.0;
  if(remote_message_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    remote_message_delay_.count_eorro++;
  }else if (remote_message_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    remote_message_delay_.count_waring++;
  }

  const double acu_sys_time_delta_time_ms =
    (current_time - acu_sys_time_received_time_).seconds() * 1000.0;
  if(acu_sys_time_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    acu_sys_time_delay_.count_eorro++;
  }else if (acu_sys_time_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    acu_sys_time_delay_.count_waring++;
  }

  const double av_message1_delta_time_ms =
    (current_time - av_message1_received_time_).seconds() * 1000.0;
  if(av_message1_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_message1_delay_.count_eorro++;
  }else if (av_message1_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_message1_delay_.count_waring++;
  }

  const double av_message2_delta_time_ms =
    (current_time - av_message2_received_time_).seconds() * 1000.0;
  if(av_message2_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    av_message2_delay_.count_eorro++;
  }else if (av_message2_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    av_message2_delay_.count_waring++;
  }
}

} // namespace control_command
} // namespace pix_robobus_driver
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(pix_robobus_driver::control_command::ControlCommand)