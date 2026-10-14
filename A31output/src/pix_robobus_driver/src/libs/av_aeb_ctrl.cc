#include <libs/av_aeb_ctrl.hpp>

int32_t AvAebCtrl::ID = 0x121;

// public
AvAebCtrl::AvAebCtrl() { Reset(); }

void AvAebCtrl::UpdateData(int acu_aeb_work_sta, int acu_aeb_active_request, int acu_fcw_active_request, int acu_aeb_brake_en, int acu_aeb_brake_pedal_target, int acu_aeb_brake_life_sig, int acu_check_sum121) {
  set_p_acu_aeb_work_sta(acu_aeb_work_sta);
  set_p_acu_aeb_active_request(acu_aeb_active_request);
  set_p_acu_fcw_active_request(acu_fcw_active_request);
  set_p_acu_aeb_brake_en(acu_aeb_brake_en);
  set_p_acu_aeb_brake_pedal_target(acu_aeb_brake_pedal_target);
  set_p_acu_aeb_brake_life_sig(acu_aeb_brake_life_sig);
  set_p_acu_check_sum121(acu_check_sum121);
}

void AvAebCtrl::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvAebCtrl::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': 'AEB功能状态', 'enum': {0: 'ACU_AEB_WORK_STA_OFF_关闭', 1: 'ACU_AEB_WORK_STA_ON_开启', 2: 'ACU_AEB_WORK_STA_FAULT_系统错误'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_aeb_work_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvAebCtrl::set_p_acu_aeb_work_sta(int acu_aeb_work_sta) {
  int x = acu_aeb_work_sta;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 2, 'description': 'AEB制动请求状态', 'enum': {0: 'ACU_AEB_ACTIVE_REQUEST_NOREQUEST', 1: 'ACU_AEB_ACTIVE_REQUEST_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_active_request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvAebCtrl::set_p_acu_aeb_active_request(int acu_aeb_active_request) {
  int x = acu_aeb_active_request;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 3, 'description': 'FCW前向碰撞预警', 'enum': {0: 'ACU_FCW_ACTIVE_REQUEST_NOREQUEST', 1: 'ACU_FCW_ACTIVE_REQUEST_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_fcw_active_request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvAebCtrl::set_p_acu_fcw_active_request(int acu_fcw_active_request) {
  int x = acu_fcw_active_request;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 3, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 4, 'description': 'AEB制动控制使能', 'enum': {0: 'ACU_AEB_BRAKE_EN_DISABLE', 1: 'ACU_AEB_BRAKE_EN_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_brake_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvAebCtrl::set_p_acu_aeb_brake_en(int acu_aeb_brake_en) {
  int x = acu_aeb_brake_en;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '制动踏板请求', 'is_signed_var': False, 'len': 8, 'name': 'acu_aeb_brake_pedal_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
void AvAebCtrl::set_p_acu_aeb_brake_pedal_target(int acu_aeb_brake_pedal_target) {
  // acu_aeb_brake_pedal_target = ProtocolData::BoundedValue(0, 100, acu_aeb_brake_pedal_target);
  int x = acu_aeb_brake_pedal_target;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 48, 'description': '循环计数0~15', 'is_signed_var': False, 'len': 4, 'name': 'acu_aeb_brake_life_sig', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvAebCtrl::set_p_acu_aeb_brake_life_sig(int acu_aeb_brake_life_sig) {
  // acu_aeb_brake_life_sig = ProtocolData::BoundedValue(0, 15, acu_aeb_brake_life_sig);
  int x = acu_aeb_brake_life_sig;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 4);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'acu_check_sum121', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvAebCtrl::set_p_acu_check_sum121(int acu_check_sum121) {
  // acu_check_sum121 = ProtocolData::BoundedValue(0, 255, acu_check_sum121);
  int x = acu_check_sum121;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


