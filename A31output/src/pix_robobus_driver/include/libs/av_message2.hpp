#pragma once
#include <libs/Byte.hpp>

class AvMessage2 {
public:
	static  int32_t ID;

	AvMessage2();
	void UpdateData(int pwm_red_ctrl, int pwm_green_ctrl, int pwm_blue_ctrl, int atmospherelightbrightness_ctrl);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': 'PWMOUT32', 'is_signed_var': False, 'len': 8, 'name': 'pwm_red_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_pwm_red_ctrl(int pwm_red_ctrl);

  // config detail: {'bit': 8, 'description': 'PWMOUT34', 'is_signed_var': False, 'len': 8, 'name': 'pwm_green_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_pwm_green_ctrl(int pwm_green_ctrl);

  // config detail: {'bit': 16, 'description': 'PWMOUT35', 'is_signed_var': False, 'len': 8, 'name': 'pwm_blue_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_pwm_blue_ctrl(int pwm_blue_ctrl);

  // config detail: {'bit': 24, 'description': '氛围灯亮度', 'is_signed_var': False, 'len': 8, 'name': 'atmospherelightbrightness_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  void set_p_atmospherelightbrightness_ctrl(int atmospherelightbrightness_ctrl);

private:
	uint8_t data[8];
};



