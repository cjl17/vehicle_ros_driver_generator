#include <libs/av_self_driving_work_st.hpp>

int32_t AvSelfDrivingWorkSt::ID = 0x230;

// public
AvSelfDrivingWorkSt::AvSelfDrivingWorkSt() { Reset(); }

void AvSelfDrivingWorkSt::UpdateData(int acu_adcu1_sys_temp, int acu_adcu2_sys_temp, int acu_self_driving_run_st, int acu_remote_control_mode, int acu_calibration_mode) {
  set_p_acu_adcu1_sys_temp(acu_adcu1_sys_temp);
  set_p_acu_adcu2_sys_temp(acu_adcu2_sys_temp);
  set_p_acu_self_driving_run_st(acu_self_driving_run_st);
  set_p_acu_remote_control_mode(acu_remote_control_mode);
  set_p_acu_calibration_mode(acu_calibration_mode);
}

void AvSelfDrivingWorkSt::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvSelfDrivingWorkSt::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '域控1温度', 'is_signed_var': False, 'len': 8, 'name': 'acu_adcu1_sys_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
void AvSelfDrivingWorkSt::set_p_acu_adcu1_sys_temp(int acu_adcu1_sys_temp) {
  // acu_adcu1_sys_temp = ProtocolData::BoundedValue(-40, 215, acu_adcu1_sys_temp);
  int x = (acu_adcu1_sys_temp - -40.000000);
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '域控2温度', 'is_signed_var': False, 'len': 8, 'name': 'acu_adcu2_sys_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
void AvSelfDrivingWorkSt::set_p_acu_adcu2_sys_temp(int acu_adcu2_sys_temp) {
  // acu_adcu2_sys_temp = ProtocolData::BoundedValue(-40, 215, acu_adcu2_sys_temp);
  int x = (acu_adcu2_sys_temp - -40.000000);
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'description': '自动驾驶系统启动状态(自动驾驶系统已启动，感知规划等有效)', 'enum': {0: 'ACU_SELF_DRIVING_RUN_ST_OFF', 1: 'ACU_SELF_DRIVING_RUN_ST_ON_自动驾驶系统启动之后就发1'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_self_driving_run_st', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvSelfDrivingWorkSt::set_p_acu_self_driving_run_st(int acu_self_driving_run_st) {
  int x = acu_self_driving_run_st;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 17, 'description': '远程驾驶控制模式(是否处于远程驾驶状态)', 'enum': {0: 'ACU_REMOTE_CONTROL_MODE_OFF', 1: 'ACU_REMOTE_CONTROL_MODE_ON_远驾介入就发1'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_remote_control_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvSelfDrivingWorkSt::set_p_acu_remote_control_mode(int acu_remote_control_mode) {
  int x = acu_remote_control_mode;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 1, 1);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 18, 'description': '自动驾驶标定模式设置(只有运行标定模式才需要发这个信号！！)', 'enum': {0: 'ACU_CALIBRATION_MODE_OFF_不开启标定模式', 1: 'ACU_CALIBRATION_MODE_OFF_无效', 2: 'ACU_CALIBRATION_MODE_OFF_无效', 3: 'ACU_CALIBRATION_MODE_ON_开启标定模式'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_calibration_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvSelfDrivingWorkSt::set_p_acu_calibration_mode(int acu_calibration_mode) {
  int x = acu_calibration_mode;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 2);
  data[2] += to_set.return_byte_t();
  
}


