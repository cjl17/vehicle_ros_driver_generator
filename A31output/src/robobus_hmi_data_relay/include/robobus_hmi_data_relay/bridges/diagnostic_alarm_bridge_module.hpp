#ifndef ROBOBUS_HMI_DATA_RELAY__BRIDGES__DIAGNOSTIC_ALARM_BRIDGE_MODULE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__BRIDGES__DIAGNOSTIC_ALARM_BRIDGE_MODULE_HPP_

#include <rclcpp/rclcpp.hpp>

#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <pixmoving_hmi_msgs/msg/alarm_list.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace robobus_hmi_data_relay::bridges
{

class DiagnosticAlarmBridgeModule
{
public:
  explicit DiagnosticAlarmBridgeModule(rclcpp::Node * node);

  struct MatchRule
  {
    std::string diagnostic_name;
    std::string hardware_id;
    std::string value_key;
    std::string value;
    int diagnostic_level{-1};
  };

  struct AlarmSpec
  {
    uint32_t code;
    uint8_t level;
    uint8_t type;
    std::string name;
    std::string msg;
    std::vector<MatchRule> rules;
  };

private:
  std::vector<AlarmSpec> load_alarm_specs(const std::string & alarm_table_path) const;
  void diagnostics_callback(const diagnostic_msgs::msg::DiagnosticArray::ConstSharedPtr msg);

  rclcpp::Node * node_;
  std::vector<AlarmSpec> alarm_specs_;
  rclcpp::Subscription<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr diagnostics_sub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::AlarmList>::SharedPtr auto_diagnostics_pub_;
};

}  // namespace robobus_hmi_data_relay::bridges

#endif  // ROBOBUS_HMI_DATA_RELAY__BRIDGES__DIAGNOSTIC_ALARM_BRIDGE_MODULE_HPP_
