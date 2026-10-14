#pragma once

#include <libs/Byte.hpp>

class VaChassisWheelRpmFb {
public:
  static const uint32_t ID = 0x539;
  VaChassisWheelRpmFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_chassis_wheel_rpm_lf_;
  int vcu_chassis_wheel_rpm_rf_;
  int vcu_chassis_wheel_rpm_lr_;
  int vcu_chassis_wheel_rpm_rr_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '左前轮转速', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_wheel_rpm_lf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-2000|2000]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
  int vcuchassiswheelrpmlf();

  // config detail: {'bit': 16, 'description': '右前轮转速', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_wheel_rpm_rf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-2000|2000]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
  int vcuchassiswheelrpmrf();

  // config detail: {'bit': 32, 'description': '左后轮转速', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_wheel_rpm_lr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-2000|2000]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
  int vcuchassiswheelrpmlr();

  // config detail: {'bit': 48, 'description': '右后轮转速', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_wheel_rpm_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-2000|2000]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
  int vcuchassiswheelrpmrr();
};



