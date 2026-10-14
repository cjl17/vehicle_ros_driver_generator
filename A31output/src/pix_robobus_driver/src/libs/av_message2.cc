#include <libs/av_message2.hpp>

int32_t AvMessage2::ID = 0x5FB;

// public
AvMessage2::AvMessage2() { Reset(); }

void AvMessage2::UpdateData(int pwm_red_ctrl, int pwm_green_ctrl, int pwm_blue_ctrl, int atmospherelightbrightness_ctrl) {
  set_p_pwm_red_ctrl(pwm_red_ctrl);
  set_p_pwm_green_ctrl(pwm_green_ctrl);
  set_p_pwm_blue_ctrl(pwm_blue_ctrl);
  set_p_atmospherelightbrightness_ctrl(atmospherelightbrightness_ctrl);
}

void AvMessage2::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvMessage2::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': 'PWMOUT32', 'is_signed_var': False, 'len': 8, 'name': 'pwm_red_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvMessage2::set_p_pwm_red_ctrl(int pwm_red_ctrl) {
  // pwm_red_ctrl = ProtocolData::BoundedValue(0, 255, pwm_red_ctrl);
  int x = pwm_red_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': 'PWMOUT34', 'is_signed_var': False, 'len': 8, 'name': 'pwm_green_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvMessage2::set_p_pwm_green_ctrl(int pwm_green_ctrl) {
  // pwm_green_ctrl = ProtocolData::BoundedValue(0, 255, pwm_green_ctrl);
  int x = pwm_green_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'description': 'PWMOUT35', 'is_signed_var': False, 'len': 8, 'name': 'pwm_blue_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvMessage2::set_p_pwm_blue_ctrl(int pwm_blue_ctrl) {
  // pwm_blue_ctrl = ProtocolData::BoundedValue(0, 255, pwm_blue_ctrl);
  int x = pwm_blue_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 24, 'description': '氛围灯亮度', 'is_signed_var': False, 'len': 8, 'name': 'atmospherelightbrightness_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
void AvMessage2::set_p_atmospherelightbrightness_ctrl(int atmospherelightbrightness_ctrl) {
  // atmospherelightbrightness_ctrl = ProtocolData::BoundedValue(0, 100, atmospherelightbrightness_ctrl);
  int x = atmospherelightbrightness_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[3] += to_set.return_byte_t();
  
}


