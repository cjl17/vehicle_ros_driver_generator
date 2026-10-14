#ifndef ROBOBUS_HMI_DATA_RELAY__PUBLISHERS__SWITCH_MANAGER_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__PUBLISHERS__SWITCH_MANAGER_MODULE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

namespace robobus_hmi_data_relay::publishers
{

class SwitchManagerModule
{
public:
  explicit SwitchManagerModule(rclcpp::Node * node);

private:
  void tick();

  rclcpp::Node * node_;
  rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr circular_switch_client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace robobus_hmi_data_relay::publishers

#endif
