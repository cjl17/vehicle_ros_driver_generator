#pragma once

#include <libs/Byte.hpp>

class VaBrakeStaFb {
public:
  static const uint32_t ID = 0x531;
  VaBrakeStaFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_chassis_brake_en_sta_;
  int vcu_vehicle_brake_lamp_fb_;
  int vcu_chassis_epb_fb_;
  int vcu_chassis_brake_communication_lost_;
  double vcu_chassis_brake_padl_fb_;
  int vcu_brake_pedal_req_fb_;
  int vcu_aeb_en_sta_fb_;
  int vcu_aeb_trigger_sta_fb_;
  int vcu_chassis_brake_pressure_fb_;
  int vcu_brake_life_;
  int vcu_brake_check_sta_;
  bool vcu_energy_recovery_sta_fb_;
  int vcu_energy_recovery_tor_fb_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '制动使能状态', 'enum': {0: 'VCU_CHASSIS_BRAKE_EN_STA_DISABLE', 1: 'VCU_CHASSIS_BRAKE_EN_STA_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_brake_en_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisbrakeensta();

  // config detail: {'bit': 2, 'description': '制动灯状态反馈', 'enum': {0: 'VCU_VEHICLE_BRAKE_LAMP_FB_OFF', 1: 'VCU_VEHICLE_BRAKE_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_brake_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclebrakelampfb();

  // config detail: {'bit': 4, 'description': '驻车状态', 'enum': {0: 'VCU_CHASSIS_EPB_FB_RELEASE', 1: 'VCU_CHASSIS_EPB_FB_BRAKE', 2: 'VCU_CHASSIS_EPB_FB_RELEASING', 3: 'VCU_CHASSIS_EPB_FB_BRAKING'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_epb_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisepbfb();

  // config detail: {'bit': 7, 'description': '制动控制报文中断提醒', 'enum': {0: 'VCU_CHASSIS_BRAKE_COMMUNICATION_LOST_NORMAL', 1: 'VCU_CHASSIS_BRAKE_COMMUNICATION_LOST_COMMUNICATIONISLOST'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_brake_communication_lost', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuchassisbrakecommunicationlost();

  // config detail: {'bit': 8, 'description': '制动踏板值反馈', 'is_signed_var': False, 'len': 10, 'name': 'vcu_chassis_brake_padl_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  double vcuchassisbrakepadlfb();

  // config detail: {'bit': 18, 'description': '自驾状态下用户请求了制动', 'enum': {0: 'VCU_BRAKE_PEDAL_REQ_FB_NOTREQBRAKEPEDAL', 1: 'VCU_BRAKE_PEDAL_REQ_FB_REQBRAKEPEDAL'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_brake_pedal_req_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcubrakepedalreqfb();

  // config detail: {'bit': 20, 'description': 'AEB开启状态反馈（预留）', 'enum': {0: 'VCU_AEB_EN_STA_FB_OFF', 1: 'VCU_AEB_EN_STA_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_aeb_en_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuaebenstafb();

  // config detail: {'bit': 22, 'description': 'AEB触发状态反馈（预留）', 'enum': {0: 'VCU_AEB_TRIGGER_STA_FB_OFF', 1: 'VCU_AEB_TRIGGER_STA_FB_AEBTRIGGER'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_aeb_trigger_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuaebtriggerstafb();

  // config detail: {'bit': 24, 'description': '制动压力反馈', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_brake_pressure_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'bar', 'precision': 1.0, 'type': 'int'}
  int vcuchassisbrakepressurefb();

  // config detail: {'bit': 48, 'description': 'VCU循环计数', 'is_signed_var': False, 'len': 4, 'name': 'vcu_brake_life', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vcubrakelife();

  // config detail: {'bit': 52, 'description': '制动控制信号的Checksum或者 life sig校验情况', 'enum': {0: 'VCU_BRAKE_CHECK_STA_CHECKOKORDISABLED_校验正常或校验功能关闭', 1: 'VCU_BRAKE_CHECK_STA_CHECKERROR_校验错误'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_brake_check_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcubrakechecksta();

  // config detail: {'bit': 53, 'description': '当前能量回收状态反馈', 'is_signed_var': False, 'len': 1, 'name': 'vcu_energy_recovery_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool vcuenergyrecoverystafb();

  // config detail: {'bit': 54, 'description': '当前能量回收扭矩反馈', 'is_signed_var': False, 'len': 10, 'name': 'vcu_energy_recovery_tor_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'Nm', 'precision': 1.0, 'type': 'int'}
  int vcuenergyrecoverytorfb();
};



