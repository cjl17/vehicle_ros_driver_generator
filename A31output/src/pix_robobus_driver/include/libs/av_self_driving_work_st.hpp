#pragma once
#include <libs/Byte.hpp>

class AvSelfDrivingWorkSt {
public:
	static  int32_t ID;

	AvSelfDrivingWorkSt();
	void UpdateData(int acu_adcu1_sys_temp, int acu_adcu2_sys_temp, int acu_self_driving_run_st, int acu_remote_control_mode, int acu_calibration_mode);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '域控1温度', 'is_signed_var': False, 'len': 8, 'name': 'acu_adcu1_sys_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_adcu1_sys_temp(int acu_adcu1_sys_temp);

  // config detail: {'bit': 8, 'description': '域控2温度', 'is_signed_var': False, 'len': 8, 'name': 'acu_adcu2_sys_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_adcu2_sys_temp(int acu_adcu2_sys_temp);

  // config detail: {'bit': 16, 'description': '自动驾驶系统启动状态(自动驾驶系统已启动，感知规划等有效)', 'enum': {0: 'ACU_SELF_DRIVING_RUN_ST_OFF', 1: 'ACU_SELF_DRIVING_RUN_ST_ON_自动驾驶系统启动之后就发1'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_self_driving_run_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_self_driving_run_st(int acu_self_driving_run_st);

  // config detail: {'bit': 17, 'description': '远程驾驶控制模式(是否处于远程驾驶状态)', 'enum': {0: 'ACU_REMOTE_CONTROL_MODE_OFF', 1: 'ACU_REMOTE_CONTROL_MODE_ON_远驾介入就发1'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_remote_control_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_remote_control_mode(int acu_remote_control_mode);

  // config detail: {'bit': 18, 'description': '自动驾驶标定模式设置(只有运行标定模式才需要发这个信号！！)', 'enum': {0: 'ACU_CALIBRATION_MODE_OFF_不开启标定模式', 1: 'ACU_CALIBRATION_MODE_OFF_无效', 2: 'ACU_CALIBRATION_MODE_OFF_无效', 3: 'ACU_CALIBRATION_MODE_ON_开启标定模式'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_calibration_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_calibration_mode(int acu_calibration_mode);

private:
	uint8_t data[8];
};



