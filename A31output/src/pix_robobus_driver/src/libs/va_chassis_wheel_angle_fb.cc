#include <libs/va_chassis_wheel_angle_fb.hpp>


VaChassisWheelAngleFb::VaChassisWheelAngleFb() {}

void VaChassisWheelAngleFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaChassisWheelAngleFb::Parse() {
  vcu_chassis_wheel_angle_lf_ = vcuchassiswheelanglelf();
  vcu_chassis_wheel_angle_rf_ = vcuchassiswheelanglerf();
  vcu_chassis_wheel_angle_lr_ = vcuchassiswheelanglelr();
  vcu_chassis_wheel_angle_rr_ = vcuchassiswheelanglerr();
}


// config detail: {'bit': 0, 'description': '左前轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_lf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelAngleFb::vcuchassiswheelanglelf() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 0));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 16, 'description': '右前轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_rf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelAngleFb::vcuchassiswheelanglerf() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 32, 'description': '左后轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_lr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelAngleFb::vcuchassiswheelanglelr() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 48, 'description': '右后轮转向转角度', 'is_signed_var': True, 'len': 12, 'name': 'vcu_chassis_wheel_angle_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-90|90]', 'physical_unit': 'deg', 'precision': 0.1, 'type': 'double'}
double VaChassisWheelAngleFb::vcuchassiswheelanglerr() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.100000;
  return ret;
}

