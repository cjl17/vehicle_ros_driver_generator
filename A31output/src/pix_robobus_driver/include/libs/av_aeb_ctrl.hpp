#pragma once
#include <libs/Byte.hpp>

class AvAebCtrl {
public:
	static  int32_t ID;

	AvAebCtrl();
	void UpdateData(int acu_aeb_work_sta, int acu_aeb_active_request, int acu_fcw_active_request, int acu_aeb_brake_en, int acu_aeb_brake_pedal_target, int acu_aeb_brake_life_sig, int acu_check_sum121);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': 'AEB功能状态', 'enum': {0: 'ACU_AEB_WORK_STA_OFF_关闭', 1: 'ACU_AEB_WORK_STA_ON_开启', 2: 'ACU_AEB_WORK_STA_FAULT_系统错误'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_aeb_work_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_aeb_work_sta(int acu_aeb_work_sta);

  // config detail: {'bit': 2, 'description': 'AEB制动请求状态', 'enum': {0: 'ACU_AEB_ACTIVE_REQUEST_NOREQUEST', 1: 'ACU_AEB_ACTIVE_REQUEST_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_active_request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_aeb_active_request(int acu_aeb_active_request);

  // config detail: {'bit': 3, 'description': 'FCW前向碰撞预警', 'enum': {0: 'ACU_FCW_ACTIVE_REQUEST_NOREQUEST', 1: 'ACU_FCW_ACTIVE_REQUEST_REQUEST'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_fcw_active_request', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_fcw_active_request(int acu_fcw_active_request);

  // config detail: {'bit': 4, 'description': 'AEB制动控制使能', 'enum': {0: 'ACU_AEB_BRAKE_EN_DISABLE', 1: 'ACU_AEB_BRAKE_EN_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_aeb_brake_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_aeb_brake_en(int acu_aeb_brake_en);

  // config detail: {'bit': 8, 'description': '制动踏板请求', 'is_signed_var': False, 'len': 8, 'name': 'acu_aeb_brake_pedal_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_aeb_brake_pedal_target(int acu_aeb_brake_pedal_target);

  // config detail: {'bit': 48, 'description': '循环计数0~15', 'is_signed_var': False, 'len': 4, 'name': 'acu_aeb_brake_life_sig', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_aeb_brake_life_sig(int acu_aeb_brake_life_sig);

  // config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'acu_check_sum121', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_check_sum121(int acu_check_sum121);

private:
	uint8_t data[8];
};



