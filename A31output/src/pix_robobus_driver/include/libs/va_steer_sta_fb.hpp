#pragma once

#include <libs/Byte.hpp>

class VaSteerStaFb {
public:
  static const uint32_t ID = 0x532;
  VaSteerStaFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_chassis_steer_en_sta_;
  int vcu_chassis_steer_slopover_;
  int vcu_chassis_steer_work_mode_;
  int vcu_chassis_steer_mode_fb_;
  int vcu_chassis_steer_communication_lost_;
  int vcu_chassis_steer_angle_fb_;
  int vcu_chassis_steer_angle_rear_fb_;
  double vcu_chassis_steer_angle_speed_fb_;
  int vcu_steer_life_;
  int vcu_steer_check_sta_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '转向使能状态', 'enum': {0: 'VCU_CHASSIS_STEER_EN_STA_DISABLE', 1: 'VCU_CHASSIS_STEER_EN_STA_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_steer_en_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassissteerensta();

  // config detail: {'bit': 1, 'description': '转向控制越界提醒', 'enum': {0: 'VCU_CHASSIS_STEER_SLOPOVER_NORMAL', 1: 'VCU_CHASSIS_STEER_SLOPOVER_OVERSLOP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_steer_slopover', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassissteerslopover();

  // config detail: {'bit': 2, 'description': '转向线控模式反馈', 'enum': {0: 'VCU_CHASSIS_STEER_WORK_MODE_MACHINE', 1: 'VCU_CHASSIS_STEER_WORK_MODE_WIRE', 2: 'VCU_CHASSIS_STEER_WORK_MODE_POWER'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_steer_work_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassissteerworkmode();

  // config detail: {'bit': 4, 'description': '转向模式反馈', 'enum': {0: 'VCU_CHASSIS_STEER_MODE_FB_FRONTACKERMAN', 1: 'VCU_CHASSIS_STEER_MODE_FB_SAMEFRONTANDBACK', 2: 'VCU_CHASSIS_STEER_MODE_FB_FRONTDIFFERENTBACK', 3: 'VCU_CHASSIS_STEER_MODE_FB_BACKACKRMAN', 4: 'VCU_CHASSIS_STEER_MODE_FB_FRONTBACK'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu_chassis_steer_mode_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassissteermodefb();

  // config detail: {'bit': 7, 'description': '转向控制报文中断提醒', 'enum': {0: 'VCU_CHASSIS_STEER_COMMUNICATION_LOST_NORMAL', 1: 'VCU_CHASSIS_STEER_COMMUNICATION_LOST_COMMUNICATIONISLOST'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_steer_communication_lost', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassissteercommunicationlost();

  // config detail: {'bit': 8, 'description': '前转向方向盘转角反馈', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_steer_angle_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  int vcuchassissteeranglefb();

  // config detail: {'bit': 24, 'description': '后转向方向盘转角反馈', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_steer_angle_rear_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  int vcuchassissteeranglerearfb();

  // config detail: {'bit': 40, 'description': '设置的转向转角速度反馈', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_steer_angle_speed_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 2.0, 'type': 'double'}
  double vcuchassissteeranglespeedfb();

  // config detail: {'bit': 48, 'description': 'VCU循环计数', 'is_signed_var': False, 'len': 4, 'name': 'vcu_steer_life', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vcusteerlife();

  // config detail: {'bit': 52, 'description': '转向控制信号的Checksum或者 life sig校验情况', 'enum': {0: 'VCU_STEER_CHECK_STA_CHECKOKORDISABLED_校验正常或校验功能关闭', 1: 'VCU_STEER_CHECK_STA_CHECKERROR_校验错误'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_steer_check_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcusteerchecksta();
};



