#include <libs/dp_messgae5.hpp>


DpMessgae5::DpMessgae5() {}

void DpMessgae5::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void DpMessgae5::Parse() {
  pwm_red_sta_ = pwmredsta();
  pwm_green_sta_ = pwmgreensta();
  pwm_blue_sta_ = pwmbluesta();
  atmospherelightbrightness_ = atmospherelightbrightness();
}


// config detail: {'bit': 0, 'description': 'PWMOUT32', 'is_signed_var': False, 'len': 8, 'name': 'pwm_red_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int DpMessgae5::pwmredsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': 'PWMOUT34', 'is_signed_var': False, 'len': 8, 'name': 'pwm_green_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int DpMessgae5::pwmgreensta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 16, 'description': 'PWMOUT35', 'is_signed_var': False, 'len': 8, 'name': 'pwm_blue_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int DpMessgae5::pwmbluesta() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'description': '氛围灯亮度', 'is_signed_var': False, 'len': 8, 'name': 'atmospherelightbrightness', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int DpMessgae5::atmospherelightbrightness() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

