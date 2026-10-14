#ifndef ROBOBUS_HMI_DATA_RELAY__BRIDGES__RELAY_AUTOWARE_TRANSFER_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__BRIDGES__RELAY_AUTOWARE_TRANSFER_MODULE_HPP_

#include <chrono>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>

#include <pixmoving_hmi_msgs/msg/autoware_command.hpp>
#include <pixmoving_hmi_msgs/msg/autoware_report.hpp>
#include <pixmoving_hmi_msgs/msg/float32_multi_array_stamped.hpp>
#include <pixmoving_hmi_msgs/msg/path.hpp>
#include <pixmoving_hmi_msgs/msg/path_point.hpp>

#include <autoware_internal_debug_msgs/msg/float32_multi_array_stamped.hpp>
#include <autoware_internal_debug_msgs/msg/float32_stamped.hpp>
#include <autoware_internal_planning_msgs/msg/velocity_limit.hpp>
#include <autoware_planning_msgs/msg/path.hpp>
#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/gear_report.hpp>
#include <autoware_vehicle_msgs/msg/steering_report.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>
#include <pix_robobus_driver_msgs/msg/va_brake_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_drive_sta_fb.hpp>

namespace robobus_hmi_data_relay::bridges
{

class RelayAutowareTransferBridgeModule
{
public:
  explicit RelayAutowareTransferBridgeModule(rclcpp::Node * node);

private:
  void drive_gear_callback(const pix_robobus_driver_msgs::msg::VaDriveStaFb::ConstSharedPtr msg);
  void brake_gear_callback(const pix_robobus_driver_msgs::msg::VaBrakeStaFb::ConstSharedPtr msg);
  void velocity_callback(const autoware_vehicle_msgs::msg::VelocityReport::ConstSharedPtr msg);
  void control_mode_callback(
    const autoware_vehicle_msgs::msg::ControlModeReport::ConstSharedPtr msg);
  void steering_report_callback(
    const autoware_vehicle_msgs::msg::SteeringReport::ConstSharedPtr msg);
  void turn_light_report_callback(
    const autoware_vehicle_msgs::msg::TurnIndicatorsReport::ConstSharedPtr msg);
  void autoware_state_callback(
    const autoware_system_msgs::msg::AutowareState::ConstSharedPtr msg);
  void ndt_quality_callback(
    const autoware_internal_debug_msgs::msg::Float32Stamped::ConstSharedPtr msg);
  void lateral_diagnostic_callback(
    const autoware_internal_debug_msgs::msg::Float32MultiArrayStamped::ConstSharedPtr msg);
  void longitudinal_diagnostic_callback(
    const autoware_internal_debug_msgs::msg::Float32MultiArrayStamped::ConstSharedPtr msg);
  void lane_driving_path_callback(const autoware_planning_msgs::msg::Path::ConstSharedPtr msg);
  void path_candidate_path_callback(const autoware_planning_msgs::msg::Path::ConstSharedPtr msg);
  void autoware_command_callback(
    const pixmoving_hmi_msgs::msg::AutowareCommand::ConstSharedPtr msg);
  void publish_autoware_report();
  void update_current_map_info();

  rclcpp::Node * node_;
  pixmoving_hmi_msgs::msg::AutowareReport autoware_report_;

  rclcpp::Publisher<pixmoving_hmi_msgs::msg::AutowareReport>::SharedPtr autoware_report_pub_;
  rclcpp::Publisher<autoware_internal_planning_msgs::msg::VelocityLimit>::SharedPtr velocity_limit_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::Float32MultiArrayStamped>::SharedPtr pub_lateral_diagnostic_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::Float32MultiArrayStamped>::SharedPtr pub_longitudinal_diagnostic_;

  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaDriveStaFb>::SharedPtr drive_gear_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaBrakeStaFb>::SharedPtr brake_gear_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr velocity_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::ControlModeReport>::SharedPtr control_mode_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::SteeringReport>::SharedPtr steering_report_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::TurnIndicatorsReport>::SharedPtr turn_light_report_sub_;
  rclcpp::Subscription<autoware_system_msgs::msg::AutowareState>::SharedPtr autoware_state_sub_;
  rclcpp::Subscription<autoware_internal_debug_msgs::msg::Float32Stamped>::SharedPtr ndt_quality_sub_;
  rclcpp::Subscription<autoware_internal_debug_msgs::msg::Float32MultiArrayStamped>::SharedPtr
    sub_control_lateral_diagnostic_;
  rclcpp::Subscription<autoware_internal_debug_msgs::msg::Float32MultiArrayStamped>::SharedPtr
    sub_control_longitudinal_diagnostic_;
  rclcpp::Subscription<pixmoving_hmi_msgs::msg::AutowareCommand>::SharedPtr autoware_command_sub_;

  rclcpp::Subscription<autoware_planning_msgs::msg::Path>::SharedPtr sub_lane_driving_path_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::Path>::SharedPtr pub_lane_driving_path_;
  rclcpp::Subscription<autoware_planning_msgs::msg::Path>::SharedPtr sub_path_candidate_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::Path>::SharedPtr pub_path_candidate_;

  rclcpp::TimerBase::SharedPtr timer_;
  std::uint8_t current_gear_report_ = autoware_vehicle_msgs::msg::GearReport::NONE;
  bool current_park_report_ = false;
  std::string map_entry_path_;
  std::chrono::steady_clock::time_point last_map_refresh_time_{};
};

}  // namespace robobus_hmi_data_relay::bridges

#endif
