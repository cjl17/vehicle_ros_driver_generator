// chassis_interface_common.hpp 中工具函数的实现。

#include "pixmoving_chassis_interface/chassis_interface_common.hpp"

#include <cmath>

namespace pixmoving
{
namespace chassis
{
namespace interface
{

float ChassisInterfaceUtils::calculateDistance(const geometry_msgs::msg::Point& p1, const geometry_msgs::msg::Point& p2)
{
  const double dx = p1.x - p2.x;
  const double dy = p1.y - p2.y;
  const double dz = p1.z - p2.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::string ChassisInterfaceUtils::driveModeToString(int8_t mode)
{
  DriveMode driver_mode = DriveMode::UNKNOWN;
  switch (mode)
  {
    case 1:
      driver_mode = DriveMode::MANUAL_CONTROL;
      break;
    case 2:
      driver_mode = DriveMode::REMOTE_NETWORK;
      break;
    case 3:
      driver_mode = DriveMode::EMERGENCY_STOP;
      break;
    case -1:
      driver_mode = DriveMode::UNKNOWN;
      break;
    case 4:
      driver_mode = DriveMode::AUTO_STANDBY;
      break;
    case 5:
      driver_mode = DriveMode::AUTO_EXECUTING;
      break;
    case 6:
      driver_mode = DriveMode::AUTO_TAKEOVER_MANUAL;
      break;
    case 7:
      driver_mode = DriveMode::AUTO_TAKEOVER_BRAKE;
      break;
    case 8:
      driver_mode = DriveMode::AUTO_DONE_NORMAL;
      break;
    case 9:
      driver_mode = DriveMode::AUTO_DONE_NEAR;
      break;
    case 10:
      driver_mode = DriveMode::AUTO_CANCEL_TAKEOVER;
      break;
    case 11:
      driver_mode = DriveMode::AUTO_CANCEL_NEW_TASK;
      break;
    case 12:
      driver_mode = DriveMode::AUTO_DONE_ESTOP_NEAR;
      break;
    default:
      driver_mode = DriveMode::UNKNOWN;
      break;
  }

  switch (driver_mode)
  {
    case DriveMode::MANUAL_CONTROL:
      return "遥控模式";
    case DriveMode::REMOTE_NETWORK:
      return "远程模式";
    case DriveMode::EMERGENCY_STOP:
      return "紧急停止";
    case DriveMode::UNKNOWN:
      return "未知";
    case DriveMode::AUTO_STANDBY:
      return "自驾待命";
    case DriveMode::AUTO_EXECUTING:
      return "自驾执行";
    case DriveMode::AUTO_TAKEOVER_MANUAL:
      return "遥控接管";
    case DriveMode::AUTO_TAKEOVER_BRAKE:
      return "刹车接管";
    case DriveMode::AUTO_DONE_NORMAL:
      return "正常完成";
    case DriveMode::AUTO_DONE_NEAR:
      return "附近完成";
    case DriveMode::AUTO_CANCEL_TAKEOVER:
      return "接管取消";
    case DriveMode::AUTO_CANCEL_NEW_TASK:
      return "新任务取消";
    case DriveMode::AUTO_DONE_ESTOP_NEAR:
      return "终点附近急停结束";
    default:
      return "未定义";
  }
}

int8_t ChassisInterfaceUtils::toInt8(DriveMode mode)
{
  return static_cast<int8_t>(mode);
}

double ChassisInterfaceUtils::yawFromQuaternion(const geometry_msgs::msg::Quaternion& q)
{
  return std::atan2(2.0 * (q.w * q.z + q.x * q.y), 1.0 - 2.0 * (q.y * q.y + q.z * q.z));
}

double ChassisInterfaceUtils::angleDifference(double yaw1, double yaw2)
{
  double diff = yaw1 - yaw2;
  while (diff > M_PI)
  {
    diff -= 2.0 * M_PI;
  }
  while (diff < -M_PI)
  {
    diff += 2.0 * M_PI;
  }
  return std::fabs(diff);
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
