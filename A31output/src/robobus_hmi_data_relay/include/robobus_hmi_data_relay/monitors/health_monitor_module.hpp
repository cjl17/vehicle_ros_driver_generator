#ifndef ROBOBUS_HMI_DATA_RELAY__MONITORS__HEALTH_MONITOR_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__MONITORS__HEALTH_MONITOR_MODULE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace robobus_hmi_data_relay::monitors
{

class HealthMonitorModule
{
public:
  explicit HealthMonitorModule(rclcpp::Node * node);

private:
  void publish_health() const;

  rclcpp::Node * node_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace robobus_hmi_data_relay::monitors

#endif
