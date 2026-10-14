#pragma once

#include <libs/Byte.hpp>

class DpMessgae5 {
public:
  static const uint32_t ID = 0x6F5;
  DpMessgae5();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int pwm_red_sta_;
  int pwm_green_sta_;
  int pwm_blue_sta_;
  int atmospherelightbrightness_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': 'PWMOUT32', 'is_signed_var': False, 'len': 8, 'name': 'pwm_red_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int pwmredsta();

  // config detail: {'bit': 8, 'description': 'PWMOUT34', 'is_signed_var': False, 'len': 8, 'name': 'pwm_green_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int pwmgreensta();

  // config detail: {'bit': 16, 'description': 'PWMOUT35', 'is_signed_var': False, 'len': 8, 'name': 'pwm_blue_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int pwmbluesta();

  // config detail: {'bit': 24, 'description': '氛围灯亮度', 'is_signed_var': False, 'len': 8, 'name': 'atmospherelightbrightness', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  int atmospherelightbrightness();
};



