#include <libs/av_manual_spd_limit.hpp>

int32_t AvManualSpdLimit::ID = 0x160;

// public
AvManualSpdLimit::AvManualSpdLimit() { Reset(); }

void AvManualSpdLimit::UpdateData(int acu_aeb_usable_manual_limit, int acu_aeb_unusable_manual_limit, double acu_aeb_usable_manual_spd_set, double acu_aeb_unusable_manual_spd_set) {
  set_p_acu_aeb_usable_manual_limit(acu_aeb_usable_manual_limit);
  set_p_acu_aeb_unusable_manual_limit(acu_aeb_unusable_manual_limit);
  set_p_acu_aeb_usable_manual_spd_set(acu_aeb_usable_manual_spd_set);
  set_p_acu_aeb_unusable_manual_spd_set(acu_aeb_unusable_manual_spd_set);
}

void AvManualSpdLimit::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvManualSpdLimit::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': 'AEB可用时人工驾驶的限速开关', 'enum': {0: 'ACU_AEB_USABLE_MANUAL_LIMIT_OFF_关闭_按车辆默认的限速', 1: 'ACU_AEB_USABLE_MANUAL_LIMIT_ON_开启'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_usable_manual_limit', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvManualSpdLimit::set_p_acu_aeb_usable_manual_limit(int acu_aeb_usable_manual_limit) {
  int x = acu_aeb_usable_manual_limit;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 1, 'description': 'AEB不可用时人工驾驶的限速开关', 'enum': {0: 'ACU_AEB_UNUSABLE_MANUAL_LIMIT_OFF_关闭_按车辆默认的限速', 1: 'ACU_AEB_UNUSABLE_MANUAL_LIMIT_ON_开启'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_unusable_manual_limit', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvManualSpdLimit::set_p_acu_aeb_unusable_manual_limit(int acu_aeb_unusable_manual_limit) {
  int x = acu_aeb_unusable_manual_limit;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 1, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': 'AEB可用时人工驾驶的限速值', 'is_signed_var': False, 'len': 8, 'name': 'acu_aeb_usable_manual_spd_set', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|20]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
void AvManualSpdLimit::set_p_acu_aeb_usable_manual_spd_set(double acu_aeb_usable_manual_spd_set) {
  // acu_aeb_usable_manual_spd_set = ProtocolData::BoundedValue(0.0, 20.0, acu_aeb_usable_manual_spd_set);
  int x = acu_aeb_usable_manual_spd_set / 0.100000;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'description': 'AEB不可用时人工驾驶的限速值', 'is_signed_var': False, 'len': 8, 'name': 'acu_aeb_unusable_manual_spd_set', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
void AvManualSpdLimit::set_p_acu_aeb_unusable_manual_spd_set(double acu_aeb_unusable_manual_spd_set) {
  // acu_aeb_unusable_manual_spd_set = ProtocolData::BoundedValue(0.0, 10.0, acu_aeb_unusable_manual_spd_set);
  int x = acu_aeb_unusable_manual_spd_set / 0.100000;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[2] += to_set.return_byte_t();
  
}


