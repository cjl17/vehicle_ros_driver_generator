#ifndef ROBOBUS_HMI_DATA_RELAY__MONITORS__BLIND_SPOT_MONITOR_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__MONITORS__BLIND_SPOT_MONITOR_MODULE_HPP_

#include <memory>
#include <string>
#include <deque>
#include <tuple>
#include <cmath>
#include <optional>
#include <map>
#include <vector>
#include <algorithm>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <pixmoving_hmi_msgs/msg/blind_spot_status.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

#include <autoware_perception_msgs/msg/predicted_objects.hpp>
#include <pixmoving_hmi_msgs/msg/vehicle_info.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <builtin_interfaces/msg/time.hpp>

namespace robobus_hmi_data_relay::monitors
{

struct BlindSpotZone
{
  double x_min;
  double x_max;
  double y_min;
  double y_max;
};

struct WarningState
{
  bool current_occupied;
  bool warning_state;
  double entry_time;
  double exit_time;
};

class BlindSpotMonitorModule
{
public:
  explicit BlindSpotMonitorModule(rclcpp::Node * node);

private:
  double declare_compat_double_parameter(
      const std::string & primary_name, const std::string & legacy_name, double default_value) const;
  void objects_callback(const autoware_perception_msgs::msg::PredictedObjects::ConstSharedPtr msg);
  void vehicle_info_callback(const pixmoving_hmi_msgs::msg::VehicleInfo::ConstSharedPtr msg);
  void odometry_callback(const nav_msgs::msg::Odometry::ConstSharedPtr msg);
  void update_warning_states();
  void publish_zone_markers();
  bool check_footprint_in_zone(const std::vector<std::pair<double, double>>& footprint_points,
                               const BlindSpotZone& zone);
  bool check_object_in_zone_simple(double center_x, double center_y, double radius, const BlindSpotZone& zone);
  std::tuple<bool, bool, bool, bool> compute_warning(double speed_kmh, const std::string& gear,
                                                     const std::string& turn_signal, bool left_occupied,
                                                     bool right_occupied, bool front_occupied, bool rear_occupied);
  visualization_msgs::msg::Marker create_zone_marker(int marker_id, const BlindSpotZone& zone, double r, double g,
                                                     double b, double a, const std::string& name,
                                                     builtin_interfaces::msg::Time stamp);
  builtin_interfaces::msg::Time get_suitable_timestamp();
  std::vector<std::pair<double, double>> transform_footprint_to_base_link(
      const autoware_perception_msgs::msg::PredictedObject& obj,
      const std::string& source_frame,
      const rclcpp::Time& msg_stamp,
      const geometry_msgs::msg::TransformStamped& source_to_base_transform);

  rclcpp::Node * node_;
  BlindSpotZone left_blind_zone_;
  BlindSpotZone right_blind_zone_;
  BlindSpotZone front_blind_zone_;
  BlindSpotZone rear_blind_zone_;
  double low_speed_threshold_kmh_;
  double high_speed_threshold_kmh_;
  double entry_delay_sec_;
  double exit_delay_sec_;
  std::string target_frame_;

  double vehicle_speed_kmh_;
  std::string vehicle_gear_;
  std::string vehicle_gear_upper_;
  std::string turn_signal_;
  std::string turn_signal_lower_;
  rclcpp::Time last_vehicle_info_time_;

  std::optional<std::tuple<double, double, double>> vehicle_position_;
  std::optional<std::tuple<double, double, double, double>> vehicle_orientation_;
  std::optional<std::tuple<double, double, double>> vehicle_velocity_;
  rclcpp::Time last_odometry_time_;

  WarningState left_warning_;
  WarningState right_warning_;
  WarningState front_warning_;
  WarningState rear_warning_;

  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;

  rclcpp::Subscription<autoware_perception_msgs::msg::PredictedObjects>::SharedPtr objects_sub_;
  rclcpp::Subscription<pixmoving_hmi_msgs::msg::VehicleInfo>::SharedPtr vehicle_info_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odometry_sub_;

  rclcpp::Publisher<pixmoving_hmi_msgs::msg::BlindSpotStatus>::SharedPtr status_pub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;

  rclcpp::TimerBase::SharedPtr warning_timer_;
  rclcpp::TimerBase::SharedPtr marker_timer_;
};

}  // namespace robobus_hmi_data_relay::monitors

#endif
