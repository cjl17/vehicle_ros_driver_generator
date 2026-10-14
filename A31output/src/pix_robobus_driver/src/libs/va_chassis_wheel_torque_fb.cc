#include <libs/va_chassis_wheel_torque_fb.hpp>


VaChassisWheelTorqueFb::VaChassisWheelTorqueFb() {}

void VaChassisWheelTorqueFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaChassisWheelTorqueFb::Parse() {
  vcu_chassis_torque_lf_ = vcuchassistorquelf();
  vcu_chassis_torque_rf_ = vcuchassistorquerf();
  vcu_chassis_torque_lr_ = vcuchassistorquelr();
  vcu_chassis_torque_rr_ = vcuchassistorquerr();
}


// config detail: {'bit': 0, 'description': '左前轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_lf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelTorqueFb::vcuchassistorquelf() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 0));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 16, 'description': '右前轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_rf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelTorqueFb::vcuchassistorquerf() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 32, 'description': '左后轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_lr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelTorqueFb::vcuchassistorquelr() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 48, 'description': '右后轮扭矩', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_torque_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelTorqueFb::vcuchassistorquerr() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.100000;
  return ret;
}

