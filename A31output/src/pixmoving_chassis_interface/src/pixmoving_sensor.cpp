// 传感器相关回调（GNSS、Heading 等）放在此文件，便于模块化管理。

#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

namespace pixmoving
{
namespace chassis
{
namespace interface
{

void PixmovingChassisInterfaceNode::onNavSatFix(const sensor_msgs::msg::NavSatFix::ConstSharedPtr& msg)
{
  const bool has_fix = msg->status.status >= sensor_msgs::msg::NavSatStatus::STATUS_FIX;
  if (has_fix)
  {
    sensor_info_msg_.gps_located = true;
    sensor_info_msg_.gps_strength = 80;
  }
  else
  {
    sensor_info_msg_.gps_located = false;
    sensor_info_msg_.gps_strength = 30;
  }

  sensor_info_msg_.sat_cnt = 23;

  if (msg->latitude == 0.0 && msg->longitude == 0.0 && msg->altitude == 0.0)
  {
    last_gnss_fix_valid_ = false;
    gnss_valid_streak_ = 0;
    return;
  }

  sensor_info_msg_.lat = msg->latitude;
  sensor_info_msg_.lng = msg->longitude;
  sensor_info_msg_.alt = msg->altitude;

  if (has_fix)
  {
    latest_valid_gnss_fix_ptr_ = msg;
    last_gnss_fix_time_ = this->now();
    last_gnss_fix_valid_ = true;
    ++gnss_valid_streak_;
  }
  else
  {
    last_gnss_fix_valid_ = false;
    gnss_valid_streak_ = 0;
  }
}

void PixmovingChassisInterfaceNode::onHeading(const std_msgs::msg::Float32::ConstSharedPtr& msg)
{
  sensor_info_msg_.angle = msg->data;
}

void PixmovingChassisInterfaceNode::onSatellitesNumber1(const std_msgs::msg::UInt8::ConstSharedPtr& msg)
{
  sensor_info_msg_.sat_cnt = std::max(static_cast<uint8_t>(sensor_info_msg_.sat_cnt), msg->data);
}

void PixmovingChassisInterfaceNode::onSatellitesNumber2(const std_msgs::msg::UInt8::ConstSharedPtr& msg)
{
  sensor_info_msg_.sat_cnt = std::max(static_cast<uint8_t>(sensor_info_msg_.sat_cnt), msg->data);
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
