#ifndef ROBOBUS_HMI_DATA_RELAY__BRIDGES__PIXMOVING_VEHICLE_DISPLAY_BRIDGE_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__BRIDGES__PIXMOVING_VEHICLE_DISPLAY_BRIDGE_MODULE_HPP_

#include <builtin_interfaces/msg/time.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <std_msgs/msg/float32.hpp>
#include <tier4_external_api_msgs/srv/set_door.hpp>
#include <tier4_vehicle_msgs/msg/actuation_status_stamped.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <autoware_internal_debug_msgs/msg/float32_stamped.hpp>
#include <autoware_perception_msgs/msg/predicted_objects.hpp>
#include <autoware_perception_msgs/msg/traffic_light_group_array.hpp>
#include <autoware_planning_msgs/msg/path.hpp>
#include <autoware_planning_msgs/msg/trajectory.hpp>
#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/engage.hpp>
#include <autoware_vehicle_msgs/msg/gear_report.hpp>
#include <autoware_vehicle_msgs/msg/steering_report.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>

#include <pixmoving_hmi_msgs/msg/alarm.hpp>
#include <pixmoving_hmi_msgs/msg/app_comm.hpp>
#include <pixmoving_hmi_msgs/msg/autoware_info.hpp>
#include <pixmoving_hmi_msgs/msg/sensor_info.hpp>
#include <pixmoving_hmi_msgs/msg/system_volume_report.hpp>
#include <pixmoving_hmi_msgs/msg/v2d_all_station_info.hpp>
#include <pixmoving_hmi_msgs/msg/v2d_current_station_info.hpp>
#include <pixmoving_hmi_msgs/msg/vehicle_info.hpp>
#include <pixmoving_hmi_msgs/srv/app_control.hpp>
#include <pixmoving_hmi_msgs/srv/get_ipc_info.hpp>
#include <pixmoving_hmi_msgs/srv/ota_cmd.hpp>

#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace robobus_hmi_data_relay::bridges
{

class PixmovingVehicleDisplayBridgeModule
{
public:
  explicit PixmovingVehicleDisplayBridgeModule(rclcpp::Node * node);

private:
  template<typename MsgT>
  void create_ipc_to_hmi_forwarder(const std::string & input_topic)
  {
    auto output_topic = "hmi_input" + input_topic;
    auto publisher = node_->create_publisher<MsgT>(output_topic, 10);
    ipc_publishers_.push_back(publisher);
    auto subscription = node_->create_subscription<MsgT>(
      input_topic, 10,
      [publisher](const typename MsgT::SharedPtr msg) {
        publisher->publish(*msg);
      });
    subscriptions_.push_back(subscription);
  }

  template<typename MsgT>
  void create_hmi_to_ipc_forwarder(const std::string & input_topic)
  {
    std::string output_topic = input_topic;
    const std::string prefix = "hmi_output/";
    if (output_topic.rfind(prefix, 0) == 0) {
      output_topic.erase(0, prefix.size());
    }
    auto publisher = node_->create_publisher<MsgT>(output_topic, 10);
    hmi_publishers_.push_back(publisher);
    auto subscription = node_->create_subscription<MsgT>(
      input_topic, 10,
      [publisher](const typename MsgT::SharedPtr msg) {
        publisher->publish(*msg);
      });
    subscriptions_.push_back(subscription);
  }

  void setup_forwarders();
  void setup_services();
  void setup_clients();
  void on_alarm(const pixmoving_hmi_msgs::msg::Alarm::SharedPtr msg);
  void handle_app_control(
    const std::shared_ptr<rmw_request_id_t>,
    const std::shared_ptr<pixmoving_hmi_msgs::srv::AppControl::Request> request,
    std::shared_ptr<pixmoving_hmi_msgs::srv::AppControl::Response> response);
  void handle_get_ipc_info(
    const std::shared_ptr<rmw_request_id_t>,
    const std::shared_ptr<pixmoving_hmi_msgs::srv::GetIPCInfo::Request>,
    std::shared_ptr<pixmoving_hmi_msgs::srv::GetIPCInfo::Response> response);
  void publish_system_volume();
  std::optional<int> get_system_volume() const;
  void set_system_volume(int volume) const;
  void execute_tool(const std::string & tool_name) const;
  std::string get_auto_driving_version() const;
  void send_set_door_request(bool open);
  void send_ota_cmd_request(int8_t mode);

  rclcpp::Node * node_;
  std::string tools_path_;
  bool has_pactl_{false};
  std::vector<rclcpp::SubscriptionBase::SharedPtr> subscriptions_;
  std::vector<rclcpp::PublisherBase::SharedPtr> ipc_publishers_;
  std::vector<rclcpp::PublisherBase::SharedPtr> hmi_publishers_;
  rclcpp::Subscription<pixmoving_hmi_msgs::msg::Alarm>::SharedPtr alarm_sub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::SystemVolumeReport>::SharedPtr system_volume_pub_;
  rclcpp::TimerBase::SharedPtr system_volume_timer_;
  rclcpp::Service<pixmoving_hmi_msgs::srv::AppControl>::SharedPtr app_control_service_;
  rclcpp::Service<pixmoving_hmi_msgs::srv::GetIPCInfo>::SharedPtr get_ipc_info_service_;
  rclcpp::Client<tier4_external_api_msgs::srv::SetDoor>::SharedPtr door_client_;
  rclcpp::Client<pixmoving_hmi_msgs::srv::OtaCmd>::SharedPtr ota_client_;
};

}  // namespace robobus_hmi_data_relay::bridges

#endif
