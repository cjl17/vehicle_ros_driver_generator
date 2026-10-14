#include <libs/historical_vehiclefailures1.hpp>


HistoricalVehiclefailures1::HistoricalVehiclefailures1() {}

void HistoricalVehiclefailures1::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void HistoricalVehiclefailures1::Parse() {
  flmc_hardware_fault51_c_ = flmchardwarefault51c();
  flmc_tem_fault51_c_ = flmctemfault51c();
  flm_tem_fault51_c_ = flmtemfault51c();
  rlmc_hardware_fault51_c_ = rlmchardwarefault51c();
  rlmc_tem_fault51_c_ = rlmctemfault51c();
  rlm_tem_fault51_c_ = rlmtemfault51c();
  frmc_hardware_fault51_c_ = frmchardwarefault51c();
  frmc_tem_fault51_c_ = frmctemfault51c();
  frm_tem_fault51_c_ = frmtemfault51c();
  rrmc_hardware_fault51_c_ = rrmchardwarefault51c();
  rrmc_tem_fault51_c_ = rrmctemfault51c();
  rrm_tem_fault51_c_ = rrmtemfault51c();
  flmc_network_fault51_c_ = flmcnetworkfault51c();
  frmc_network_fault51_c_ = frmcnetworkfault51c();
  rlmc_network_fault51_c_ = rlmcnetworkfault51c();
  rrmc_network_fault51_c_ = rrmcnetworkfault51c();
  fr_steer_hardware_fault51_c_ = frsteerhardwarefault51c();
  rr_steer_hardware_fault51_c_ = rrsteerhardwarefault51c();
  fr_steer_network_fault51_c_ = frsteernetworkfault51c();
  rr_steer_network_fault51_c_ = rrsteernetworkfault51c();
  brake_hardware_fault51_c_ = brakehardwarefault51c();
  brake_high_tem_fault51_c_ = brakehightemfault51c();
  brake_luid_level_low51_c_ = brakeluidlevellow51c();
  brake_network_fault51_c_ = brakenetworkfault51c();
  park_hardware_fault51_c_ = parkhardwarefault51c();
  park_network_fault51_c_ = parknetworkfault51c();
  rcu_network_fault51_c_ = rcunetworkfault51c();
  rcu_weak_signal51_c_ = rcuweaksignal51c();
  rcu_elec_low_alarm51_c_ = rcueleclowalarm51c();
  spare151_c_ = spare151c();
  spare251_c_ = spare251c();
  bms_network_fault51_c_ = bmsnetworkfault51c();
  bms_insulation_fault51_c_ = bmsinsulationfault51c();
  bms_ocv_cell51_c_ = bmsocvcell51c();
  bms_odv_cell51_c_ = bmsodvcell51c();
  bms_ocv_batt51_c_ = bmsocvbatt51c();
  bms_odv_batt51_c_ = bmsodvbatt51c();
  bms_cell_volt_diff51_c_ = bmscellvoltdiff51c();
  bms_temp_h51_c_ = bmstemph51c();
  bms_temp_l51_c_ = bmstempl51c();
  bms_temp_diff51_c_ = bmstempdiff51c();
  bms_war_chg_overcurrent51_c_ = bmswarchgovercurrent51c();
  bms_soc_h51_c_ = bmssoch51c();
  bms_soc_l51_c_ = bmssocl51c();
  bms_time_of_heating_too_long51_c_ = bmstimeofheatingtoolong51c();
  bms_soc_break51_c_ = bmssocbreak51c();
  bms_dis_char_over_cur51_c_ = bmsdischarovercur51c();
  bms_char_over_cur_slow51_c_ = bmscharovercurslow51c();
  bms_fast_char_over_cur51_c_ = bmsfastcharovercur51c();
  bms_alm_sense_cell51_c_ = bmsalmsensecell51c();
  bms_alm_sense_temp51_c_ = bmsalmsensetemp51c();
  bms_alm_sense_curr51_c_ = bmsalmsensecurr51c();
  bms_hvil51_c_ = bmshvil51c();
  bms_war_in_can_fault51_c_ = bmswarincanfault51c();
  bms_lst_com_with_obc51_c_ = bmslstcomwithobc51c();
  bms_lst_com_with_vcu51_c_ = bmslstcomwithvcu51c();
  bms_precharger_fault51_c_ = bmsprechargerfault51c();
  bms_pos_relay_conglutination51_c_ = bmsposrelayconglutination51c();
  bms_neg_relay_conglutination51_c_ = bmsnegrelayconglutination51c();
  spare351_c_ = spare351c();
  spare451_c_ = spare451c();
  dcdc_high_tem_alarm51_c_ = dcdchightemalarm51c();
  dcdc_hardware_fault51_c_ = dcdchardwarefault51c();
  dcdc_network_fault51_c_ = dcdcnetworkfault51c();
}


// config detail: {'bit': 0, 'description': '前左电控硬件故障', 'enum': {0: 'FLMC_HARDWARE_FAULT51_C_NORMAL', 1: 'FLMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::flmchardwarefault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': '前左电控温度故障', 'enum': {0: 'FLMC_TEM_FAULT51_C_NORMAL', 1: 'FLMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::flmctemfault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '前左电机温度故障', 'enum': {0: 'FLM_TEM_FAULT51_C_NORMAL', 1: 'FLM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::flmtemfault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': '后左电控硬件故障', 'enum': {0: 'RLMC_HARDWARE_FAULT51_C_NORMAL', 1: 'RLMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rlmchardwarefault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '后左电控温度故障', 'enum': {0: 'RLMC_TEM_FAULT51_C_NORMAL', 1: 'RLMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rlmctemfault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 5, 'description': '后左电机温度故障', 'enum': {0: 'RLM_TEM_FAULT51_C_NORMAL', 1: 'RLM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rlmtemfault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': '前右电控硬件故障', 'enum': {0: 'FRMC_HARDWARE_FAULT51_C_NORMAL', 1: 'FRMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::frmchardwarefault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '前右电控温度故障', 'enum': {0: 'FRMC_TEM_FAULT51_C_NORMAL', 1: 'FRMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::frmctemfault51c() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '前右电机温度故障', 'enum': {0: 'FRM_TEM_FAULT51_C_NORMAL', 1: 'FRM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::frmtemfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': '后右电控硬件故障', 'enum': {0: 'RRMC_HARDWARE_FAULT51_C_NORMAL', 1: 'RRMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rrmchardwarefault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': '后右电控温度故障', 'enum': {0: 'RRMC_TEM_FAULT51_C_NORMAL', 1: 'RRMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rrmctemfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 11, 'description': '后右电机温度故障', 'enum': {0: 'RRM_TEM_FAULT51_C_NORMAL', 1: 'RRM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rrmtemfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': '前左电控网络故障', 'enum': {0: 'FLMC_NETWORK_FAULT51_C_NORMAL', 1: 'FLMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::flmcnetworkfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 13, 'description': '前右电控网络故障', 'enum': {0: 'FRMC_NETWORK_FAULT51_C_NORMAL', 1: 'FRMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::frmcnetworkfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': '后左电控网络故障', 'enum': {0: 'RLMC_NETWORK_FAULT51_C_NORMAL', 1: 'RLMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rlmcnetworkfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': '后右电控网络故障', 'enum': {0: 'RRMC_NETWORK_FAULT51_C_NORMAL', 1: 'RRMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rrmcnetworkfault51c() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '前电子转向硬件故障', 'enum': {0: 'FR_STEER_HARDWARE_FAULT51_C_NORMAL', 1: 'FR_STEER_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::frsteerhardwarefault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 17, 'description': '后电子转向硬件故障', 'enum': {0: 'RR_STEER_HARDWARE_FAULT51_C_NORMAL', 1: 'RR_STEER_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rrsteerhardwarefault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': '前电子转向网络故障', 'enum': {0: 'FR_STEER_NETWORK_FAULT51_C_NORMAL', 1: 'FR_STEER_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::frsteernetworkfault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 19, 'description': '后电子转向网络故障', 'enum': {0: 'RR_STEER_NETWORK_FAULT51_C_NORMAL', 1: 'RR_STEER_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rrsteernetworkfault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': '电制动系统硬件故障', 'enum': {0: 'BRAKE_HARDWARE_FAULT51_C_NORMAL', 1: 'BRAKE_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::brakehardwarefault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 21, 'description': '电制动系统高温故障', 'enum': {0: 'BRAKE_HIGH_TEM_FAULT51_C_NORMAL', 1: 'BRAKE_HIGH_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_high_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::brakehightemfault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 22, 'description': '制动液位过低', 'enum': {0: 'BRAKE_LUID_LEVEL_LOW51_C_NORMAL', 1: 'BRAKE_LUID_LEVEL_LOW51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_luid_level_low51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::brakeluidlevellow51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 23, 'description': '电制动系统网络故障', 'enum': {0: 'BRAKE_NETWORK_FAULT51_C_NORMAL', 1: 'BRAKE_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::brakenetworkfault51c() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '驻车冗余系统硬件故障', 'enum': {0: 'PARK_HARDWARE_FAULT51_C_NORMAL', 1: 'PARK_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::parkhardwarefault51c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 25, 'description': '驻车冗余系统网络故障', 'enum': {0: 'PARK_NETWORK_FAULT51_C_NORMAL', 1: 'PARK_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::parknetworkfault51c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': '无线遥控器系统网络故障', 'enum': {0: 'RCU_NETWORK_FAULT51_C_NORMAL', 1: 'RCU_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rcunetworkfault51c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 27, 'description': '无线遥控器系统信号强度弱', 'enum': {0: 'RCU_WEAK_SIGNAL51_C_NORMAL', 1: 'RCU_WEAK_SIGNAL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_weak_signal51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rcuweaksignal51c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '无线遥控电池电量报警', 'enum': {0: 'RCU_ELEC_LOW_ALARM51_C_NORMAL', 1: 'RCU_ELEC_LOW_ALARM51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_elec_low_alarm51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::rcueleclowalarm51c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 29, 'description': '预留', 'enum': {0: 'SPARE151_C_NORMAL', 1: 'SPARE151_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare151_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::spare151c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '预留', 'enum': {0: 'SPARE251_C_NORMAL', 1: 'SPARE251_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare251_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::spare251c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 31, 'description': 'BMS系统网络故障', 'enum': {0: 'BMS_NETWORK_FAULT51_C_NORMAL', 1: 'BMS_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsnetworkfault51c() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '绝缘报警', 'enum': {0: 'BMS_INSULATION_FAULT51_C_NORMAL', 1: 'BMS_INSULATION_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_insulation_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsinsulationfault51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 33, 'description': '单体电压过压', 'enum': {0: 'BMS_OCV_CELL51_C_NORMAL', 1: 'BMS_OCV_CELL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_cell51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsocvcell51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': '单体电压欠压', 'enum': {0: 'BMS_ODV_CELL51_C_NORMAL', 1: 'BMS_ODV_CELL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_cell51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsodvcell51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 35, 'description': '总压过高', 'enum': {0: 'BMS_OCV_BATT51_C_NORMAL', 1: 'BMS_OCV_BATT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_batt51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsocvbatt51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': '总压过低', 'enum': {0: 'BMS_ODV_BATT51_C_NORMAL', 1: 'BMS_ODV_BATT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_batt51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsodvbatt51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 37, 'description': '压差过大', 'enum': {0: 'BMS_CELL_VOLT_DIFF51_C_NORMAL', 1: 'BMS_CELL_VOLT_DIFF51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_cell_volt_diff51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmscellvoltdiff51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 38, 'description': '电池温度过高', 'enum': {0: 'BMS_TEMP_H51_C_NORMAL', 1: 'BMS_TEMP_H51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_h51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmstemph51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 39, 'description': '电池温度过低', 'enum': {0: 'BMS_TEMP_L51_C_NORMAL', 1: 'BMS_TEMP_L51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_l51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmstempl51c() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '温差过大', 'enum': {0: 'BMS_TEMP_DIFF51_C_NORMAL', 1: 'BMS_TEMP_DIFF51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_diff51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmstempdiff51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 41, 'description': '回馈过流', 'enum': {0: 'BMS_WAR_CHG_OVERCURRENT51_C_NORMAL', 1: 'BMS_WAR_CHG_OVERCURRENT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_chg_overcurrent51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmswarchgovercurrent51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': 'SOC过高', 'enum': {0: 'BMS_SOC_H51_C_NORMAL', 1: 'BMS_SOC_H51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_h51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmssoch51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 43, 'description': 'SOC过低', 'enum': {0: 'BMS_SOC_L51_C_NORMAL', 1: 'BMS_SOC_L51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_l51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmssocl51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': '充电加热超时', 'enum': {0: 'BMS_TIME_OF_HEATING_TOO_LONG51_C_NORMAL', 1: 'BMS_TIME_OF_HEATING_TOO_LONG51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_time_of_heating_too_long51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmstimeofheatingtoolong51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 45, 'description': 'SOC跳变', 'enum': {0: 'BMS_SOC_BREAK51_C_NORMAL', 1: 'BMS_SOC_BREAK51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_break51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmssocbreak51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 46, 'description': '放电过流', 'enum': {0: 'BMS_DIS_CHAR_OVER_CUR51_C_NORMAL', 1: 'BMS_DIS_CHAR_OVER_CUR51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_dis_char_over_cur51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsdischarovercur51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 47, 'description': '慢充充电过流', 'enum': {0: 'BMS_CHAR_OVER_CUR_SLOW51_C_NORMAL', 1: 'BMS_CHAR_OVER_CUR_SLOW51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_char_over_cur_slow51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmscharovercurslow51c() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': '快充充电过流', 'enum': {0: 'BMS_FAST_CHAR_OVER_CUR51_C_NORMAL', 1: 'BMS_FAST_CHAR_OVER_CUR51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_fast_char_over_cur51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsfastcharovercur51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 49, 'description': '单体电压采集故障', 'enum': {0: 'BMS_ALM_SENSE_CELL51_C_NORMAL', 1: 'BMS_ALM_SENSE_CELL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_cell51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsalmsensecell51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 50, 'description': '温度采集故障', 'enum': {0: 'BMS_ALM_SENSE_TEMP51_C_NORMAL', 1: 'BMS_ALM_SENSE_TEMP51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_temp51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsalmsensetemp51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 51, 'description': '电流传感器故障', 'enum': {0: 'BMS_ALM_SENSE_CURR51_C_NORMAL', 1: 'BMS_ALM_SENSE_CURR51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_curr51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsalmsensecurr51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 52, 'description': '高压互锁故障', 'enum': {0: 'BMS_HVIL51_C_NORMAL', 1: 'BMS_HVIL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_hvil51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmshvil51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 53, 'description': '内网通信', 'enum': {0: 'BMS_WAR_IN_CAN_FAULT51_C_NORMAL', 1: 'BMS_WAR_IN_CAN_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_in_can_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmswarincanfault51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 54, 'description': '充电机通信中断', 'enum': {0: 'BMS_LST_COM_WITH_OBC51_C_NORMAL', 1: 'BMS_LST_COM_WITH_OBC51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_obc51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmslstcomwithobc51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 55, 'description': '整车通信中断', 'enum': {0: 'BMS_LST_COM_WITH_VCU51_C_NORMAL', 1: 'BMS_LST_COM_WITH_VCU51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_vcu51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmslstcomwithvcu51c() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '预充失败', 'enum': {0: 'BMS_PRECHARGER_FAULT51_C_NORMAL', 1: 'BMS_PRECHARGER_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_precharger_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsprechargerfault51c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 57, 'description': '总正继电器黏连', 'enum': {0: 'BMS_POS_RELAY_CONGLUTINATION51_C_NORMAL', 1: 'BMS_POS_RELAY_CONGLUTINATION51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_pos_relay_conglutination51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsposrelayconglutination51c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 58, 'description': '总负继电器黏连', 'enum': {0: 'BMS_NEG_RELAY_CONGLUTINATION51_C_NORMAL', 1: 'BMS_NEG_RELAY_CONGLUTINATION51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_neg_relay_conglutination51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::bmsnegrelayconglutination51c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE351_C_NORMAL', 1: 'SPARE351_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare351_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::spare351c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE451_C_NORMAL', 1: 'SPARE451_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare451_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::spare451c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 61, 'description': 'DCDC系统过温故障', 'enum': {0: 'DCDC_HIGH_TEM_ALARM51_C_NORMAL', 1: 'DCDC_HIGH_TEM_ALARM51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_high_tem_alarm51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::dcdchightemalarm51c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 62, 'description': 'DCDC系统硬件故障', 'enum': {0: 'DCDC_HARDWARE_FAULT51_C_NORMAL', 1: 'DCDC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::dcdchardwarefault51c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 63, 'description': 'DCDC系统网络故障', 'enum': {0: 'DCDC_NETWORK_FAULT51_C_NORMAL', 1: 'DCDC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures1::dcdcnetworkfault51c() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

