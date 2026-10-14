#pragma once
#include <libs/Byte.hpp>

class AvManualSpdLimit {
public:
	static  int32_t ID;

	AvManualSpdLimit();
	void UpdateData(int acu_aeb_usable_manual_limit, int acu_aeb_unusable_manual_limit, double acu_aeb_usable_manual_spd_set, double acu_aeb_unusable_manual_spd_set);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': 'AEB可用时人工驾驶的限速开关', 'enum': {0: 'ACU_AEB_USABLE_MANUAL_LIMIT_OFF_关闭_按车辆默认的限速', 1: 'ACU_AEB_USABLE_MANUAL_LIMIT_ON_开启'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_usable_manual_limit', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_aeb_usable_manual_limit(int acu_aeb_usable_manual_limit);

  // config detail: {'bit': 1, 'description': 'AEB不可用时人工驾驶的限速开关', 'enum': {0: 'ACU_AEB_UNUSABLE_MANUAL_LIMIT_OFF_关闭_按车辆默认的限速', 1: 'ACU_AEB_UNUSABLE_MANUAL_LIMIT_ON_开启'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_unusable_manual_limit', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_aeb_unusable_manual_limit(int acu_aeb_unusable_manual_limit);

  // config detail: {'bit': 8, 'description': 'AEB可用时人工驾驶的限速值', 'is_signed_var': False, 'len': 8, 'name': 'acu_aeb_usable_manual_spd_set', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|20]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_aeb_usable_manual_spd_set(double acu_aeb_usable_manual_spd_set);

  // config detail: {'bit': 16, 'description': 'AEB不可用时人工驾驶的限速值', 'is_signed_var': False, 'len': 8, 'name': 'acu_aeb_unusable_manual_spd_set', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|10]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_aeb_unusable_manual_spd_set(double acu_aeb_unusable_manual_spd_set);

private:
	uint8_t data[8];
};



