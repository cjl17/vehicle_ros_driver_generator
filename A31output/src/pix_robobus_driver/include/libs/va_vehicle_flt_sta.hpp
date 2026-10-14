#pragma once

#include <libs/Byte.hpp>

class VaVehicleFltSta {
public:
  static const uint32_t ID = 0x537;
  VaVehicleFltSta();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_sys_motor_over_temp_sta_;
  int vcu_sys_bms_over_temp_sta_;
  int vcu_sys_brake_over_temp_sta_;
  int vcu_sys_steer_over_temp_sta_;
  int vcu_sys_under_volt_;
  int vcu_sys_flt_;
  int vcu_sys_brake_flt_;
  int vcu_sys_parking_flt_;
  int vcu_sys_steer_front_flt_;
  int vcu_sys_steer_back_flt_;
  int vcu_sys_motor_lf_flt_;
  int vcu_sys_motor_rf_flt_;
  int vcu_sys_motor_lr_flt_;
  int vcu_sys_motor_rr_flt_;
  int vcu_sys_bms_flt_;
  int vcu_sys_dc_flt_;
  int vcu_sys_door_flt_;
  int vcu_sys_dpm_flt_;
  int vcu_sys_bcm_flt_;
  int vcu_vehicle_flt_level_;
  int vcu_sys_flt_reserve1_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '电机系统过温', 'enum': {0: 'VCU_SYS_MOTOR_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_MOTOR_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_motor_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysmotorovertempsta();

  // config detail: {'bit': 1, 'description': '电池系统过温', 'enum': {0: 'VCU_SYS_BMS_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_BMS_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_bms_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysbmsovertempsta();

  // config detail: {'bit': 2, 'description': '制动系统过温', 'enum': {0: 'VCU_SYS_BRAKE_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_BRAKE_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_brake_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysbrakeovertempsta();

  // config detail: {'bit': 3, 'description': '转向系统过温', 'enum': {0: 'VCU_SYS_STEER_OVER_TEMP_STA_NORMAL', 1: 'VCU_SYS_STEER_OVER_TEMP_STA_OVERTEMP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_steer_over_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusyssteerovertempsta();

  // config detail: {'bit': 4, 'description': '蓄电池电压过低', 'enum': {0: 'VCU_SYS_UNDER_VOLT_NORMAL', 1: 'VCU_SYS_UNDER_VOLT_UNDERVOLT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_sys_under_volt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysundervolt();

  // config detail: {'bit': 8, 'description': '系统故障', 'enum': {0: 'VCU_SYS_FLT_NORMAL', 1: 'VCU_SYS_FLT_FAULTLEVEL1', 2: 'VCU_SYS_FLT_FAULTLEVEL2', 3: 'VCU_SYS_FLT_FAULTLEVEL3', 4: 'VCU_SYS_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysflt();

  // config detail: {'bit': 12, 'description': '制动系统故障', 'enum': {0: 'VCU_SYS_BRAKE_FLT_NORMAL', 1: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL1', 2: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL2', 3: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL3', 4: 'VCU_SYS_BRAKE_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_brake_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysbrakeflt();

  // config detail: {'bit': 16, 'description': '驻车系统故障', 'enum': {0: 'VCU_SYS_PARKING_FLT_NORMAL', 1: 'VCU_SYS_PARKING_FLT_FAULTLEVEL1', 2: 'VCU_SYS_PARKING_FLT_FAULTLEVEL2', 3: 'VCU_SYS_PARKING_FLT_FAULTLEVEL3', 4: 'VCU_SYS_PARKING_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_parking_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysparkingflt();

  // config detail: {'bit': 20, 'description': '前转向系统故障', 'enum': {0: 'VCU_SYS_STEER_FRONT_FLT_NORMAL', 1: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL1', 2: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL2', 3: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL3', 4: 'VCU_SYS_STEER_FRONT_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_steer_front_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusyssteerfrontflt();

  // config detail: {'bit': 24, 'description': '后转向系统故障', 'enum': {0: 'VCU_SYS_STEER_BACK_FLT_NORMAL', 1: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL1', 2: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL2', 3: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL3', 4: 'VCU_SYS_STEER_BACK_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_steer_back_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusyssteerbackflt();

  // config detail: {'bit': 28, 'description': '左前电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_LF_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_LF_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_lf_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysmotorlfflt();

  // config detail: {'bit': 32, 'description': '右前电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_RF_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_RF_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_rf_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysmotorrfflt();

  // config detail: {'bit': 36, 'description': '左后电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_LR_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_LR_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_lr_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysmotorlrflt();

  // config detail: {'bit': 40, 'description': '右后电机系统故障', 'enum': {0: 'VCU_SYS_MOTOR_RR_FLT_NORMAL', 1: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL1', 2: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL2', 3: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL3', 4: 'VCU_SYS_MOTOR_RR_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_motor_rr_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysmotorrrflt();

  // config detail: {'bit': 44, 'description': 'BMS系统故障', 'enum': {0: 'VCU_SYS_BMS_FLT_NORMAL', 1: 'VCU_SYS_BMS_FLT_FAULTLEVEL1', 2: 'VCU_SYS_BMS_FLT_FAULTLEVEL2', 3: 'VCU_SYS_BMS_FLT_FAULTLEVEL3', 4: 'VCU_SYS_BMS_FLT_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_bms_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysbmsflt();

  // config detail: {'bit': 48, 'description': 'DC系统故障', 'enum': {0: 'VCU_SYS_DC_FLT_NORMAL', 1: 'VCU_SYS_DC_FLT_FAULTLEVEL1', 2: 'VCU_SYS_DC_FLT_FAULTLEVEL2', 3: 'VCU_SYS_DC_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_dc_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysdcflt();

  // config detail: {'bit': 50, 'description': '门系统故障', 'enum': {0: 'VCU_SYS_DOOR_FLT_NORMAL', 1: 'VCU_SYS_DOOR_FLT_FAULTLEVEL1', 2: 'VCU_SYS_DOOR_FLT_FAULTLEVEL2', 3: 'VCU_SYS_DOOR_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_door_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysdoorflt();

  // config detail: {'bit': 52, 'description': '数字电源模块故障', 'enum': {0: 'VCU_SYS_DPM_FLT_NORMAL', 1: 'VCU_SYS_DPM_FLT_FAULTLEVEL1', 2: 'VCU_SYS_DPM_FLT_FAULTLEVEL2', 3: 'VCU_SYS_DPM_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_dpm_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysdpmflt();

  // config detail: {'bit': 54, 'description': '车身模块故障', 'enum': {0: 'VCU_SYS_BCM_FLT_NORMAL', 1: 'VCU_SYS_BCM_FLT_FAULTLEVEL1', 2: 'VCU_SYS_BCM_FLT_FAULTLEVEL2', 3: 'VCU_SYS_BCM_FLT_FAULTLEVEL3'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_bcm_flt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysbcmflt();

  // config detail: {'bit': 56, 'description': '整车故障等级', 'enum': {0: 'VCU_VEHICLE_FLT_LEVEL_NORMAL', 1: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL1', 2: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL2', 3: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL3', 4: 'VCU_VEHICLE_FLT_LEVEL_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_vehicle_flt_level', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclefltlevel();

  // config detail: {'bit': 60, 'description': '预留1', 'enum': {0: 'VCU_SYS_FLT_RESERVE1_NORMAL', 1: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL1', 2: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL2', 3: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL3', 4: 'VCU_SYS_FLT_RESERVE1_FAULTLEVEL4'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_sys_flt_reserve1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusysfltreserve1();
};



