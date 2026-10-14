#include <libs/vehicle_errcode1.hpp>


VehicleErrcode1::VehicleErrcode1() {}

void VehicleErrcode1::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VehicleErrcode1::Parse() {
  flmc_hardware_fault_ = flmchardwarefault();
  flmc_tem_fault_ = flmctemfault();
  flm_tem_fault_ = flmtemfault();
  rlmc_hardware_fault_ = rlmchardwarefault();
  rlmc_tem_fault_ = rlmctemfault();
  rlm_tem_fault_ = rlmtemfault();
  frmc_hardware_fault_ = frmchardwarefault();
  frmc_tem_fault_ = frmctemfault();
  frm_tem_fault_ = frmtemfault();
  rrmc_hardware_fault_ = rrmchardwarefault();
  rrmc_tem_fault_ = rrmctemfault();
  rrm_tem_fault_ = rrmtemfault();
  flmc_network_fault_ = flmcnetworkfault();
  frmc_network_fault_ = frmcnetworkfault();
  rlmc_network_fault_ = rlmcnetworkfault();
  rrmc_network_fault_ = rrmcnetworkfault();
  fr_steer_hardware_fault_ = frsteerhardwarefault();
  rr_steer_hardware_fault_ = rrsteerhardwarefault();
  fr_steer_network_fault_ = frsteernetworkfault();
  rr_steer_network_fault_ = rrsteernetworkfault();
  brake_hardware_fault_ = brakehardwarefault();
  brake_high_tem_fault_ = brakehightemfault();
  brake_luid_level_low_ = brakeluidlevellow();
  brake_network_fault_ = brakenetworkfault();
  park_hardware_fault_ = parkhardwarefault();
  park_network_fault_ = parknetworkfault();
  rcu_network_fault_ = rcunetworkfault();
  rcu_weak_signal_ = rcuweaksignal();
  rcu_elec_low_alarm_ = rcueleclowalarm();
  spare1_ = spare1();
  spare2_ = spare2();
  bms_network_fault_ = bmsnetworkfault();
  bms_insulation_fault_ = bmsinsulationfault();
  bms_ocv_cell_ = bmsocvcell();
  bms_odv_cell_ = bmsodvcell();
  bms_ocv_batt_ = bmsocvbatt();
  bms_odv_batt_ = bmsodvbatt();
  bms_cell_volt_diff_ = bmscellvoltdiff();
  bms_temp_h_ = bmstemph();
  bms_temp_l_ = bmstempl();
  bms_temp_diff_ = bmstempdiff();
  bms_war_chg_overcurrent_ = bmswarchgovercurrent();
  bms_soc_h_ = bmssoch();
  bms_soc_l_ = bmssocl();
  bms_time_of_heating_too_long_ = bmstimeofheatingtoolong();
  bms_soc_break_ = bmssocbreak();
  bms_dis_char_over_cur_ = bmsdischarovercur();
  bms_char_over_cur_slow_ = bmscharovercurslow();
  bms_fast_char_over_cur_ = bmsfastcharovercur();
  bms_alm_sense_cell_ = bmsalmsensecell();
  bms_alm_sense_temp_ = bmsalmsensetemp();
  bms_alm_sense_curr_ = bmsalmsensecurr();
  bms_hvil_ = bmshvil();
  bms_war_in_can_fault_ = bmswarincanfault();
  bms_lst_com_with_obc_ = bmslstcomwithobc();
  bms_lst_com_with_vcu_ = bmslstcomwithvcu();
  bms_precharger_fault_ = bmsprechargerfault();
  bms_pos_relay_conglutination_ = bmsposrelayconglutination();
  bms_neg_relay_conglutination_ = bmsnegrelayconglutination();
  spare3_ = spare3();
  spare4_ = spare4();
  dcdc_high_tem_alarm_ = dcdchightemalarm();
  dcdc_hardware_fault_ = dcdchardwarefault();
  dcdc_network_fault_ = dcdcnetworkfault();
}


// config detail: {'bit': 0, 'description': '前左电控硬件故障', 'enum': {0: 'FLMC_HARDWARE_FAULT_NORMAL', 1: 'FLMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::flmchardwarefault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': '前左电控温度故障', 'enum': {0: 'FLMC_TEM_FAULT_NORMAL', 1: 'FLMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::flmctemfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '前左电机温度故障', 'enum': {0: 'FLM_TEM_FAULT_NORMAL', 1: 'FLM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::flmtemfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': '后左电控硬件故障', 'enum': {0: 'RLMC_HARDWARE_FAULT_NORMAL', 1: 'RLMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rlmchardwarefault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '后左电控温度故障', 'enum': {0: 'RLMC_TEM_FAULT_NORMAL', 1: 'RLMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rlmctemfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 5, 'description': '后左电机温度故障', 'enum': {0: 'RLM_TEM_FAULT_NORMAL', 1: 'RLM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rlmtemfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': '前右电控硬件故障', 'enum': {0: 'FRMC_HARDWARE_FAULT_NORMAL', 1: 'FRMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::frmchardwarefault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '前右电控温度故障', 'enum': {0: 'FRMC_TEM_FAULT_NORMAL', 1: 'FRMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::frmctemfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '前右电机温度故障', 'enum': {0: 'FRM_TEM_FAULT_NORMAL', 1: 'FRM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::frmtemfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': '后右电控硬件故障', 'enum': {0: 'RRMC_HARDWARE_FAULT_NORMAL', 1: 'RRMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rrmchardwarefault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': '后右电控温度故障', 'enum': {0: 'RRMC_TEM_FAULT_NORMAL', 1: 'RRMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rrmctemfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 11, 'description': '后右电机温度故障', 'enum': {0: 'RRM_TEM_FAULT_NORMAL', 1: 'RRM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rrmtemfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': '前左电控网络故障', 'enum': {0: 'FLMC_NETWORK_FAULT_NORMAL', 1: 'FLMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::flmcnetworkfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 13, 'description': '前右电控网络故障', 'enum': {0: 'FRMC_NETWORK_FAULT_NORMAL', 1: 'FRMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::frmcnetworkfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': '后左电控网络故障', 'enum': {0: 'RLMC_NETWORK_FAULT_NORMAL', 1: 'RLMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rlmcnetworkfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': '后右电控网络故障', 'enum': {0: 'RRMC_NETWORK_FAULT_NORMAL', 1: 'RRMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rrmcnetworkfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '前电子转向硬件故障', 'enum': {0: 'FR_STEER_HARDWARE_FAULT_NORMAL', 1: 'FR_STEER_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::frsteerhardwarefault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 17, 'description': '后电子转向硬件故障', 'enum': {0: 'RR_STEER_HARDWARE_FAULT_NORMAL', 1: 'RR_STEER_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rrsteerhardwarefault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': '前电子转向网络故障', 'enum': {0: 'FR_STEER_NETWORK_FAULT_NORMAL', 1: 'FR_STEER_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::frsteernetworkfault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 19, 'description': '后电子转向网络故障', 'enum': {0: 'RR_STEER_NETWORK_FAULT_NORMAL', 1: 'RR_STEER_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rrsteernetworkfault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': '电制动系统硬件故障', 'enum': {0: 'BRAKE_HARDWARE_FAULT_NORMAL', 1: 'BRAKE_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::brakehardwarefault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 21, 'description': '电制动系统高温故障', 'enum': {0: 'BRAKE_HIGH_TEM_FAULT_NORMAL', 1: 'BRAKE_HIGH_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_high_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::brakehightemfault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 22, 'description': '制动液位过低', 'enum': {0: 'BRAKE_LUID_LEVEL_LOW_NORMAL', 1: 'BRAKE_LUID_LEVEL_LOW_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_luid_level_low', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::brakeluidlevellow() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 23, 'description': '电制动系统网络故障', 'enum': {0: 'BRAKE_NETWORK_FAULT_NORMAL', 1: 'BRAKE_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::brakenetworkfault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '驻车冗余系统硬件故障', 'enum': {0: 'PARK_HARDWARE_FAULT_NORMAL', 1: 'PARK_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::parkhardwarefault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 25, 'description': '驻车冗余系统网络故障', 'enum': {0: 'PARK_NETWORK_FAULT_NORMAL', 1: 'PARK_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::parknetworkfault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': '无线遥控器系统网络故障', 'enum': {0: 'RCU_NETWORK_FAULT_NORMAL', 1: 'RCU_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rcunetworkfault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 27, 'description': '无线遥控器系统信号强度弱', 'enum': {0: 'RCU_WEAK_SIGNAL_NORMAL', 1: 'RCU_WEAK_SIGNAL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_weak_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rcuweaksignal() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '无线遥控电池电量报警', 'enum': {0: 'RCU_ELEC_LOW_ALARM_NORMAL', 1: 'RCU_ELEC_LOW_ALARM_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_elec_low_alarm', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::rcueleclowalarm() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 29, 'description': '预留', 'enum': {0: 'SPARE1_NORMAL', 1: 'SPARE1_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::spare1() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '预留', 'enum': {0: 'SPARE2_NORMAL', 1: 'SPARE2_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::spare2() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 31, 'description': 'BMS系统网络故障', 'enum': {0: 'BMS_NETWORK_FAULT_NORMAL', 1: 'BMS_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsnetworkfault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '绝缘报警', 'enum': {0: 'BMS_INSULATION_FAULT_NORMAL', 1: 'BMS_INSULATION_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_insulation_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsinsulationfault() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 33, 'description': '单体电压过压', 'enum': {0: 'BMS_OCV_CELL_NORMAL', 1: 'BMS_OCV_CELL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_cell', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsocvcell() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': '单体电压欠压', 'enum': {0: 'BMS_ODV_CELL_NORMAL', 1: 'BMS_ODV_CELL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_cell', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsodvcell() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 35, 'description': '总压过高', 'enum': {0: 'BMS_OCV_BATT_NORMAL', 1: 'BMS_OCV_BATT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_batt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsocvbatt() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': '总压过低', 'enum': {0: 'BMS_ODV_BATT_NORMAL', 1: 'BMS_ODV_BATT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_batt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsodvbatt() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 37, 'description': '压差过大', 'enum': {0: 'BMS_CELL_VOLT_DIFF_NORMAL', 1: 'BMS_CELL_VOLT_DIFF_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_cell_volt_diff', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmscellvoltdiff() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 38, 'description': '电池温度过高', 'enum': {0: 'BMS_TEMP_H_NORMAL', 1: 'BMS_TEMP_H_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_h', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmstemph() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 39, 'description': '电池温度过低', 'enum': {0: 'BMS_TEMP_L_NORMAL', 1: 'BMS_TEMP_L_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_l', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmstempl() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '温差过大', 'enum': {0: 'BMS_TEMP_DIFF_NORMAL', 1: 'BMS_TEMP_DIFF_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_diff', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmstempdiff() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 41, 'description': '回馈过流', 'enum': {0: 'BMS_WAR_CHG_OVERCURRENT_NORMAL', 1: 'BMS_WAR_CHG_OVERCURRENT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_chg_overcurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmswarchgovercurrent() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': 'SOC过高', 'enum': {0: 'BMS_SOC_H_NORMAL', 1: 'BMS_SOC_H_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_h', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmssoch() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 43, 'description': 'SOC过低', 'enum': {0: 'BMS_SOC_L_NORMAL', 1: 'BMS_SOC_L_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_l', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmssocl() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': '充电加热超时', 'enum': {0: 'BMS_TIME_OF_HEATING_TOO_LONG_NORMAL', 1: 'BMS_TIME_OF_HEATING_TOO_LONG_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_time_of_heating_too_long', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmstimeofheatingtoolong() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 45, 'description': 'SOC跳变', 'enum': {0: 'BMS_SOC_BREAK_NORMAL', 1: 'BMS_SOC_BREAK_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_break', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmssocbreak() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 46, 'description': '放电过流', 'enum': {0: 'BMS_DIS_CHAR_OVER_CUR_NORMAL', 1: 'BMS_DIS_CHAR_OVER_CUR_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_dis_char_over_cur', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsdischarovercur() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 47, 'description': '慢充充电过流', 'enum': {0: 'BMS_CHAR_OVER_CUR_SLOW_NORMAL', 1: 'BMS_CHAR_OVER_CUR_SLOW_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_char_over_cur_slow', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmscharovercurslow() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': '快充充电过流', 'enum': {0: 'BMS_FAST_CHAR_OVER_CUR_NORMAL', 1: 'BMS_FAST_CHAR_OVER_CUR_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_fast_char_over_cur', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsfastcharovercur() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 49, 'description': '单体电压采集故障', 'enum': {0: 'BMS_ALM_SENSE_CELL_NORMAL', 1: 'BMS_ALM_SENSE_CELL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_cell', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsalmsensecell() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 50, 'description': '温度采集故障', 'enum': {0: 'BMS_ALM_SENSE_TEMP_NORMAL', 1: 'BMS_ALM_SENSE_TEMP_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_temp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsalmsensetemp() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 51, 'description': '电流传感器故障', 'enum': {0: 'BMS_ALM_SENSE_CURR_NORMAL', 1: 'BMS_ALM_SENSE_CURR_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_curr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsalmsensecurr() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 52, 'description': '高压互锁故障', 'enum': {0: 'BMS_HVIL_NORMAL', 1: 'BMS_HVIL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_hvil', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmshvil() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 53, 'description': '内网通信', 'enum': {0: 'BMS_WAR_IN_CAN_FAULT_NORMAL', 1: 'BMS_WAR_IN_CAN_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_in_can_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmswarincanfault() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 54, 'description': '充电机通信中断', 'enum': {0: 'BMS_LST_COM_WITH_OBC_NORMAL', 1: 'BMS_LST_COM_WITH_OBC_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_obc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmslstcomwithobc() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 55, 'description': '整车通信中断', 'enum': {0: 'BMS_LST_COM_WITH_VCU_NORMAL', 1: 'BMS_LST_COM_WITH_VCU_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_vcu', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmslstcomwithvcu() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '预充失败', 'enum': {0: 'BMS_PRECHARGER_FAULT_NORMAL', 1: 'BMS_PRECHARGER_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_precharger_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsprechargerfault() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 57, 'description': '总正继电器黏连', 'enum': {0: 'BMS_POS_RELAY_CONGLUTINATION_NORMAL', 1: 'BMS_POS_RELAY_CONGLUTINATION_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_pos_relay_conglutination', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsposrelayconglutination() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 58, 'description': '总负继电器黏连', 'enum': {0: 'BMS_NEG_RELAY_CONGLUTINATION_NORMAL', 1: 'BMS_NEG_RELAY_CONGLUTINATION_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_neg_relay_conglutination', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::bmsnegrelayconglutination() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE3_NORMAL', 1: 'SPARE3_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::spare3() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE4_NORMAL', 1: 'SPARE4_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::spare4() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 61, 'description': 'DCDC系统过温故障', 'enum': {0: 'DCDC_HIGH_TEM_ALARM_NORMAL', 1: 'DCDC_HIGH_TEM_ALARM_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_high_tem_alarm', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::dcdchightemalarm() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 62, 'description': 'DCDC系统硬件故障', 'enum': {0: 'DCDC_HARDWARE_FAULT_NORMAL', 1: 'DCDC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::dcdchardwarefault() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 63, 'description': 'DCDC系统网络故障', 'enum': {0: 'DCDC_NETWORK_FAULT_NORMAL', 1: 'DCDC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode1::dcdcnetworkfault() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

