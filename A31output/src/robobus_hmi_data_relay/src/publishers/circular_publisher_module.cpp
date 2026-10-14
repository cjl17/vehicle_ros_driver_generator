#include "robobus_hmi_data_relay/publishers/circular_publisher_module.hpp"

namespace robobus_hmi_data_relay::publishers
{

CircularPublisherModule::CircularPublisherModule(rclcpp::Node * node)
: node_(node)
{
  switch_service_ = node_->create_service<std_srvs::srv::SetBool>(
    "/circular_publisher/switch",
    std::bind(&CircularPublisherModule::handle_switch, this, std::placeholders::_1, std::placeholders::_2));
  engage_pub_ = node_->create_publisher<autoware_vehicle_msgs::msg::Engage>("/autoware/engage", 5);
  velocity_limit_pub_ = node_->create_publisher<autoware_internal_planning_msgs::msg::VelocityLimit>(
    "/planning/scenario_planning/max_velocity_default", rclcpp::QoS(1).transient_local());
  goal_pub_ = node_->create_publisher<geometry_msgs::msg::PoseStamped>("/planning/mission_planning/goal", 5);
  autoware_state_sub_ = node_->create_subscription<autoware_system_msgs::msg::AutowareState>(
    "/autoware/state", 1, [](const autoware_system_msgs::msg::AutowareState::SharedPtr) {});
}

void CircularPublisherModule::handle_switch(
  const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
  std::shared_ptr<std_srvs::srv::SetBool::Response> response)
{
  enabled_ = request->data;
  response->success = true;
  response->message = enabled_ ? "circular run enabled" : "circular run disabled";
}

}  // namespace robobus_hmi_data_relay::publishers
