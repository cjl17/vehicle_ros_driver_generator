#include "robobus_hmi_data_relay/bridges/relay_autoware_transfer_module.hpp"

#include <chrono>
#include <filesystem>

namespace robobus_hmi_data_relay::bridges
{
namespace fs = std::filesystem;

RelayAutowareTransferBridgeModule::RelayAutowareTransferBridgeModule(rclcpp::Node * node)
: node_(node)
{
  map_entry_path_ = node_->declare_parameter<std::string>("map_entry_path", "/home/ipc/pix/map/main");
  update_current_map_info();

  autoware_report_pub_ = node_->create_publisher<pixmoving_hmi_msgs::msg::AutowareReport>(
    "/pixmoving_api/autoware_report", 10);

  rclcpp::QoS qos_profile{rclcpp::KeepAll{}};
  qos_profile.transient_local();
  velocity_limit_pub_ = node_->create_publisher<autoware_internal_planning_msgs::msg::VelocityLimit>(
    "/planning/scenario_planning/max_velocity_default", qos_profile);

  pub_lateral_diagnostic_ =
    node_->create_publisher<pixmoving_hmi_msgs::msg::Float32MultiArrayStamped>(
      "/pixmoving_api/trajectory_follower/lateral/diagnostic", 10);
  pub_longitudinal_diagnostic_ =
    node_->create_publisher<pixmoving_hmi_msgs::msg::Float32MultiArrayStamped>(
      "/pixmoving_api/trajectory_follower/longitudinal/diagnostic", 10);

  drive_gear_sub_ = node_->create_subscription<pix_robobus_driver_msgs::msg::VaDriveStaFb>(
    "/pix_robobus/va_drive_sta_fb", 10,
    std::bind(&RelayAutowareTransferBridgeModule::drive_gear_callback, this, std::placeholders::_1));
  brake_gear_sub_ = node_->create_subscription<pix_robobus_driver_msgs::msg::VaBrakeStaFb>(
    "/pix_robobus/va_brake_sta_fb", 10,
    std::bind(&RelayAutowareTransferBridgeModule::brake_gear_callback, this, std::placeholders::_1));
  velocity_sub_ = node_->create_subscription<autoware_vehicle_msgs::msg::VelocityReport>(
    "/vehicle/status/velocity_status", 10,
    std::bind(&RelayAutowareTransferBridgeModule::velocity_callback, this, std::placeholders::_1));
  control_mode_sub_ = node_->create_subscription<autoware_vehicle_msgs::msg::ControlModeReport>(
    "/vehicle/status/control_mode", 10,
    std::bind(&RelayAutowareTransferBridgeModule::control_mode_callback, this, std::placeholders::_1));
  steering_report_sub_ = node_->create_subscription<autoware_vehicle_msgs::msg::SteeringReport>(
    "/vehicle/status/steering_status", 10,
    std::bind(&RelayAutowareTransferBridgeModule::steering_report_callback, this, std::placeholders::_1));
  turn_light_report_sub_ =
    node_->create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsReport>(
      "/vehicle/status/turn_indicators_status", 10,
      std::bind(&RelayAutowareTransferBridgeModule::turn_light_report_callback, this, std::placeholders::_1));
  autoware_state_sub_ = node_->create_subscription<autoware_system_msgs::msg::AutowareState>(
    "/autoware/state", 10,
    std::bind(&RelayAutowareTransferBridgeModule::autoware_state_callback, this, std::placeholders::_1));
  ndt_quality_sub_ = node_->create_subscription<autoware_internal_debug_msgs::msg::Float32Stamped>(
    "/localization/pose_estimator/nearest_voxel_transformation_likelihood", 10,
    std::bind(&RelayAutowareTransferBridgeModule::ndt_quality_callback, this, std::placeholders::_1));
  sub_control_lateral_diagnostic_ =
    node_->create_subscription<autoware_internal_debug_msgs::msg::Float32MultiArrayStamped>(
      "/control/trajectory_follower/lateral/diagnostic", 10,
      std::bind(&RelayAutowareTransferBridgeModule::lateral_diagnostic_callback, this, std::placeholders::_1));
  sub_control_longitudinal_diagnostic_ =
    node_->create_subscription<autoware_internal_debug_msgs::msg::Float32MultiArrayStamped>(
      "/control/trajectory_follower/longitudinal/diagnostic", 10,
      std::bind(&RelayAutowareTransferBridgeModule::longitudinal_diagnostic_callback, this, std::placeholders::_1));
  sub_lane_driving_path_ = node_->create_subscription<autoware_planning_msgs::msg::Path>(
    "/planning/scenario_planning/lane_driving/behavior_planning/path", 10,
    std::bind(&RelayAutowareTransferBridgeModule::lane_driving_path_callback, this, std::placeholders::_1));
  pub_lane_driving_path_ = node_->create_publisher<pixmoving_hmi_msgs::msg::Path>(
    "/pixmoving_api/lane_driving/behavior_planning/path", 10);
  sub_path_candidate_ = node_->create_subscription<autoware_planning_msgs::msg::Path>(
    "/planning/path_candidate/start_planner", 10,
    std::bind(&RelayAutowareTransferBridgeModule::path_candidate_path_callback, this, std::placeholders::_1));
  pub_path_candidate_ = node_->create_publisher<pixmoving_hmi_msgs::msg::Path>(
    "/pixmoving_api/path_candidate/start_planner", 10);
  autoware_command_sub_ = node_->create_subscription<pixmoving_hmi_msgs::msg::AutowareCommand>(
    "/pixmoving_api/autoware_command", 10,
    std::bind(&RelayAutowareTransferBridgeModule::autoware_command_callback, this, std::placeholders::_1));

  timer_ = node_->create_wall_timer(
    std::chrono::milliseconds(100),
    std::bind(&RelayAutowareTransferBridgeModule::publish_autoware_report, this));
}

void RelayAutowareTransferBridgeModule::lateral_diagnostic_callback(
  const autoware_internal_debug_msgs::msg::Float32MultiArrayStamped::ConstSharedPtr msg)
{
  pixmoving_hmi_msgs::msg::Float32MultiArrayStamped out_msg;
  out_msg.stamp = msg->stamp;
  out_msg.layout = msg->layout;
  out_msg.data = msg->data;
  pub_lateral_diagnostic_->publish(out_msg);
}

void RelayAutowareTransferBridgeModule::longitudinal_diagnostic_callback(
  const autoware_internal_debug_msgs::msg::Float32MultiArrayStamped::ConstSharedPtr msg)
{
  pixmoving_hmi_msgs::msg::Float32MultiArrayStamped out_msg;
  out_msg.stamp = msg->stamp;
  out_msg.layout = msg->layout;
  out_msg.data = msg->data;
  pub_longitudinal_diagnostic_->publish(out_msg);
}

void RelayAutowareTransferBridgeModule::lane_driving_path_callback(
  const autoware_planning_msgs::msg::Path::ConstSharedPtr msg)
{
  pixmoving_hmi_msgs::msg::Path out_msg;
  out_msg.header = msg->header;
  out_msg.points.reserve(msg->points.size());
  for (const auto & pt : msg->points) {
    pixmoving_hmi_msgs::msg::PathPoint out_pt;
    out_pt.pose = pt.pose;
    out_pt.longitudinal_velocity_mps = pt.longitudinal_velocity_mps;
    out_pt.lateral_velocity_mps = pt.lateral_velocity_mps;
    out_pt.heading_rate_rps = pt.heading_rate_rps;
    out_pt.is_final = pt.is_final;
    out_msg.points.push_back(out_pt);
  }
  out_msg.left_bound = msg->left_bound;
  out_msg.right_bound = msg->right_bound;
  pub_lane_driving_path_->publish(out_msg);
}

void RelayAutowareTransferBridgeModule::path_candidate_path_callback(
  const autoware_planning_msgs::msg::Path::ConstSharedPtr msg)
{
  pixmoving_hmi_msgs::msg::Path out_msg;
  out_msg.header = msg->header;
  out_msg.points.reserve(msg->points.size());
  for (const auto & pt : msg->points) {
    pixmoving_hmi_msgs::msg::PathPoint out_pt;
    out_pt.pose = pt.pose;
    out_pt.longitudinal_velocity_mps = pt.longitudinal_velocity_mps;
    out_pt.lateral_velocity_mps = pt.lateral_velocity_mps;
    out_pt.heading_rate_rps = pt.heading_rate_rps;
    out_pt.is_final = pt.is_final;
    out_msg.points.push_back(out_pt);
  }
  out_msg.left_bound = msg->left_bound;
  out_msg.right_bound = msg->right_bound;
  pub_path_candidate_->publish(out_msg);
}

void RelayAutowareTransferBridgeModule::drive_gear_callback(
  const pix_robobus_driver_msgs::msg::VaDriveStaFb::ConstSharedPtr msg)
{
  switch (msg->vcu_chassis_gear_fb) {
    case 1:
      current_gear_report_ = autoware_vehicle_msgs::msg::GearReport::DRIVE;
      break;
    case 2:
      current_gear_report_ = autoware_vehicle_msgs::msg::GearReport::NEUTRAL;
      break;
    case 3:
      current_gear_report_ = autoware_vehicle_msgs::msg::GearReport::REVERSE;
      break;
    case 0:
    default:
      current_gear_report_ = autoware_vehicle_msgs::msg::GearReport::NONE;
      break;
  }

  autoware_report_.gear =
    current_park_report_ ? autoware_vehicle_msgs::msg::GearReport::PARK : current_gear_report_;
}

void RelayAutowareTransferBridgeModule::brake_gear_callback(
  const pix_robobus_driver_msgs::msg::VaBrakeStaFb::ConstSharedPtr msg)
{
  current_park_report_ = (msg->vcu_chassis_epb_fb == 1 || msg->vcu_chassis_epb_fb == 3);
  autoware_report_.gear =
    current_park_report_ ? autoware_vehicle_msgs::msg::GearReport::PARK : current_gear_report_;
}

void RelayAutowareTransferBridgeModule::velocity_callback(
  const autoware_vehicle_msgs::msg::VelocityReport::ConstSharedPtr msg)
{
  autoware_report_.velocity = msg->longitudinal_velocity;
}

void RelayAutowareTransferBridgeModule::control_mode_callback(
  const autoware_vehicle_msgs::msg::ControlModeReport::ConstSharedPtr msg)
{
  autoware_report_.control_mode = msg->mode;
}

void RelayAutowareTransferBridgeModule::steering_report_callback(
  const autoware_vehicle_msgs::msg::SteeringReport::ConstSharedPtr msg)
{
  autoware_report_.steering_tire_angle = msg->steering_tire_angle;
}

void RelayAutowareTransferBridgeModule::turn_light_report_callback(
  const autoware_vehicle_msgs::msg::TurnIndicatorsReport::ConstSharedPtr msg)
{
  autoware_report_.turn_light_report = msg->report;
}

void RelayAutowareTransferBridgeModule::autoware_state_callback(
  const autoware_system_msgs::msg::AutowareState::ConstSharedPtr msg)
{
  autoware_report_.state = msg->state;
}

void RelayAutowareTransferBridgeModule::ndt_quality_callback(
  const autoware_internal_debug_msgs::msg::Float32Stamped::ConstSharedPtr msg)
{
  autoware_report_.ndt_quality = msg->data;
}

void RelayAutowareTransferBridgeModule::publish_autoware_report()
{
  update_current_map_info();
  autoware_report_pub_->publish(autoware_report_);
}

void RelayAutowareTransferBridgeModule::update_current_map_info()
{
  const auto now = std::chrono::steady_clock::now();
  if (
    last_map_refresh_time_.time_since_epoch().count() != 0 &&
    now - last_map_refresh_time_ < std::chrono::seconds(1))
  {
    return;
  }
  last_map_refresh_time_ = now;

  std::error_code ec;
  const fs::path entry_path(map_entry_path_);
  if (!fs::exists(entry_path, ec)) {
    autoware_report_.current_map_name.clear();
    autoware_report_.current_map_path.clear();
    return;
  }

  fs::path resolved_path = entry_path;
  if (fs::is_symlink(entry_path, ec)) {
    const fs::path symlink_target = fs::read_symlink(entry_path, ec);
    if (ec) {
      autoware_report_.current_map_name.clear();
      autoware_report_.current_map_path.clear();
      return;
    }
    resolved_path = symlink_target.is_relative() ? entry_path.parent_path() / symlink_target : symlink_target;
  }

  resolved_path = resolved_path.lexically_normal();
  autoware_report_.current_map_name = resolved_path.filename().string();
  autoware_report_.current_map_path = resolved_path.string();
}

void RelayAutowareTransferBridgeModule::autoware_command_callback(
  const pixmoving_hmi_msgs::msg::AutowareCommand::ConstSharedPtr msg)
{
  if (!msg->velocity_limit_en) {
    return;
  }
  autoware_internal_planning_msgs::msg::VelocityLimit velocity_limit_msg;
  velocity_limit_msg.stamp = node_->now();
  velocity_limit_msg.max_velocity = msg->velocity_limit * 0.2777;
  velocity_limit_msg.use_constraints = true;
  velocity_limit_msg.constraints.min_acceleration = -1.0;
  velocity_limit_msg.constraints.min_jerk = -1.0;
  velocity_limit_msg.constraints.max_jerk = 1.0;
  velocity_limit_msg.sender = "autoware_state_panel";
  velocity_limit_pub_->publish(velocity_limit_msg);
}

}  // namespace robobus_hmi_data_relay::bridges
