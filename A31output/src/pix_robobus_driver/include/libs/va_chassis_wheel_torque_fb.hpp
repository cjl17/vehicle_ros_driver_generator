#pragma once

#include <libs/Byte.hpp>

class VaChassisWheelTorqueFb {
public:
  static const uint32_t ID = 0x542;
  VaChassisWheelTorqueFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  double vcu_chassis_torque_lf_;
  double vcu_chassis_torque_rf_;
  double vcu_chassis_torque_lr_;
  double vcu_chassis_torque_rr_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '左前轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_lf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  double vcuchassistorquelf();

  // config detail: {'bit': 16, 'description': '右前轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_rf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  double vcuchassistorquerf();

  // config detail: {'bit': 32, 'description': '左后轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_lr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  double vcuchassistorquelr();

  // config detail: {'bit': 48, 'description': '右后轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  double vcuchassistorquerr();
};



