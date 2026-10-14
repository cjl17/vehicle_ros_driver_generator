#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <can_msgs/msg/frame.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>

// pix_robobus_driver msgs - include_msgsName_list
#include <pix_robobus_driver_msgs/msg/av_aeb_ctrl.hpp>
#include <pix_robobus_driver_msgs/msg/av_drive_ctrl.hpp>
#include <pix_robobus_driver_msgs/msg/av_brake_ctrl.hpp>
#include <pix_robobus_driver_msgs/msg/av_steer_ctrl.hpp>
#include <pix_robobus_driver_msgs/msg/av_vehicle_ctrl.hpp>
#include <pix_robobus_driver_msgs/msg/av_wheel_torque_ctrl.hpp>
#include <pix_robobus_driver_msgs/msg/av_manual_spd_limit.hpp>
#include <pix_robobus_driver_msgs/msg/av_self_driving_work_st.hpp>
#include <pix_robobus_driver_msgs/msg/auto_message.hpp>
#include <pix_robobus_driver_msgs/msg/remote_message.hpp>
#include <pix_robobus_driver_msgs/msg/acu_sys_time.hpp>
#include <pix_robobus_driver_msgs/msg/av_message1.hpp>
#include <pix_robobus_driver_msgs/msg/av_message2.hpp>


// pix_robobus_driver parse  - include_ParseName_list
#include <libs/av_aeb_ctrl.hpp>
#include <libs/av_drive_ctrl.hpp>
#include <libs/av_brake_ctrl.hpp>
#include <libs/av_steer_ctrl.hpp>
#include <libs/av_vehicle_ctrl.hpp>
#include <libs/av_wheel_torque_ctrl.hpp>
#include <libs/av_manual_spd_limit.hpp>
#include <libs/av_self_driving_work_st.hpp>
#include <libs/auto_message.hpp>
#include <libs/remote_message.hpp>
#include <libs/acu_sys_time.hpp>
#include <libs/av_message1.hpp>
#include <libs/av_message2.hpp>


#define ERROR_THRESHOLD 5   // 严重级别延迟阈值
#define WARNING_THRESHOLD 3  // 警告级别延迟阈值
// 延迟记录
struct DelayRecording
{
  uint32_t count_eorro;  // 严重级别延迟累计 - 丢失5个周期
  uint32_t count_waring; // 警告级别延迟累计 - 丢失3个周期
};

namespace pix_robobus_driver
{
namespace control_command
{

/**
 * @param pix_interface_driver_eorro pix_interface 严重超时阀值
 * @param pix_interface_driver_warn pix_interface 警告超时阀值
 */
struct TimeoutThresholdMs
{
  uint8_t pix_interface_driver_eorro;  // ms
  uint8_t pix_interface_driver_warn;  // ms
};

/**
 * @brief param structure of control command node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 * @param timeout_threshold_ms 超时阀值
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
  TimeoutThresholdMs timeout_threshold_ms;
};

class ControlCommand : public rclcpp::Node
{
private:
  // Diagnostics Updater
  diagnostic_updater::Updater updater_;
  void onDelayedAlarm(diagnostic_updater::DiagnosticStatusWrapper & stat);

  // 订阅 pix_interface 底盘控制帧的下发延迟记录 - delay_recording_definition_list
  DelayRecording av_aeb_ctrl_delay_;
  DelayRecording av_drive_ctrl_delay_;
  DelayRecording av_brake_ctrl_delay_;
  DelayRecording av_steer_ctrl_delay_;
  DelayRecording av_vehicle_ctrl_delay_;
  DelayRecording av_wheel_torque_ctrl_delay_;
  DelayRecording av_manual_spd_limit_delay_;
  DelayRecording av_self_driving_work_st_delay_;
  DelayRecording auto_message_delay_;
  DelayRecording remote_message_delay_;
  DelayRecording acu_sys_time_delay_;
  DelayRecording av_message1_delay_;
  DelayRecording av_message2_delay_;


  // 订阅 pix_interface 是否已经下发 - is_pix_interface_definition_list
  bool av_aeb_ctrl_issub_;
  bool av_drive_ctrl_issub_;
  bool av_brake_ctrl_issub_;
  bool av_steer_ctrl_issub_;
  bool av_vehicle_ctrl_issub_;
  bool av_wheel_torque_ctrl_issub_;
  bool av_manual_spd_limit_issub_;
  bool av_self_driving_work_st_issub_;
  bool auto_message_issub_;
  bool remote_message_issub_;
  bool acu_sys_time_issub_;
  bool av_message1_issub_;
  bool av_message2_issub_;


private:
  // parameters of node
  Param param_;

  // subscribers - subscriber_member_list
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvAebCtrl>::SharedPtr av_aeb_ctrl_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvDriveCtrl>::SharedPtr av_drive_ctrl_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvBrakeCtrl>::SharedPtr av_brake_ctrl_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvSteerCtrl>::SharedPtr av_steer_ctrl_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvVehicleCtrl>::SharedPtr av_vehicle_ctrl_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvWheelTorqueCtrl>::SharedPtr av_wheel_torque_ctrl_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvManualSpdLimit>::SharedPtr av_manual_spd_limit_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvSelfDrivingWorkSt>::SharedPtr av_self_driving_work_st_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AutoMessage>::SharedPtr auto_message_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::RemoteMessage>::SharedPtr remote_message_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AcuSysTime>::SharedPtr acu_sys_time_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvMessage1>::SharedPtr av_message1_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::AvMessage2>::SharedPtr av_message2_sub_;


  // pix_robobus_driver msgs -  msg_member_list
  pix_robobus_driver_msgs::msg::AvAebCtrl::ConstSharedPtr av_aeb_ctrl_ptr_;
  pix_robobus_driver_msgs::msg::AvDriveCtrl::ConstSharedPtr av_drive_ctrl_ptr_;
  pix_robobus_driver_msgs::msg::AvBrakeCtrl::ConstSharedPtr av_brake_ctrl_ptr_;
  pix_robobus_driver_msgs::msg::AvSteerCtrl::ConstSharedPtr av_steer_ctrl_ptr_;
  pix_robobus_driver_msgs::msg::AvVehicleCtrl::ConstSharedPtr av_vehicle_ctrl_ptr_;
  pix_robobus_driver_msgs::msg::AvWheelTorqueCtrl::ConstSharedPtr av_wheel_torque_ctrl_ptr_;
  pix_robobus_driver_msgs::msg::AvManualSpdLimit::ConstSharedPtr av_manual_spd_limit_ptr_;
  pix_robobus_driver_msgs::msg::AvSelfDrivingWorkSt::ConstSharedPtr av_self_driving_work_st_ptr_;
  pix_robobus_driver_msgs::msg::AutoMessage::ConstSharedPtr auto_message_ptr_;
  pix_robobus_driver_msgs::msg::RemoteMessage::ConstSharedPtr remote_message_ptr_;
  pix_robobus_driver_msgs::msg::AcuSysTime::ConstSharedPtr acu_sys_time_ptr_;
  pix_robobus_driver_msgs::msg::AvMessage1::ConstSharedPtr av_message1_ptr_;
  pix_robobus_driver_msgs::msg::AvMessage2::ConstSharedPtr av_message2_ptr_;


  // control command structures - control_command_structure_list
  AvAebCtrl av_aeb_ctrl_parse_;
  AvDriveCtrl av_drive_ctrl_parse_;
  AvBrakeCtrl av_brake_ctrl_parse_;
  AvSteerCtrl av_steer_ctrl_parse_;
  AvVehicleCtrl av_vehicle_ctrl_parse_;
  AvWheelTorqueCtrl av_wheel_torque_ctrl_parse_;
  AvManualSpdLimit av_manual_spd_limit_parse_;
  AvSelfDrivingWorkSt av_self_driving_work_st_parse_;
  AutoMessage auto_message_parse_;
  RemoteMessage remote_message_parse_;
  AcuSysTime acu_sys_time_parse_;
  AvMessage1 av_message1_parse_;
  AvMessage2 av_message2_parse_;


  // msg received timestamp - msg_received_timestamp_list
  rclcpp::Time av_aeb_ctrl_received_time_;
  rclcpp::Time av_drive_ctrl_received_time_;
  rclcpp::Time av_brake_ctrl_received_time_;
  rclcpp::Time av_steer_ctrl_received_time_;
  rclcpp::Time av_vehicle_ctrl_received_time_;
  rclcpp::Time av_wheel_torque_ctrl_received_time_;
  rclcpp::Time av_manual_spd_limit_received_time_;
  rclcpp::Time av_self_driving_work_st_received_time_;
  rclcpp::Time auto_message_received_time_;
  rclcpp::Time remote_message_received_time_;
  rclcpp::Time acu_sys_time_received_time_;
  rclcpp::Time av_message1_received_time_;
  rclcpp::Time av_message2_received_time_;


  // publishers to can card driver
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;

  // publishing can msgs - publishing_can_msg_list
    can_msgs::msg::Frame::ConstSharedPtr av_aeb_ctrl_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_drive_ctrl_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_brake_ctrl_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_steer_ctrl_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_vehicle_ctrl_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_wheel_torque_ctrl_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_manual_spd_limit_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_self_driving_work_st_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr auto_message_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr remote_message_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr acu_sys_time_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_message1_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr av_message2_can_ptr_;


  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ControlCommand(const rclcpp::NodeOptions & node_option);

  // calback functions - callback_function_prototype_list
  void callbackAvAebCtrl(const pix_robobus_driver_msgs::msg::AvAebCtrl::ConstSharedPtr & msg);
  void callbackAvDriveCtrl(const pix_robobus_driver_msgs::msg::AvDriveCtrl::ConstSharedPtr & msg);
  void callbackAvBrakeCtrl(const pix_robobus_driver_msgs::msg::AvBrakeCtrl::ConstSharedPtr & msg);
  void callbackAvSteerCtrl(const pix_robobus_driver_msgs::msg::AvSteerCtrl::ConstSharedPtr & msg);
  void callbackAvVehicleCtrl(const pix_robobus_driver_msgs::msg::AvVehicleCtrl::ConstSharedPtr & msg);
  void callbackAvWheelTorqueCtrl(const pix_robobus_driver_msgs::msg::AvWheelTorqueCtrl::ConstSharedPtr & msg);
  void callbackAvManualSpdLimit(const pix_robobus_driver_msgs::msg::AvManualSpdLimit::ConstSharedPtr & msg);
  void callbackAvSelfDrivingWorkSt(const pix_robobus_driver_msgs::msg::AvSelfDrivingWorkSt::ConstSharedPtr & msg);
  void callbackAutoMessage(const pix_robobus_driver_msgs::msg::AutoMessage::ConstSharedPtr & msg);
  void callbackRemoteMessage(const pix_robobus_driver_msgs::msg::RemoteMessage::ConstSharedPtr & msg);
  void callbackAcuSysTime(const pix_robobus_driver_msgs::msg::AcuSysTime::ConstSharedPtr & msg);
  void callbackAvMessage1(const pix_robobus_driver_msgs::msg::AvMessage1::ConstSharedPtr & msg);
  void callbackAvMessage2(const pix_robobus_driver_msgs::msg::AvMessage2::ConstSharedPtr & msg);

  void timerCallback();

};

} // control_command
} // pix_robobus_driver