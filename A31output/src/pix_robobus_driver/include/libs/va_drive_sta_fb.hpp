#pragma once

#include <libs/Byte.hpp>

class VaDriveStaFb {
public:
  static const uint32_t ID = 0x530;
  VaDriveStaFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_chassis_driver_en_sta_;
  int vcu_chassis_diver_slopover_;
  int vcu_chassis_driver_mode_sta_;
  int vcu_chassis_gear_fb_;
  int vcu_chassis4_wd_mode_fb_;
  double vcu_chassis_speed_fb_;
  double vcu_chassis_throttle_pald_fb_;
  int vcu_chassis_throttle_pedal_req_fb_;
  double vcu_chassis_acceleration_fb_;
  int vcu_drive_life_;
  int vcu_drive_check_sta_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '驱动使能状态', 'enum': {0: 'VCU_CHASSIS_DRIVER_EN_STA_DISABLE', 1: 'VCU_CHASSIS_DRIVER_EN_STA_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_driver_en_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisdriverensta();

  // config detail: {'bit': 1, 'description': '驱动控制越界提醒', 'enum': {0: 'VCU_CHASSIS_DIVER_SLOPOVER_NORMAL', 1: 'VCU_CHASSIS_DIVER_SLOPOVER_OVERSLOP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_diver_slopover', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisdiverslopover();

  // config detail: {'bit': 2, 'description': '驱动模式反馈', 'enum': {0: 'VCU_CHASSIS_DRIVER_MODE_STA_SPEEDCTRLMODE', 1: 'VCU_CHASSIS_DRIVER_MODE_STA_THROTTLECTRLMODE', 2: 'VCU_CHASSIS_DRIVER_MODE_STA_RESERVE', 3: 'VCU_CHASSIS_DRIVER_MODE_STA_RESERVE'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_driver_mode_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisdrivermodesta();

  // config detail: {'bit': 4, 'description': '档位状态', 'enum': {0: 'VCU_CHASSIS_GEAR_FB_NOTUSED', 1: 'VCU_CHASSIS_GEAR_FB_D', 2: 'VCU_CHASSIS_GEAR_FB_N', 3: 'VCU_CHASSIS_GEAR_FB_R'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_gear_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisgearfb();

  // config detail: {'bit': 6, 'description': '四驱两驱状态反馈', 'enum': {0: 'VCU_CHASSIS4_WD_MODE_FB_FOURWD', 1: 'VCU_CHASSIS4_WD_MODE_FB_RWD', 2: 'VCU_CHASSIS4_WD_MODE_FB_FWD'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis4_wd_mode_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassis4wdmodefb();

  // config detail: {'bit': 8, 'description': '车速实际反馈', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_speed_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-50|50]', 'physical_unit': 'm/s', 'precision': 0.01, 'type': 'double'}
  double vcuchassisspeedfb();

  // config detail: {'bit': 24, 'description': '油门请求值反馈', 'is_signed_var': False, 'len': 10, 'name': 'vcu_chassis_throttle_pald_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  double vcuchassisthrottlepaldfb();

  // config detail: {'bit': 34, 'description': '自驾模式下操作员请求了油门踏板(预留)', 'enum': {0: 'VCU_CHASSIS_THROTTLE_PEDAL_REQ_FB_NOTREQTHROTTLEPEDAL', 1: 'VCU_CHASSIS_THROTTLE_PEDAL_REQ_FB_USERREQTHROTTLEPEDAL'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_throttle_pedal_req_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisthrottlepedalreqfb();

  // config detail: {'bit': 40, 'description': '车辆加速度', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_acceleration_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-20|20]', 'physical_unit': 'm/s2', 'precision': 0.01, 'type': 'double'}
  double vcuchassisaccelerationfb();

  // config detail: {'bit': 56, 'description': 'VCU循环计数', 'is_signed_var': False, 'len': 4, 'name': 'vcu_drive_life', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vcudrivelife();

  // config detail: {'bit': 60, 'description': '驱动控制信号的Checksum或者 life sig校验情况', 'enum': {0: 'VCU_DRIVE_CHECK_STA_CHECKOKORDISABLED_校验正常或校验功能关闭', 1: 'VCU_DRIVE_CHECK_STA_CHECKERROR_校验错误'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_drive_check_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcudrivechecksta();
};



