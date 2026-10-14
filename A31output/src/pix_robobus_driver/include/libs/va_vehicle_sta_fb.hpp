#pragma once

#include <libs/Byte.hpp>

class VaVehicleStaFb {
public:
  static const uint32_t ID = 0x536;
  VaVehicleStaFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_vehicle_pos_lamp_fb_;
  int vcu_vehicle_head_lamp_fb_;
  int vcu_vehicle_left_lamp_fb_;
  int vcu_vehicle_right_lamp_fb_;
  int vcu_vehicle_high_beam_fb_;
  int vcu_vehicle_fog_lamp_fb_;
  int vcu_vehicle_hazard_war_lamp_fb_;
  int vcu_vehicle_body_lamp_fb_;
  int vcu_vehicle_read_lamp_fb_;
  int vcu_vehicle_horn_st_fb_;
  int acu_vehicle_window_fb_;
  int acu_vehicle_door_req_sig_fb_;
  int vcu_vehicle_door_sta_fb_;
  int vcu_vehicle_wipers_sta_fb_;
  int vcu_vehicle_safety_belt1_;
  int vcu_vehicle_safety_belt2_;
  int vcu_vehicle_safety_belt3_;
  int vcu_vehicle_safety_belt4_;
  int vcu_vehicle_safety_belt5_;
  int vcu_vehicle_safety_belt6_;
  int vcu_vehicle_reserve_warning_;
  int vcu_vehicle_display_speed_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '位置灯状态反馈', 'enum': {0: 'VCU_VEHICLE_POS_LAMP_FB_OFF', 1: 'VCU_VEHICLE_POS_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_pos_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehicleposlampfb();

  // config detail: {'bit': 1, 'description': '近光灯状态反馈', 'enum': {0: 'VCU_VEHICLE_HEAD_LAMP_FB_OFF', 1: 'VCU_VEHICLE_HEAD_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_head_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehicleheadlampfb();

  // config detail: {'bit': 2, 'description': '左转向灯状态反馈', 'enum': {0: 'VCU_VEHICLE_LEFT_LAMP_FB_OFF', 1: 'VCU_VEHICLE_LEFT_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_left_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehicleleftlampfb();

  // config detail: {'bit': 3, 'description': '右转向灯状态反馈', 'enum': {0: 'VCU_VEHICLE_RIGHT_LAMP_FB_OFF', 1: 'VCU_VEHICLE_RIGHT_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_right_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclerightlampfb();

  // config detail: {'bit': 4, 'description': '远光灯状态反馈', 'enum': {0: 'VCU_VEHICLE_HIGH_BEAM_FB_OFF', 1: 'VCU_VEHICLE_HIGH_BEAM_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_high_beam_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclehighbeamfb();

  // config detail: {'bit': 5, 'description': '雾灯状态反馈', 'enum': {0: 'VCU_VEHICLE_FOG_LAMP_FB_OFF', 1: 'VCU_VEHICLE_FOG_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_fog_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclefoglampfb();

  // config detail: {'bit': 6, 'description': '危险警示灯开关状态', 'enum': {0: 'VCU_VEHICLE_HAZARD_WAR_LAMP_FB_OFF', 1: 'VCU_VEHICLE_HAZARD_WAR_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_hazard_war_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclehazardwarlampfb();

  // config detail: {'bit': 7, 'description': '车外氛围灯状态反馈', 'enum': {0: 'VCU_VEHICLE_BODY_LAMP_FB_OFF', 1: 'VCU_VEHICLE_BODY_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_body_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclebodylampfb();

  // config detail: {'bit': 8, 'description': '车内灯光状态反馈', 'enum': {0: 'VCU_VEHICLE_READ_LAMP_FB_OFF', 1: 'VCU_VEHICLE_READ_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_read_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclereadlampfb();

  // config detail: {'bit': 9, 'description': '喇叭开启状态反馈', 'enum': {0: 'VCU_VEHICLE_HORN_ST_FB_OFF', 1: 'VCU_VEHICLE_HORN_ST_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_horn_st_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclehornstfb();

  // config detail: {'bit': 12, 'description': '车内车窗状态反馈（预留）', 'enum': {0: 'ACU_VEHICLE_WINDOW_FB_OPENING', 1: 'ACU_VEHICLE_WINDOW_FB_CLOSING', 2: 'ACU_VEHICLE_WINDOW_FB_OPENINPLACE', 3: 'ACU_VEHICLE_WINDOW_FB_CLOSEINPLACE'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_window_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int acuvehiclewindowfb();

  // config detail: {'bit': 14, 'description': '请求车辆开门的信号来源', 'enum': {0: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_NOTREQ_未请求开关门', 1: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_RCUREQDOOR_遥控请求', 2: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_OUTSIDEREQDOOR_车外请求', 3: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_INSIDEREQDOOR_车内请求'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_door_req_sig_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int acuvehicledoorreqsigfb();

  // config detail: {'bit': 16, 'description': '车门状态反馈', 'enum': {0: 'VCU_VEHICLE_DOOR_STA_FB_INVALID', 1: 'VCU_VEHICLE_DOOR_STA_FB_OPENING', 2: 'VCU_VEHICLE_DOOR_STA_FB_CLOSING', 3: 'VCU_VEHICLE_DOOR_STA_FB_OPENINPLACE', 4: 'VCU_VEHICLE_DOOR_STA_FB_CLOSEINPLACE', 5: 'VCU_VEHICLE_DOOR_STA_FB_OPENTIMEOUT', 6: 'VCU_VEHICLE_DOOR_STA_FB_CLOSETIMEOUT'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_vehicle_door_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehicledoorstafb();

  // config detail: {'bit': 20, 'description': '雨刮状态反馈(预留)', 'enum': {0: 'VCU_VEHICLE_WIPERS_STA_FB_OFF', 1: 'VCU_VEHICLE_WIPERS_STA_FB_LOW', 2: 'VCU_VEHICLE_WIPERS_STA_FB_MID', 3: 'VCU_VEHICLE_WIPERS_STA_FB_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_wipers_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclewipersstafb();

  // config detail: {'bit': 24, 'description': '安全带状态1反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT1_NO', 1: 'VCU_VEHICLE_SAFETY_BELT1_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT1_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT1_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclesafetybelt1();

  // config detail: {'bit': 26, 'description': '安全带状态2反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT2_NO', 1: 'VCU_VEHICLE_SAFETY_BELT2_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT2_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT2_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclesafetybelt2();

  // config detail: {'bit': 28, 'description': '安全带状态3反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT3_NO', 1: 'VCU_VEHICLE_SAFETY_BELT3_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT3_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT3_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclesafetybelt3();

  // config detail: {'bit': 30, 'description': '安全带状态4反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT4_NO', 1: 'VCU_VEHICLE_SAFETY_BELT4_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT4_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT4_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclesafetybelt4();

  // config detail: {'bit': 32, 'description': '安全带状态5反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT5_NO', 1: 'VCU_VEHICLE_SAFETY_BELT5_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT5_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT5_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclesafetybelt5();

  // config detail: {'bit': 34, 'description': '安全带状态6反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT6_NO', 1: 'VCU_VEHICLE_SAFETY_BELT6_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT6_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT6_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int vcuvehiclesafetybelt6();

  // config detail: {'bit': 40, 'description': 'VCU反馈的提醒信号(预留)', 'is_signed_var': False, 'len': 16, 'name': 'vcu_vehicle_reserve_warning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vcuvehiclereservewarning();

  // config detail: {'bit': 56, 'description': '自动驾驶仪表显示的车速', 'is_signed_var': False, 'len': 8, 'name': 'vcu_vehicle_display_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|240]', 'physical_unit': 'Km/h', 'precision': 1.0, 'type': 'int'}
  int vcuvehicledisplayspeed();
};



