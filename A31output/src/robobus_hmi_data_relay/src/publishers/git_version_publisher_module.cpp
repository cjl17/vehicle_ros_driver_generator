#include "robobus_hmi_data_relay/publishers/git_version_publisher_module.hpp"

#include <fstream>
#include <sstream>

namespace robobus_hmi_data_relay::publishers
{

GitVersionPublisherModule::GitVersionPublisherModule(rclcpp::Node * node)
: node_(node)
{
  auto qos = rclcpp::QoS(1).reliable().transient_local();
  publisher_ = node_->create_publisher<std_msgs::msg::String>(
    "/app/cloud_control_platform/git_version", qos);
  const auto json_path = node_->declare_parameter<std::string>("git_version_json_path", "");
  publish_once(json_path);
}

void GitVersionPublisherModule::publish_once(const std::string & json_path) const
{
  std_msgs::msg::String msg;
  if (json_path.empty()) {
    msg.data =
      "Branch: unknown, Commit: unknown, Author: unknown, Commit Time: unknown, Message: unknown, Build: unknown";
  } else {
    std::ifstream input(json_path);
    std::stringstream buffer;
    buffer << input.rdbuf();
    msg.data = buffer.str();
    if (msg.data.empty()) {
      msg.data =
        "Branch: unknown, Commit: unknown, Author: unknown, Commit Time: unknown, Message: unknown, Build: unknown";
    }
  }
  publisher_->publish(msg);
}

}  // namespace robobus_hmi_data_relay::publishers
