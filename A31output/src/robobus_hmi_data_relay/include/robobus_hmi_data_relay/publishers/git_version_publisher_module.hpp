#ifndef ROBOBUS_HMI_DATA_RELAY__PUBLISHERS__GIT_VERSION_PUBLISHER_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__PUBLISHERS__GIT_VERSION_PUBLISHER_MODULE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <string>

namespace robobus_hmi_data_relay::publishers
{

class GitVersionPublisherModule
{
public:
  explicit GitVersionPublisherModule(rclcpp::Node * node);

private:
  void publish_once(const std::string & json_path) const;

  rclcpp::Node * node_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

}  // namespace robobus_hmi_data_relay::publishers

#endif
