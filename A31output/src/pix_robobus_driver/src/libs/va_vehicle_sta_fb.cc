#include <libs/va_vehicle_sta_fb.hpp>


VaVehicleStaFb::VaVehicleStaFb() {}

void VaVehicleStaFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaVehicleStaFb::Parse() {
  vcu_vehicle_pos_lamp_fb_ = vcuvehicleposlampfb();
  vcu_vehicle_head_lamp_fb_ = vcuvehicleheadlampfb();
  vcu_vehicle_left_lamp_fb_ = vcuvehicleleftlampfb();
  vcu_vehicle_right_lamp_fb_ = vcuvehiclerightlampfb();
  vcu_vehicle_high_beam_fb_ = vcuvehiclehighbeamfb();
  vcu_vehicle_fog_lamp_fb_ = vcuvehiclefoglampfb();
  vcu_vehicle_hazard_war_lamp_fb_ = vcuvehiclehazardwarlampfb();
  vcu_vehicle_body_lamp_fb_ = vcuvehiclebodylampfb();
  vcu_vehicle_read_lamp_fb_ = vcuvehiclereadlampfb();
  vcu_vehicle_horn_st_fb_ = vcuvehiclehornstfb();
  acu_vehicle_window_fb_ = acuvehiclewindowfb();
  acu_vehicle_door_req_sig_fb_ = acuvehicledoorreqsigfb();
  vcu_vehicle_door_sta_fb_ = vcuvehicledoorstafb();
  vcu_vehicle_wipers_sta_fb_ = vcuvehiclewipersstafb();
  vcu_vehicle_safety_belt1_ = vcuvehiclesafetybelt1();
  vcu_vehicle_safety_belt2_ = vcuvehiclesafetybelt2();
  vcu_vehicle_safety_belt3_ = vcuvehiclesafetybelt3();
  vcu_vehicle_safety_belt4_ = vcuvehiclesafetybelt4();
  vcu_vehicle_safety_belt5_ = vcuvehiclesafetybelt5();
  vcu_vehicle_safety_belt6_ = vcuvehiclesafetybelt6();
  vcu_vehicle_reserve_warning_ = vcuvehiclereservewarning();
  vcu_vehicle_display_speed_ = vcuvehicledisplayspeed();
}


// config detail: {'bit': 0, 'description': '位置灯状态反馈', 'enum': {0: 'VCU_VEHICLE_POS_LAMP_FB_OFF', 1: 'VCU_VEHICLE_POS_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_pos_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehicleposlampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': '近光灯状态反馈', 'enum': {0: 'VCU_VEHICLE_HEAD_LAMP_FB_OFF', 1: 'VCU_VEHICLE_HEAD_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_head_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehicleheadlampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '左转向灯状态反馈', 'enum': {0: 'VCU_VEHICLE_LEFT_LAMP_FB_OFF', 1: 'VCU_VEHICLE_LEFT_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_left_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehicleleftlampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': '右转向灯状态反馈', 'enum': {0: 'VCU_VEHICLE_RIGHT_LAMP_FB_OFF', 1: 'VCU_VEHICLE_RIGHT_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_right_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclerightlampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '远光灯状态反馈', 'enum': {0: 'VCU_VEHICLE_HIGH_BEAM_FB_OFF', 1: 'VCU_VEHICLE_HIGH_BEAM_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_high_beam_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclehighbeamfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 5, 'description': '雾灯状态反馈', 'enum': {0: 'VCU_VEHICLE_FOG_LAMP_FB_OFF', 1: 'VCU_VEHICLE_FOG_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_fog_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclefoglampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': '危险警示灯开关状态', 'enum': {0: 'VCU_VEHICLE_HAZARD_WAR_LAMP_FB_OFF', 1: 'VCU_VEHICLE_HAZARD_WAR_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_hazard_war_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclehazardwarlampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '车外氛围灯状态反馈', 'enum': {0: 'VCU_VEHICLE_BODY_LAMP_FB_OFF', 1: 'VCU_VEHICLE_BODY_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_body_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclebodylampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '车内灯光状态反馈', 'enum': {0: 'VCU_VEHICLE_READ_LAMP_FB_OFF', 1: 'VCU_VEHICLE_READ_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_read_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclereadlampfb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': '喇叭开启状态反馈', 'enum': {0: 'VCU_VEHICLE_HORN_ST_FB_OFF', 1: 'VCU_VEHICLE_HORN_ST_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_horn_st_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclehornstfb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': '车内车窗状态反馈（预留）', 'enum': {0: 'ACU_VEHICLE_WINDOW_FB_OPENING', 1: 'ACU_VEHICLE_WINDOW_FB_CLOSING', 2: 'ACU_VEHICLE_WINDOW_FB_OPENINPLACE', 3: 'ACU_VEHICLE_WINDOW_FB_CLOSEINPLACE'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_window_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::acuvehiclewindowfb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': '请求车辆开门的信号来源', 'enum': {0: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_NOTREQ_未请求开关门', 1: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_RCUREQDOOR_遥控请求', 2: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_OUTSIDEREQDOOR_车外请求', 3: 'ACU_VEHICLE_DOOR_REQ_SIG_FB_INSIDEREQDOOR_车内请求'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_door_req_sig_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::acuvehicledoorreqsigfb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(6, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '车门状态反馈', 'enum': {0: 'VCU_VEHICLE_DOOR_STA_FB_INVALID', 1: 'VCU_VEHICLE_DOOR_STA_FB_OPENING', 2: 'VCU_VEHICLE_DOOR_STA_FB_CLOSING', 3: 'VCU_VEHICLE_DOOR_STA_FB_OPENINPLACE', 4: 'VCU_VEHICLE_DOOR_STA_FB_CLOSEINPLACE', 5: 'VCU_VEHICLE_DOOR_STA_FB_OPENTIMEOUT', 6: 'VCU_VEHICLE_DOOR_STA_FB_CLOSETIMEOUT'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_vehicle_door_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|6]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehicledoorstafb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': '雨刮状态反馈(预留)', 'enum': {0: 'VCU_VEHICLE_WIPERS_STA_FB_OFF', 1: 'VCU_VEHICLE_WIPERS_STA_FB_LOW', 2: 'VCU_VEHICLE_WIPERS_STA_FB_MID', 3: 'VCU_VEHICLE_WIPERS_STA_FB_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_wipers_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclewipersstafb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '安全带状态1反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT1_NO', 1: 'VCU_VEHICLE_SAFETY_BELT1_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT1_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT1_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclesafetybelt1() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': '安全带状态2反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT2_NO', 1: 'VCU_VEHICLE_SAFETY_BELT2_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT2_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT2_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclesafetybelt2() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(2, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '安全带状态3反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT3_NO', 1: 'VCU_VEHICLE_SAFETY_BELT3_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT3_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT3_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclesafetybelt3() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '安全带状态4反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT4_NO', 1: 'VCU_VEHICLE_SAFETY_BELT4_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT4_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT4_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclesafetybelt4() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(6, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '安全带状态5反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT5_NO', 1: 'VCU_VEHICLE_SAFETY_BELT5_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT5_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT5_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclesafetybelt5() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': '安全带状态6反馈', 'enum': {0: 'VCU_VEHICLE_SAFETY_BELT6_NO', 1: 'VCU_VEHICLE_SAFETY_BELT6_SIT', 2: 'VCU_VEHICLE_SAFETY_BELT6_SAFETYBELT', 3: 'VCU_VEHICLE_SAFETY_BELT6_UNKNOW_传感器故障'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_vehicle_safety_belt6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleStaFb::vcuvehiclesafetybelt6() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': 'VCU反馈的提醒信号(预留)', 'is_signed_var': False, 'len': 16, 'name': 'vcu_vehicle_reserve_warning', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaVehicleStaFb::vcuvehiclereservewarning() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 5));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'description': '自动驾驶仪表显示的车速', 'is_signed_var': False, 'len': 8, 'name': 'vcu_vehicle_display_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|240]', 'physical_unit': 'Km/h', 'precision': 1.0, 'type': 'int'}
int VaVehicleStaFb::vcuvehicledisplayspeed() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

