#include "robobus_hmi_data_relay/monitors/blind_spot_monitor_module.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <string>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/convert.h>
#include <tf2/transform_datatypes.h>
#include <tf2/utils.h>

namespace robobus_hmi_data_relay::monitors
{

double BlindSpotMonitorModule::declare_compat_double_parameter(
  const std::string & primary_name, const std::string & legacy_name, double default_value) const
{
  const auto primary_value = node_->declare_parameter(primary_name, default_value);
  const auto legacy_value = node_->declare_parameter(legacy_name, default_value);

  if (primary_value != default_value) {
    return primary_value;
  }

  if (legacy_value != default_value) {
    RCLCPP_WARN(
      node_->get_logger(),
      "[blind_spot] Parameter '%s' is deprecated, please migrate to '%s'",
      legacy_name.c_str(), primary_name.c_str());
    return legacy_value;
  }

  return default_value;
}

BlindSpotMonitorModule::BlindSpotMonitorModule(rclcpp::Node * node)
: node_(node),
  target_frame_("base_link"),
  vehicle_speed_kmh_(0.0),
  vehicle_gear_("N"),
  vehicle_gear_upper_("N"),
  turn_signal_("off"),
  turn_signal_lower_("off"),
  last_vehicle_info_time_(node_->get_clock()->now()),
  last_odometry_time_(node_->get_clock()->now())
{
  left_blind_zone_.x_min = declare_compat_double_parameter(
    "blind_spot.left.x_min", "left_blind_x_min", -5.0);
  left_blind_zone_.x_max = declare_compat_double_parameter(
    "blind_spot.left.x_max", "left_blind_x_max", -1.0);
  left_blind_zone_.y_min = declare_compat_double_parameter(
    "blind_spot.left.y_min", "left_blind_y_min", 0.8);
  left_blind_zone_.y_max = declare_compat_double_parameter(
    "blind_spot.left.y_max", "left_blind_y_max", 2.5);

  right_blind_zone_.x_min = declare_compat_double_parameter(
    "blind_spot.right.x_min", "right_blind_x_min", -5.0);
  right_blind_zone_.x_max = declare_compat_double_parameter(
    "blind_spot.right.x_max", "right_blind_x_max", -1.0);
  right_blind_zone_.y_min = declare_compat_double_parameter(
    "blind_spot.right.y_min", "right_blind_y_min", -2.5);
  right_blind_zone_.y_max = declare_compat_double_parameter(
    "blind_spot.right.y_max", "right_blind_y_max", -0.8);

  front_blind_zone_.x_min = declare_compat_double_parameter(
    "blind_spot.front.x_min", "front_blind_x_min", 1.0);
  front_blind_zone_.x_max = declare_compat_double_parameter(
    "blind_spot.front.x_max", "front_blind_x_max", 5.0);
  front_blind_zone_.y_min = declare_compat_double_parameter(
    "blind_spot.front.y_min", "front_blind_y_min", -2.5);
  front_blind_zone_.y_max = declare_compat_double_parameter(
    "blind_spot.front.y_max", "front_blind_y_max", 2.5);

  rear_blind_zone_.x_min = declare_compat_double_parameter(
    "blind_spot.rear.x_min", "rear_blind_x_min", -5.0);
  rear_blind_zone_.x_max = declare_compat_double_parameter(
    "blind_spot.rear.x_max", "rear_blind_x_max", -1.0);
  rear_blind_zone_.y_min = declare_compat_double_parameter(
    "blind_spot.rear.y_min", "rear_blind_y_min", -2.5);
  rear_blind_zone_.y_max = declare_compat_double_parameter(
    "blind_spot.rear.y_max", "rear_blind_y_max", -0.8);

  low_speed_threshold_kmh_ = declare_compat_double_parameter(
    "blind_spot.threshold.low_speed_kmh", "low_speed_threshold_kmh", 10.0);
  high_speed_threshold_kmh_ = declare_compat_double_parameter(
    "blind_spot.threshold.high_speed_kmh", "high_speed_threshold_kmh", 30.0);
  entry_delay_sec_ = declare_compat_double_parameter(
    "blind_spot.delay.entry_sec", "entry_delay_sec", 0.3);
  exit_delay_sec_ = declare_compat_double_parameter(
    "blind_spot.delay.exit_sec", "exit_delay_sec", 0.5);

  RCLCPP_INFO(node_->get_logger(), "[blind_spot] Loaded parameters:");
  RCLCPP_INFO(
    node_->get_logger(), "[blind_spot]   Left blind zone: x[%.2f, %.2f], y[%.2f, %.2f]",
    left_blind_zone_.x_min, left_blind_zone_.x_max, left_blind_zone_.y_min, left_blind_zone_.y_max);
  RCLCPP_INFO(
    node_->get_logger(), "[blind_spot]   Right blind zone: x[%.2f, %.2f], y[%.2f, %.2f]",
    right_blind_zone_.x_min, right_blind_zone_.x_max, right_blind_zone_.y_min, right_blind_zone_.y_max);
  RCLCPP_INFO(
    node_->get_logger(), "[blind_spot]   Front blind zone: x[%.2f, %.2f], y[%.2f, %.2f]",
    front_blind_zone_.x_min, front_blind_zone_.x_max, front_blind_zone_.y_min, front_blind_zone_.y_max);
  RCLCPP_INFO(
    node_->get_logger(), "[blind_spot]   Rear blind zone: x[%.2f, %.2f], y[%.2f, %.2f]",
    rear_blind_zone_.x_min, rear_blind_zone_.x_max, rear_blind_zone_.y_min, rear_blind_zone_.y_max);

  left_warning_ = {false, false, 0.0, 0.0};
  right_warning_ = {false, false, 0.0, 0.0};
  front_warning_ = {false, false, 0.0, 0.0};
  rear_warning_ = {false, false, 0.0, 0.0};

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(node_->get_clock());
  tf_buffer_->setUsingDedicatedThread(true);
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_, node_->shared_from_this(), false);

  rclcpp::QoS qos(10);
  qos.best_effort();
  objects_sub_ = node_->create_subscription<autoware_perception_msgs::msg::PredictedObjects>(
    "/perception/object_recognition/objects", qos,
    std::bind(&BlindSpotMonitorModule::objects_callback, this, std::placeholders::_1));
  vehicle_info_sub_ = node_->create_subscription<pixmoving_hmi_msgs::msg::VehicleInfo>(
    "/app/cloud_control_platform/vehicle_info", 10,
    std::bind(&BlindSpotMonitorModule::vehicle_info_callback, this, std::placeholders::_1));
  rclcpp::QoS odom_qos(10);
  odom_qos.reliable();
  odometry_sub_ = node_->create_subscription<nav_msgs::msg::Odometry>(
    "/localization/kinematic_state", odom_qos,
    std::bind(&BlindSpotMonitorModule::odometry_callback, this, std::placeholders::_1));

  status_pub_ = node_->create_publisher<pixmoving_hmi_msgs::msg::BlindSpotStatus>(
    "/pixmoving/blind_spot/status", 10);
  marker_pub_ = node_->create_publisher<visualization_msgs::msg::MarkerArray>(
    "/vehicle/safety/blind_spot_zones", 10);

  warning_timer_ = node_->create_wall_timer(
    std::chrono::milliseconds(100),
    std::bind(&BlindSpotMonitorModule::update_warning_states, this));
  marker_timer_ = node_->create_wall_timer(
    std::chrono::seconds(1),
    std::bind(&BlindSpotMonitorModule::publish_zone_markers, this));

  RCLCPP_INFO(node_->get_logger(), "[blind_spot] BlindSpotMonitorModule started.");
}

void BlindSpotMonitorModule::vehicle_info_callback(
  const pixmoving_hmi_msgs::msg::VehicleInfo::ConstSharedPtr msg)
{
  vehicle_speed_kmh_ = msg->spd >= 0 ? static_cast<double>(msg->spd) : 0.0;

  std::map<int8_t, std::string> gear_map = {{0, "P"}, {2, "R"}, {3, "N"}, {4, "D"}, {-1, "N"}};
  auto it = gear_map.find(msg->gear);
  vehicle_gear_ = (it != gear_map.end()) ? it->second : "N";
  vehicle_gear_upper_ = vehicle_gear_;
  std::transform(vehicle_gear_upper_.begin(), vehicle_gear_upper_.end(), vehicle_gear_upper_.begin(), ::toupper);

  std::map<int8_t, std::string> turn_light_map = {
    {0, "off"}, {1, "left"}, {2, "right"}, {3, "off"}, {-1, "off"}};
  auto turn_it = turn_light_map.find(msg->turn_light);
  turn_signal_ = (turn_it != turn_light_map.end()) ? turn_it->second : "off";
  turn_signal_lower_ = turn_signal_;
  std::transform(turn_signal_lower_.begin(), turn_signal_lower_.end(), turn_signal_lower_.begin(), ::tolower);

  last_vehicle_info_time_ = node_->get_clock()->now();
}

void BlindSpotMonitorModule::odometry_callback(const nav_msgs::msg::Odometry::ConstSharedPtr msg)
{
  vehicle_position_ = std::make_tuple(
    msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
  vehicle_orientation_ = std::make_tuple(
    msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z,
    msg->pose.pose.orientation.w);
  vehicle_velocity_ = std::make_tuple(
    msg->twist.twist.linear.x, msg->twist.twist.linear.y, msg->twist.twist.linear.z);
  last_odometry_time_ = node_->get_clock()->now();
}

void BlindSpotMonitorModule::objects_callback(
  const autoware_perception_msgs::msg::PredictedObjects::ConstSharedPtr msg)
{
  std::string source_frame = msg->header.frame_id;
  if (source_frame.empty()) {
    RCLCPP_WARN(node_->get_logger(), "[blind_spot] PredictedObjects header.frame_id is empty");
    return;
  }

  geometry_msgs::msg::TransformStamped transform;
  try {
    try {
      rclcpp::Time stamp(msg->header.stamp.sec, msg->header.stamp.nanosec);
      transform = tf_buffer_->lookupTransform(
        target_frame_, source_frame, stamp, rclcpp::Duration::from_seconds(0.05));
    } catch (tf2::TransformException &) {
      transform = tf_buffer_->lookupTransform(
        target_frame_, source_frame, rclcpp::Time(0), rclcpp::Duration::from_seconds(0.1));
    }
  } catch (tf2::TransformException & ex) {
    RCLCPP_DEBUG(
      node_->get_logger(), "[blind_spot] Failed to get TF transform: %s -> %s, error: %s",
      source_frame.c_str(), target_frame_.c_str(), ex.what());
    return;
  }

  bool left_occupied = false;
  bool right_occupied = false;
  bool front_occupied = false;
  bool rear_occupied = false;

  const std::string & gear_upper = vehicle_gear_upper_;
  const std::string & turn_signal_lower = turn_signal_lower_;

  for (const auto & obj : msg->objects) {
    geometry_msgs::msg::PoseStamped pose_stamped;
    pose_stamped.header.frame_id = source_frame;
    pose_stamped.header.stamp = msg->header.stamp;
    pose_stamped.pose = obj.kinematics.initial_pose_with_covariance.pose;

    geometry_msgs::msg::PoseStamped pose_in_base;
    try {
      tf2::doTransform(pose_stamped, pose_in_base, transform);
    } catch (const std::exception & e) {
      RCLCPP_DEBUG(node_->get_logger(), "[blind_spot] Transform failed: %s", e.what());
      continue;
    }

    auto footprint_points = transform_footprint_to_base_link(
      obj, source_frame, rclcpp::Time(msg->header.stamp.sec, msg->header.stamp.nanosec), transform);

    bool in_left = false;
    bool in_right = false;
    bool in_front = false;
    bool in_rear = false;

    double center_x = pose_in_base.pose.position.x;
    double center_y = pose_in_base.pose.position.y;

    if (footprint_points.empty()) {
      double obj_radius = 1.0;
      if (obj.shape.dimensions.x > 0.0 || obj.shape.dimensions.y > 0.0) {
        double obj_length = std::max(obj.shape.dimensions.x, 0.1);
        double obj_width = std::max(obj.shape.dimensions.y, 0.1);
        double hypot_size = std::hypot(obj_length, obj_width);
        obj_radius = std::clamp(hypot_size * 0.5, 0.4, 1.2);
      }
      in_left = check_object_in_zone_simple(center_x, center_y, obj_radius, left_blind_zone_);
      in_right = check_object_in_zone_simple(center_x, center_y, obj_radius, right_blind_zone_);
      in_front = check_object_in_zone_simple(center_x, center_y, obj_radius, front_blind_zone_);
      in_rear = check_object_in_zone_simple(center_x, center_y, obj_radius, rear_blind_zone_);
    } else {
      double footprint_min_x = footprint_points[0].first;
      double footprint_max_x = footprint_points[0].first;
      double footprint_min_y = footprint_points[0].second;
      double footprint_max_y = footprint_points[0].second;
      for (const auto & point : footprint_points) {
        footprint_min_x = std::min(footprint_min_x, point.first);
        footprint_max_x = std::max(footprint_max_x, point.first);
        footprint_min_y = std::min(footprint_min_y, point.second);
        footprint_max_y = std::max(footprint_max_y, point.second);
      }
      in_left = check_footprint_in_zone(footprint_points, left_blind_zone_) ||
        (footprint_max_x >= left_blind_zone_.x_min && footprint_min_x <= left_blind_zone_.x_max &&
        footprint_max_y >= left_blind_zone_.y_min && footprint_min_y <= left_blind_zone_.y_max);
      in_right = check_footprint_in_zone(footprint_points, right_blind_zone_) ||
        (footprint_max_x >= right_blind_zone_.x_min && footprint_min_x <= right_blind_zone_.x_max &&
        footprint_max_y >= right_blind_zone_.y_min && footprint_min_y <= right_blind_zone_.y_max);
      in_front = check_footprint_in_zone(footprint_points, front_blind_zone_) ||
        (footprint_max_x >= front_blind_zone_.x_min && footprint_min_x <= front_blind_zone_.x_max &&
        footprint_max_y >= front_blind_zone_.y_min && footprint_min_y <= front_blind_zone_.y_max);
      in_rear = check_footprint_in_zone(footprint_points, rear_blind_zone_) ||
        (footprint_max_x >= rear_blind_zone_.x_min && footprint_min_x <= rear_blind_zone_.x_max &&
        footprint_max_y >= rear_blind_zone_.y_min && footprint_min_y <= rear_blind_zone_.y_max);
    }

    int zone_count = (in_left ? 1 : 0) + (in_right ? 1 : 0) + (in_front ? 1 : 0) + (in_rear ? 1 : 0);
    if (zone_count > 1) {
      if (in_front && in_rear) {
        if (gear_upper == "R") {
          in_front = false;
        } else {
          in_rear = false;
        }
      }
      if (in_left && in_right) {
        if (turn_signal_lower == "left") {
          in_right = false;
        } else if (turn_signal_lower == "right") {
          in_left = false;
        } else if (center_y > 0) {
          in_right = false;
        } else {
          in_left = false;
        }
      }
      zone_count = (in_left ? 1 : 0) + (in_right ? 1 : 0) + (in_front ? 1 : 0) + (in_rear ? 1 : 0);
      if (zone_count > 1) {
        int left_score = in_left ? 1 : 0;
        int right_score = in_right ? 1 : 0;
        int front_score = in_front ? 1 : 0;
        int rear_score = in_rear ? 1 : 0;
        if (gear_upper == "R") {
          rear_score += 10;
        } else {
          front_score += 10;
        }
        if (turn_signal_lower == "left") {
          left_score += 5;
        } else if (turn_signal_lower == "right") {
          right_score += 5;
        }
        int max_score = std::max({left_score, right_score, front_score, rear_score});
        if (left_score < max_score) in_left = false;
        if (right_score < max_score) in_right = false;
        if (front_score < max_score) in_front = false;
        if (rear_score < max_score) in_rear = false;
      }
    }

    if (in_left) left_occupied = true;
    if (in_right) right_occupied = true;
    if (in_front) front_occupied = true;
    if (in_rear) rear_occupied = true;
  }

  left_warning_.current_occupied = left_occupied;
  right_warning_.current_occupied = right_occupied;
  front_warning_.current_occupied = front_occupied;
  rear_warning_.current_occupied = rear_occupied;
}

std::vector<std::pair<double, double>> BlindSpotMonitorModule::transform_footprint_to_base_link(
  const autoware_perception_msgs::msg::PredictedObject & obj,
  const std::string &,
  const rclcpp::Time &,
  const geometry_msgs::msg::TransformStamped & source_to_base_transform)
{
  std::vector<std::pair<double, double>> footprint_points_in_base;
  if (obj.shape.footprint.points.empty()) {
    return footprint_points_in_base;
  }

  tf2::Transform object_to_source_tf;
  tf2::Quaternion q;
  tf2::fromMsg(obj.kinematics.initial_pose_with_covariance.pose.orientation, q);
  tf2::Vector3 p(
    obj.kinematics.initial_pose_with_covariance.pose.position.x,
    obj.kinematics.initial_pose_with_covariance.pose.position.y,
    obj.kinematics.initial_pose_with_covariance.pose.position.z);
  object_to_source_tf.setOrigin(p);
  object_to_source_tf.setRotation(q);

  tf2::Transform source_to_base_tf;
  tf2::fromMsg(source_to_base_transform.transform, source_to_base_tf);
  tf2::Transform object_to_base_tf = source_to_base_tf * object_to_source_tf;

  for (const auto & point32 : obj.shape.footprint.points) {
    tf2::Vector3 point_local(point32.x, point32.y, point32.z);
    tf2::Vector3 point_base = object_to_base_tf * point_local;
    footprint_points_in_base.emplace_back(point_base.x(), point_base.y());
  }

  return footprint_points_in_base;
}

bool BlindSpotMonitorModule::check_footprint_in_zone(
  const std::vector<std::pair<double, double>> & footprint_points, const BlindSpotZone & zone)
{
  for (const auto & point : footprint_points) {
    if (
      zone.x_min <= point.first && point.first <= zone.x_max && zone.y_min <= point.second &&
      point.second <= zone.y_max)
    {
      return true;
    }
  }
  return false;
}

bool BlindSpotMonitorModule::check_object_in_zone_simple(
  double center_x, double center_y, double radius, const BlindSpotZone & zone)
{
  double expanded_x_min = zone.x_min - radius;
  double expanded_x_max = zone.x_max + radius;
  double expanded_y_min = zone.y_min - radius;
  double expanded_y_max = zone.y_max + radius;
  return expanded_x_min <= center_x && center_x <= expanded_x_max &&
    expanded_y_min <= center_y && center_y <= expanded_y_max;
}

void BlindSpotMonitorModule::update_warning_states()
{
  double current_time = node_->get_clock()->now().seconds();

  auto update_state = [&](WarningState & state, double now_sec) {
    if (state.current_occupied) {
      if (!state.warning_state) {
        if (state.entry_time == 0.0) {
          state.entry_time = now_sec;
        } else if (now_sec - state.entry_time >= entry_delay_sec_) {
          state.warning_state = true;
          state.exit_time = 0.0;
        }
      } else {
        state.entry_time = 0.0;
      }
    } else if (state.warning_state) {
      if (state.exit_time == 0.0) {
        state.exit_time = now_sec;
      } else if (now_sec - state.exit_time >= exit_delay_sec_) {
        state.warning_state = false;
        state.entry_time = 0.0;
      }
    } else {
      state.exit_time = 0.0;
      state.entry_time = 0.0;
    }
  };

  update_state(left_warning_, current_time);
  update_state(right_warning_, current_time);
  update_state(front_warning_, current_time);
  update_state(rear_warning_, current_time);

  auto [left_warn, right_warn, front_warn, rear_warn] = compute_warning(
    vehicle_speed_kmh_, vehicle_gear_, turn_signal_, left_warning_.warning_state,
    right_warning_.warning_state, front_warning_.warning_state, rear_warning_.warning_state);

  pixmoving_hmi_msgs::msg::BlindSpotStatus status_msg;
  status_msg.left_warning = left_warn;
  status_msg.right_warning = right_warn;
  status_msg.front_warning = front_warn;
  status_msg.rear_warning = rear_warn;
  status_pub_->publish(status_msg);
}

std::tuple<bool, bool, bool, bool> BlindSpotMonitorModule::compute_warning(
  double speed_kmh, const std::string & gear, const std::string & turn_signal, bool left_occupied,
  bool right_occupied, bool front_occupied, bool rear_occupied)
{
  bool left_warning = false;
  bool right_warning = false;
  bool front_warning = false;
  bool rear_warning = false;

  std::string gear_upper = gear;
  std::transform(gear_upper.begin(), gear_upper.end(), gear_upper.begin(), ::toupper);
  std::string turn_signal_lower = turn_signal;
  std::transform(turn_signal_lower.begin(), turn_signal_lower.end(), turn_signal_lower.begin(), ::tolower);

  if (speed_kmh < low_speed_threshold_kmh_ && (gear_upper == "D" || gear_upper == "R")) {
    left_warning = left_occupied;
    right_warning = right_occupied;
    if (gear_upper == "D") {
      front_warning = front_occupied;
      rear_warning = rear_occupied;
    } else {
      rear_warning = rear_occupied;
      front_warning = front_occupied;
    }
    return {left_warning, right_warning, front_warning, rear_warning};
  }

  if (speed_kmh >= high_speed_threshold_kmh_) {
    if (turn_signal_lower == "left") {
      left_warning = left_occupied;
      front_warning = front_occupied;
      rear_warning = rear_occupied;
    } else if (turn_signal_lower == "right") {
      right_warning = right_occupied;
      front_warning = front_occupied;
      rear_warning = rear_occupied;
    }
    return {left_warning, right_warning, front_warning, rear_warning};
  }

  return {false, false, false, false};
}

void BlindSpotMonitorModule::publish_zone_markers()
{
  visualization_msgs::msg::MarkerArray marker_array;
  auto stamp = get_suitable_timestamp();
  marker_array.markers.push_back(
    create_zone_marker(0, left_blind_zone_, 1.0, 0.0, 0.0, 0.3, "Left Blind Zone", stamp));
  marker_array.markers.push_back(
    create_zone_marker(1, right_blind_zone_, 0.0, 0.0, 1.0, 0.3, "Right Blind Zone", stamp));
  marker_array.markers.push_back(
    create_zone_marker(2, front_blind_zone_, 0.0, 1.0, 0.0, 0.3, "Front Blind Zone", stamp));
  marker_array.markers.push_back(
    create_zone_marker(3, rear_blind_zone_, 1.0, 1.0, 0.0, 0.3, "Rear Blind Zone", stamp));
  marker_pub_->publish(marker_array);
}

builtin_interfaces::msg::Time BlindSpotMonitorModule::get_suitable_timestamp()
{
  try {
    auto transform = tf_buffer_->lookupTransform(
      "map", target_frame_, rclcpp::Time(0), rclcpp::Duration::from_seconds(0.1));
    return transform.header.stamp;
  } catch (const tf2::TransformException &) {
    builtin_interfaces::msg::Time zero_time;
    zero_time.sec = 0;
    zero_time.nanosec = 0;
    return zero_time;
  }
}

visualization_msgs::msg::Marker BlindSpotMonitorModule::create_zone_marker(
  int marker_id, const BlindSpotZone & zone, double r, double g, double b, double a,
  const std::string & name, builtin_interfaces::msg::Time stamp)
{
  visualization_msgs::msg::Marker marker;
  marker.header.frame_id = target_frame_;
  marker.header.stamp = stamp;
  marker.ns = "blind_spot_zones";
  marker.id = marker_id;
  marker.type = visualization_msgs::msg::Marker::CUBE;
  marker.action = visualization_msgs::msg::Marker::ADD;

  double center_x = (zone.x_min + zone.x_max) / 2.0;
  double center_y = (zone.y_min + zone.y_max) / 2.0;
  double size_x = std::abs(zone.x_max - zone.x_min);
  double size_y = std::abs(zone.y_max - zone.y_min);
  double size_z = 0.1;

  marker.pose.position.x = center_x;
  marker.pose.position.y = center_y;
  marker.pose.position.z = size_z / 2.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = size_x;
  marker.scale.y = size_y;
  marker.scale.z = size_z;
  marker.color.r = r;
  marker.color.g = g;
  marker.color.b = b;
  marker.color.a = a;
  marker.lifetime.sec = 0;
  marker.lifetime.nanosec = 0;
  marker.text = name;
  return marker;
}

}  // namespace robobus_hmi_data_relay::monitors
