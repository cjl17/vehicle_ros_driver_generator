#include <libs/va_vehicle_flt_sta.hpp>


VaVehicleFltSta::VaVehicleFltSta() {}

void VaVehicleFltSta::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaVehicleFltSta::Parse() {
  vcu_sys_motor_over_temp_sta_ = vcusysmotorovertempsta();
  vcu_sys_bms_over_temp_sta_ = vcusysbmsovertempsta();
  vcu_sys_brake_over_temp_sta_ = vcusysbrakeovertempsta();
  vcu_sys_steer_over_temp_sta_ = vcusyssteerovertempsta();
  vcu_sys_under_volt_ = vcusysundervolt();
  vcu_sys_flt_ = vcusysflt();
  vcu_sys_brake_flt_ = vcusysbrakeflt();
  vcu_sys_parking_flt_ = vcusysparkingflt();
  vcu_sys_steer_front_flt_ = vcusyssteerfrontflt();
  vcu_sys_steer_back_flt_ = vcusyssteerbackflt();
  vcu_sys_motor_lf_flt_ = vcusysmotorlfflt();
  vcu_sys_motor_rf_flt_ = vcusysmotorrfflt();
  vcu_sys_motor_lr_flt_ = vcusysmotorlrflt();
  vcu_sys_motor_rr_flt_ = vcusysmotorrrflt();
  vcu_sys_bms_flt_ = vcusysbmsflt();
  vcu_sys_dc_flt_ = vcusysdcflt();
  vcu_sys_door_flt_ = vcusysdoorflt();
  vcu_sys_dpm_flt_ = vcusysdpmflt();
  vcu_sys_bcm_flt_ = vcusysbcmflt();
  vcu_vehicle_flt_level_ = vcuvehiclefltlevel();
  vcu_sys_flt_reserve1_ = vcusysfltreserve1();
}


// config detail: {'bit': 0, 'description': '电机系统过温', 'enum': {0: 'VCU_SYS_MOTOR_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_MOTOR_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_motor_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysmotorovertempsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': '电池系统过温', 'enum': {0: 'VCU_SYS_BMS_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_BMS_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_bms_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysbmsovertempsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '制动系统过温', 'enum': {0: 'VCU_SYS_BRAKE_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_BRAKE_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_brake_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysbrakeovertempsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': '转向系统过温', 'enum': {0: 'VCU_SYS_STEER_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_STEER_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_steer_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusyssteerovertempsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '蓄电池电压过低', 'enum': {0: 'VCU_SYS_UNDER_VOLT_NORMAL', 1: 'VCU_SYS_UNDER_VOLT_UNDERVOLT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_under_volt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysundervolt() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '系统故障', 'enum': {0: 'VCU_SYS_FLT_NORMAL', 1: 'VCU_SYS_FLT_FAULTLEVEL1', 2: 'VCU_SYS_FLT_FAULTLEVEL2', 3: 'VCU_SYS_FLT_FAULTLEVEL3', 4: 'VCU_SYS_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysflt() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': '制动系统故障', 'enum': {0: 'VCU_SYS_BRAKE_FLT_NORMAL', 1: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL1', 2: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL2', 3: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL3', 4: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_brake_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysbrakeflt() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '驻车系统故障', 'enum': {0: 'VCU_SYS_PARKING_FLT_NORMAL', 1: 'VCU_SYS_PARKING_FLT_FAULTLEVEL1', 2: 'VCU_SYS_PARKING_FLT_FAULTLEVEL2', 3: 'VCU_SYS_PARKING_FLT_FAULTLEVEL3', 4: 'VCU_SYS_PARKING_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_parking_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysparkingflt() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': '前转向系统故障', 'enum': {0: 'VCU_SYS_STEER_FRONT_FLT_NORMAL', 1: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL1', 2: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL2', 3: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL3', 4: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_steer_front_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusyssteerfrontflt() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '后转向系统故障', 'enum': {0: 'VCU_SYS_STEER_BACK_FLT_NORMAL', 1: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL1', 2: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL2', 3: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL3', 4: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_steer_back_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusyssteerbackflt() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '左前电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_LF_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_lf_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysmotorlfflt() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '右前电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_RF_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_rf_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysmotorrfflt() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': '左后电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_LR_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_lr_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysmotorlrflt() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(4, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '右后电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_RR_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_rr_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysmotorrrflt() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': 'BMS系统故障', 'enum': {0: 'VCU_SYS_BMS_FLT_NORMAL', 1: 'VCU_SYS_BMS_FLT_FAULTLEVEL1', 2: 'VCU_SYS_BMS_FLT_FAULTLEVEL2', 3: 'VCU_SYS_BMS_FLT_FAULTLEVEL3', 4: 'VCU_SYS_BMS_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_bms_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysbmsflt() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(4, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': 'DC系统故障', 'enum': {0: 'VCU_SYS_DC_FLT_NORMAL', 1: 'VCU_SYS_DC_FLT_FAULTLEVEL1', 2: 'VCU_SYS_DC_FLT_FAULTLEVEL2', 3: 'VCU_SYS_DC_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_dc_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysdcflt() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 50, 'description': '门系统故障', 'enum': {0: 'VCU_SYS_DOOR_FLT_NORMAL', 1: 'VCU_SYS_DOOR_FLT_FAULTLEVEL1', 2: 'VCU_SYS_DOOR_FLT_FAULTLEVEL2', 3: 'VCU_SYS_DOOR_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_door_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysdoorflt() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(2, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 52, 'description': '数字电源模块故障', 'enum': {0: 'VCU_SYS_DPM_FLT_NORMAL', 1: 'VCU_SYS_DPM_FLT_FAULTLEVEL1', 2: 'VCU_SYS_DPM_FLT_FAULTLEVEL2', 3: 'VCU_SYS_DPM_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_dpm_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysdpmflt() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 54, 'description': '车身模块故障', 'enum': {0: 'VCU_SYS_BCM_FLT_NORMAL', 1: 'VCU_SYS_BCM_FLT_FAULTLEVEL1', 2: 'VCU_SYS_BCM_FLT_FAULTLEVEL2', 3: 'VCU_SYS_BCM_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_bcm_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysbcmflt() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(6, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '整车故障等级', 'enum': {0: 'VCU_VEHICLE_FLT_LEVEL_NORMAL', 1: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL1', 2: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL2', 3: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL3', 4: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_vehicle_flt_level', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcuvehiclefltlevel() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': '预留1', 'enum': {0: 'VCU_SYS_FLT_RESERVE1_NORMAL', 1: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL1', 2: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL2', 3: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL3', 4: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_flt_reserve1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleFltSta::vcusysfltreserve1() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(4, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

