#include "robobus_hmi_data_relay/publishers/switch_manager_module.hpp"

namespace robobus_hmi_data_relay::publishers
{

SwitchManagerModule::SwitchManagerModule(rclcpp::Node * node)
: node_(node)
{
  circular_switch_client_ = node_->create_client<std_srvs::srv::SetBool>("/circular_publisher/switch");
  timer_ = node_->create_wall_timer(
    std::chrono::milliseconds(500), std::bind(&SwitchManagerModule::tick, this));
}

void SwitchManagerModule::tick()
{
  if (!circular_switch_client_->service_is_ready()) {
    return;
  }
  auto request = std::make_shared<std_srvs::srv::SetBool::Request>();
  request->data = false;
  circular_switch_client_->async_send_request(request);
  timer_->cancel();
}

}  // namespace robobus_hmi_data_relay::publishers
