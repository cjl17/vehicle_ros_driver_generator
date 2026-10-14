#include "robobus_hmi_data_relay/monitors/health_monitor_module.hpp"

namespace robobus_hmi_data_relay::monitors
{

HealthMonitorModule::HealthMonitorModule(rclcpp::Node * node)
: node_(node)
{
  publisher_ = node_->create_publisher<std_msgs::msg::String>("/system/health_monitor_text", 1);
  timer_ = node_->create_wall_timer(
    std::chrono::minutes(5), std::bind(&HealthMonitorModule::publish_health, this));
  publish_health();
}

void HealthMonitorModule::publish_health() const
{
  std_msgs::msg::String msg;
  msg.data = "health monitor active";
  publisher_->publish(msg);
}

}  // namespace robobus_hmi_data_relay::monitors
