#include "robobus_hmi_data_relay/bridges/diagnostic_alarm_bridge_module.hpp"

#include <ament_index_cpp/get_package_share_directory.hpp>
#include <yaml-cpp/yaml.h>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

namespace robobus_hmi_data_relay::bridges
{
namespace
{

std::string toLower(std::string text)
{
  std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return text;
}

bool containsToken(const std::string & text, const std::string & token)
{
  if (text.empty() || token.empty()) {
    return false;
  }
  const auto lower_text = toLower(text);
  const auto lower_token = toLower(token);
  return lower_text == lower_token || lower_text.find(lower_token) != std::string::npos;
}

bool hasValue(
  const diagnostic_msgs::msg::DiagnosticStatus & status, const std::string & key,
  const std::string & expected_value)
{
  if (key.empty() && expected_value.empty()) {
    return true;
  }
  for (const auto & item : status.values) {
    const bool key_matches = key.empty() || containsToken(item.key, key);
    const bool value_matches =
      expected_value.empty() || containsToken(item.value, expected_value);
    if (key_matches && value_matches) {
      return true;
    }
  }
  return (!key.empty() && containsToken(status.message, key)) ||
         (!expected_value.empty() && containsToken(status.message, expected_value));
}

bool matchesSpec(
  const diagnostic_msgs::msg::DiagnosticStatus & status,
  const DiagnosticAlarmBridgeModule::AlarmSpec & spec)
{
  for (const auto & rule : spec.rules) {
    const bool name_matches =
      rule.diagnostic_name.empty() || containsToken(status.name, rule.diagnostic_name);
    const bool hardware_matches =
      rule.hardware_id.empty() || containsToken(status.hardware_id, rule.hardware_id);
    const bool level_matches = rule.diagnostic_level < 0 || status.level == rule.diagnostic_level;
    if (
      name_matches && hardware_matches && level_matches &&
      hasValue(status, rule.value_key, rule.value)) {
      return true;
    }
  }
  return false;
}

uint64_t stampToUnixSeconds(const rclcpp::Node * node, const builtin_interfaces::msg::Time & stamp)
{
  if (stamp.sec > 0) {
    return static_cast<uint64_t>(stamp.sec);
  }
  return static_cast<uint64_t>(node->now().seconds());
}

uint32_t parseCode(const YAML::Node & node)
{
  if (!node) {
    throw std::runtime_error("missing code");
  }
  const auto text = node.as<std::string>();
  std::size_t consumed = 0;
  const auto parsed = std::stoul(text, &consumed, 0);
  if (consumed != text.size() || parsed > UINT32_MAX) {
    std::ostringstream oss;
    oss << "invalid code: " << text;
    throw std::runtime_error(oss.str());
  }
  return static_cast<uint32_t>(parsed);
}

std::string defaultAlarmTablePath()
{
  const auto share_dir = ament_index_cpp::get_package_share_directory("robobus_hmi_data_relay");
  return share_dir + "/config/autopilot_alarm_table.yaml";
}

}  // namespace

DiagnosticAlarmBridgeModule::DiagnosticAlarmBridgeModule(rclcpp::Node * node)
: node_(node)
{
  const auto input_topic = node_->declare_parameter<std::string>(
    "autopilot_diagnostics.input_topic", "/diagnostics");
  const auto output_topic = node_->declare_parameter<std::string>(
    "autopilot_diagnostics.output_topic", "/auto/diagnostics");
  const auto alarm_table_path_param =
    node_->declare_parameter<std::string>("autopilot_diagnostics.alarm_table_path", "");
  const auto alarm_table_path =
    alarm_table_path_param.empty() ? defaultAlarmTablePath() : alarm_table_path_param;

  alarm_specs_ = load_alarm_specs(alarm_table_path);

  auto_diagnostics_pub_ =
    node_->create_publisher<pixmoving_hmi_msgs::msg::AlarmList>(output_topic, rclcpp::QoS(10));
  diagnostics_sub_ = node_->create_subscription<diagnostic_msgs::msg::DiagnosticArray>(
    input_topic, rclcpp::QoS(10),
    std::bind(&DiagnosticAlarmBridgeModule::diagnostics_callback, this, std::placeholders::_1));

  RCLCPP_INFO(
    node_->get_logger(),
    "Autopilot diagnostics alarm bridge initialized: %s -> %s, alarm_table=%s, specs=%zu",
    input_topic.c_str(), output_topic.c_str(), alarm_table_path.c_str(), alarm_specs_.size());
}

std::vector<DiagnosticAlarmBridgeModule::AlarmSpec>
DiagnosticAlarmBridgeModule::load_alarm_specs(const std::string & alarm_table_path) const
{
  std::vector<AlarmSpec> specs;
  try {
    const auto root = YAML::LoadFile(alarm_table_path);
    const auto alarms = root["alarms"];
    if (!alarms || !alarms.IsSequence()) {
      RCLCPP_ERROR(
        node_->get_logger(), "Alarm table %s has no sequence field 'alarms'",
        alarm_table_path.c_str());
      return specs;
    }

    for (const auto & alarm_node : alarms) {
      AlarmSpec spec;
      spec.code = parseCode(alarm_node["code"]);
      spec.level = alarm_node["level"].as<uint8_t>();
      spec.type = alarm_node["type"].as<uint8_t>();
      spec.name = alarm_node["name"].as<std::string>("");
      spec.msg = alarm_node["msg"].as<std::string>(spec.name);

      const auto rules_node = alarm_node["rules"];
      if (rules_node && rules_node.IsSequence()) {
        for (const auto & rule_node : rules_node) {
          MatchRule rule;
          rule.diagnostic_name = rule_node["diagnostic_name"].as<std::string>("");
          rule.hardware_id = rule_node["hardware_id"].as<std::string>("");
          rule.value_key = rule_node["value_key"].as<std::string>("");
          rule.value = rule_node["value"].as<std::string>("");
          rule.diagnostic_level = rule_node["diagnostic_level"].as<int>(-1);
          if (
            !rule.diagnostic_name.empty() || !rule.hardware_id.empty() ||
            !rule.value_key.empty() || !rule.value.empty() || rule.diagnostic_level >= 0) {
            spec.rules.push_back(std::move(rule));
          }
        }
      }

      if (spec.rules.empty() && !spec.name.empty()) {
        MatchRule fallback_rule;
        fallback_rule.diagnostic_name = spec.name;
        spec.rules.push_back(std::move(fallback_rule));
      }
      if (spec.rules.empty()) {
        RCLCPP_WARN(
          node_->get_logger(), "Skip alarm 0x%08X from %s because it has no match rule",
          spec.code, alarm_table_path.c_str());
        continue;
      }
      specs.push_back(std::move(spec));
    }
  } catch (const YAML::Exception & e) {
    RCLCPP_ERROR(
      node_->get_logger(), "Failed to load alarm table %s: %s", alarm_table_path.c_str(),
      e.what());
  } catch (const std::exception & e) {
    RCLCPP_ERROR(
      node_->get_logger(), "Failed to parse alarm table %s: %s", alarm_table_path.c_str(),
      e.what());
  }
  return specs;
}

void DiagnosticAlarmBridgeModule::diagnostics_callback(
  const diagnostic_msgs::msg::DiagnosticArray::ConstSharedPtr msg)
{
  if (!msg) {
    return;
  }

  pixmoving_hmi_msgs::msg::AlarmList out_msg;
  std::unordered_set<uint32_t> added_codes;
  const auto ts = stampToUnixSeconds(node_, msg->header.stamp);

  for (const auto & status : msg->status) {
    if (status.level == diagnostic_msgs::msg::DiagnosticStatus::OK) {
      continue;
    }
    for (const auto & spec : alarm_specs_) {
      if (!matchesSpec(status, spec) || added_codes.count(spec.code) > 0) {
        continue;
      }
      pixmoving_hmi_msgs::msg::Alarm alarm;
      alarm.code = spec.code;
      alarm.level = spec.level;
      alarm.type = spec.type;
      alarm.msg = spec.msg;
      alarm.ts = ts;
      out_msg.alarm_list.push_back(std::move(alarm));
      added_codes.insert(spec.code);
    }
  }

  if (!out_msg.alarm_list.empty()) {
    auto_diagnostics_pub_->publish(out_msg);
  }
}

}  // namespace robobus_hmi_data_relay::bridges
