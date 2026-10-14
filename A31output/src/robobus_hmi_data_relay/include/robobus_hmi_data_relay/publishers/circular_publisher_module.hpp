#ifndef ROBOBUS_HMI_DATA_RELAY__PUBLISHERS__CIRCULAR_PUBLISHER_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__PUBLISHERS__CIRCULAR_PUBLISHER_MODULE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

#include <autoware_internal_planning_msgs/msg/velocity_limit.hpp>
#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <autoware_vehicle_msgs/msg/engage.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

namespace robobus_hmi_data_relay::publishers
{

class CircularPublisherModule
{
public:
  explicit CircularPublisherModule(rclcpp::Node * node);

private:
  void handle_switch(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
    std::shared_ptr<std_srvs::srv::SetBool::Response> response);

  rclcpp::Node * node_;
  bool enabled_{false};
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr switch_service_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::Engage>::SharedPtr engage_pub_;
  rclcpp::Publisher<autoware_internal_planning_msgs::msg::VelocityLimit>::SharedPtr velocity_limit_pub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pub_;
  rclcpp::Subscription<autoware_system_msgs::msg::AutowareState>::SharedPtr autoware_state_sub_;
};

}  // namespace robobus_hmi_data_relay::publishers

#endif
