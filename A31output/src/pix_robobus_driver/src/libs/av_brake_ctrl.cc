#include <libs/av_brake_ctrl.hpp>

int32_t AvBrakeCtrl::ID = 0x131;

// public
AvBrakeCtrl::AvBrakeCtrl() { Reset(); }

void AvBrakeCtrl::UpdateData(int acu_chassis_brake_en, int acu_chassis_brake_lamp_ctrl, int acu_chassis_aeb_ctrl, double acu_chassis_brake_pdl_target, int acu_chassis_epb_ctrl, int acu_brake_life_sig, int acu_check_sum131) {
  set_p_acu_chassis_brake_en(acu_chassis_brake_en);
  set_p_acu_chassis_brake_lamp_ctrl(acu_chassis_brake_lamp_ctrl);
  set_p_acu_chassis_aeb_ctrl(acu_chassis_aeb_ctrl);
  set_p_acu_chassis_brake_pdl_target(acu_chassis_brake_pdl_target);
  set_p_acu_chassis_epb_ctrl(acu_chassis_epb_ctrl);
  set_p_acu_brake_life_sig(acu_brake_life_sig);
  set_p_acu_check_sum131(acu_check_sum131);
}

void AvBrakeCtrl::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvBrakeCtrl::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '车辆刹车控制使能', 'enum': {0: 'ACU_CHASSIS_BRAKE_EN_DISABLE', 1: 'ACU_CHASSIS_BRAKE_EN_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_brake_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvBrakeCtrl::set_p_acu_chassis_brake_en(int acu_chassis_brake_en) {
  int x = acu_chassis_brake_en;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 1, 'description': '车辆刹车灯控制', 'enum': {0: 'ACU_CHASSIS_BRAKE_LAMP_CTRL_OFF_与VCU控制制动灯是或的关系', 1: 'ACU_CHASSIS_BRAKE_LAMP_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_brake_lamp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvBrakeCtrl::set_p_acu_chassis_brake_lamp_ctrl(int acu_chassis_brake_lamp_ctrl) {
  int x = acu_chassis_brake_lamp_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 1, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 4, 'description': 'AEB使能（预留，自动驾驶实现）', 'enum': {0: 'ACU_CHASSIS_AEB_CTRL_DISABLE', 1: 'ACU_CHASSIS_AEB_CTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_aeb_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvBrakeCtrl::set_p_acu_chassis_aeb_ctrl(int acu_chassis_aeb_ctrl) {
  int x = acu_chassis_aeb_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '车辆刹车控制', 'is_signed_var': False, 'len': 10, 'name': 'acu_chassis_brake_pdl_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
void AvBrakeCtrl::set_p_acu_chassis_brake_pdl_target(double acu_chassis_brake_pdl_target) {
  // acu_chassis_brake_pdl_target = ProtocolData::BoundedValue(0.0, 100.0, acu_chassis_brake_pdl_target);
  int x = acu_chassis_brake_pdl_target / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[1] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 2);
  data[2] += to_set1.return_byte_t();
}

// config detail: {'bit': 24, 'description': '驻车控制（触发型控制）', 'enum': {0: 'ACU_CHASSIS_EPB_CTRL_DEFAULT', 1: 'ACU_CHASSIS_EPB_CTRL_BRAKE', 2: 'ACU_CHASSIS_EPB_CTRL_RELEASE'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_chassis_epb_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvBrakeCtrl::set_p_acu_chassis_epb_ctrl(int acu_chassis_epb_ctrl) {
  int x = acu_chassis_epb_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[3] += to_set.return_byte_t();
  
}

// config detail: {'bit': 48, 'description': '循环计数0~15', 'is_signed_var': False, 'len': 4, 'name': 'acu_brake_life_sig', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvBrakeCtrl::set_p_acu_brake_life_sig(int acu_brake_life_sig) {
  // acu_brake_life_sig = ProtocolData::BoundedValue(0, 15, acu_brake_life_sig);
  int x = acu_brake_life_sig;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 4);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'acu_check_sum131', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvBrakeCtrl::set_p_acu_check_sum131(int acu_check_sum131) {
  // acu_check_sum131 = ProtocolData::BoundedValue(0, 255, acu_check_sum131);
  int x = acu_check_sum131;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


