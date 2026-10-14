#include <libs/va_chassis_wheel_tire_press_fb.hpp>


VaChassisWheelTirePressFb::VaChassisWheelTirePressFb() {}

void VaChassisWheelTirePressFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaChassisWheelTirePressFb::Parse() {
  vcu_chassis_wheel_tire_press_lf_ = vcuchassiswheeltirepresslf();
  vcu_chassis_wheel_tire_press_rf_ = vcuchassiswheeltirepressrf();
  vcu_chassis_wheel_tire_press_lr_ = vcuchassiswheeltirepresslr();
  vcu_chassis_wheel_tire_press_rr_ = vcuchassiswheeltirepressrr();
}


// config detail: {'bit': 0, 'description': '左前轮胎压', 'is_signed_var': False, 'len': 12, 'name': 'vcu_chassis_wheel_tire_press_lf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|20]', 'physical_unit': 'bar', 'precision': 0.01, 'type': 'double'}
double VaChassisWheelTirePressFb::vcuchassiswheeltirepresslf() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 0));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 16, 'description': '右前轮胎压', 'is_signed_var': False, 'len': 12, 'name': 'vcu_chassis_wheel_tire_press_rf', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|20]', 'physical_unit': 'bar', 'precision': 0.01, 'type': 'double'}
double VaChassisWheelTirePressFb::vcuchassiswheeltirepressrf() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 32, 'description': '左后轮胎压', 'is_signed_var': False, 'len': 12, 'name': 'vcu_chassis_wheel_tire_press_lr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|20]', 'physical_unit': 'bar', 'precision': 0.01, 'type': 'double'}
double VaChassisWheelTirePressFb::vcuchassiswheeltirepresslr() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 48, 'description': '右后轮胎压', 'is_signed_var': False, 'len': 12, 'name': 'vcu_chassis_wheel_tire_press_rr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|20]', 'physical_unit': 'bar', 'precision': 0.01, 'type': 'double'}
double VaChassisWheelTirePressFb::vcuchassiswheeltirepressrr() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 4);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

