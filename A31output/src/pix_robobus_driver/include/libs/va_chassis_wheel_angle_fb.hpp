#pragma once

#include <libs/Byte.hpp>

class VaChassisWheelAngleFb {
public:
  static const uint32_t ID = 0x541;
  VaChassisWheelAngleFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  double vcu_chassis_wheel_angle_lf_;
  double vcu_chassis_wheel_angle_rf_;
  double vcu_chassis_wheel_angle_lr_;
  double vcu_chassis_wheel_angle_rr_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '左前轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_lf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  double vcuchassiswheelanglelf();

  // config detail: {'bit': 16, 'description': '右前轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_rf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  double vcuchassiswheelanglerf();

  // config detail: {'bit': 32, 'description': '左后轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_lr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  double vcuchassiswheelanglelr();

  // config detail: {'bit': 48, 'description': '右后轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
  double vcuchassiswheelanglerr();
};



