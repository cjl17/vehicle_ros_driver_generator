#pragma once

#include <libs/Byte.hpp>

class HistoricalVehiclefailures1 {
public:
  static const uint32_t ID = 0x51C;
  HistoricalVehiclefailures1();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int flmc_hardware_fault51_c_;
  int flmc_tem_fault51_c_;
  int flm_tem_fault51_c_;
  int rlmc_hardware_fault51_c_;
  int rlmc_tem_fault51_c_;
  int rlm_tem_fault51_c_;
  int frmc_hardware_fault51_c_;
  int frmc_tem_fault51_c_;
  int frm_tem_fault51_c_;
  int rrmc_hardware_fault51_c_;
  int rrmc_tem_fault51_c_;
  int rrm_tem_fault51_c_;
  int flmc_network_fault51_c_;
  int frmc_network_fault51_c_;
  int rlmc_network_fault51_c_;
  int rrmc_network_fault51_c_;
  int fr_steer_hardware_fault51_c_;
  int rr_steer_hardware_fault51_c_;
  int fr_steer_network_fault51_c_;
  int rr_steer_network_fault51_c_;
  int brake_hardware_fault51_c_;
  int brake_high_tem_fault51_c_;
  int brake_luid_level_low51_c_;
  int brake_network_fault51_c_;
  int park_hardware_fault51_c_;
  int park_network_fault51_c_;
  int rcu_network_fault51_c_;
  int rcu_weak_signal51_c_;
  int rcu_elec_low_alarm51_c_;
  int spare151_c_;
  int spare251_c_;
  int bms_network_fault51_c_;
  int bms_insulation_fault51_c_;
  int bms_ocv_cell51_c_;
  int bms_odv_cell51_c_;
  int bms_ocv_batt51_c_;
  int bms_odv_batt51_c_;
  int bms_cell_volt_diff51_c_;
  int bms_temp_h51_c_;
  int bms_temp_l51_c_;
  int bms_temp_diff51_c_;
  int bms_war_chg_overcurrent51_c_;
  int bms_soc_h51_c_;
  int bms_soc_l51_c_;
  int bms_time_of_heating_too_long51_c_;
  int bms_soc_break51_c_;
  int bms_dis_char_over_cur51_c_;
  int bms_char_over_cur_slow51_c_;
  int bms_fast_char_over_cur51_c_;
  int bms_alm_sense_cell51_c_;
  int bms_alm_sense_temp51_c_;
  int bms_alm_sense_curr51_c_;
  int bms_hvil51_c_;
  int bms_war_in_can_fault51_c_;
  int bms_lst_com_with_obc51_c_;
  int bms_lst_com_with_vcu51_c_;
  int bms_precharger_fault51_c_;
  int bms_pos_relay_conglutination51_c_;
  int bms_neg_relay_conglutination51_c_;
  int spare351_c_;
  int spare451_c_;
  int dcdc_high_tem_alarm51_c_;
  int dcdc_hardware_fault51_c_;
  int dcdc_network_fault51_c_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '前左电控硬件故障', 'enum': {0: 'FLMC_HARDWARE_FAULT51_C_NORMAL', 1: 'FLMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmchardwarefault51c();

  // config detail: {'bit': 1, 'description': '前左电控温度故障', 'enum': {0: 'FLMC_TEM_FAULT51_C_NORMAL', 1: 'FLMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmctemfault51c();

  // config detail: {'bit': 2, 'description': '前左电机温度故障', 'enum': {0: 'FLM_TEM_FAULT51_C_NORMAL', 1: 'FLM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmtemfault51c();

  // config detail: {'bit': 3, 'description': '后左电控硬件故障', 'enum': {0: 'RLMC_HARDWARE_FAULT51_C_NORMAL', 1: 'RLMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmchardwarefault51c();

  // config detail: {'bit': 4, 'description': '后左电控温度故障', 'enum': {0: 'RLMC_TEM_FAULT51_C_NORMAL', 1: 'RLMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmctemfault51c();

  // config detail: {'bit': 5, 'description': '后左电机温度故障', 'enum': {0: 'RLM_TEM_FAULT51_C_NORMAL', 1: 'RLM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmtemfault51c();

  // config detail: {'bit': 6, 'description': '前右电控硬件故障', 'enum': {0: 'FRMC_HARDWARE_FAULT51_C_NORMAL', 1: 'FRMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmchardwarefault51c();

  // config detail: {'bit': 7, 'description': '前右电控温度故障', 'enum': {0: 'FRMC_TEM_FAULT51_C_NORMAL', 1: 'FRMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmctemfault51c();

  // config detail: {'bit': 8, 'description': '前右电机温度故障', 'enum': {0: 'FRM_TEM_FAULT51_C_NORMAL', 1: 'FRM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmtemfault51c();

  // config detail: {'bit': 9, 'description': '后右电控硬件故障', 'enum': {0: 'RRMC_HARDWARE_FAULT51_C_NORMAL', 1: 'RRMC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmchardwarefault51c();

  // config detail: {'bit': 10, 'description': '后右电控温度故障', 'enum': {0: 'RRMC_TEM_FAULT51_C_NORMAL', 1: 'RRMC_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmctemfault51c();

  // config detail: {'bit': 11, 'description': '后右电机温度故障', 'enum': {0: 'RRM_TEM_FAULT51_C_NORMAL', 1: 'RRM_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrm_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmtemfault51c();

  // config detail: {'bit': 12, 'description': '前左电控网络故障', 'enum': {0: 'FLMC_NETWORK_FAULT51_C_NORMAL', 1: 'FLMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmcnetworkfault51c();

  // config detail: {'bit': 13, 'description': '前右电控网络故障', 'enum': {0: 'FRMC_NETWORK_FAULT51_C_NORMAL', 1: 'FRMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmcnetworkfault51c();

  // config detail: {'bit': 14, 'description': '后左电控网络故障', 'enum': {0: 'RLMC_NETWORK_FAULT51_C_NORMAL', 1: 'RLMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmcnetworkfault51c();

  // config detail: {'bit': 15, 'description': '后右电控网络故障', 'enum': {0: 'RRMC_NETWORK_FAULT51_C_NORMAL', 1: 'RRMC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmcnetworkfault51c();

  // config detail: {'bit': 16, 'description': '前电子转向硬件故障', 'enum': {0: 'FR_STEER_HARDWARE_FAULT51_C_NORMAL', 1: 'FR_STEER_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frsteerhardwarefault51c();

  // config detail: {'bit': 17, 'description': '后电子转向硬件故障', 'enum': {0: 'RR_STEER_HARDWARE_FAULT51_C_NORMAL', 1: 'RR_STEER_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrsteerhardwarefault51c();

  // config detail: {'bit': 18, 'description': '前电子转向网络故障', 'enum': {0: 'FR_STEER_NETWORK_FAULT51_C_NORMAL', 1: 'FR_STEER_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frsteernetworkfault51c();

  // config detail: {'bit': 19, 'description': '后电子转向网络故障', 'enum': {0: 'RR_STEER_NETWORK_FAULT51_C_NORMAL', 1: 'RR_STEER_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrsteernetworkfault51c();

  // config detail: {'bit': 20, 'description': '电制动系统硬件故障', 'enum': {0: 'BRAKE_HARDWARE_FAULT51_C_NORMAL', 1: 'BRAKE_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakehardwarefault51c();

  // config detail: {'bit': 21, 'description': '电制动系统高温故障', 'enum': {0: 'BRAKE_HIGH_TEM_FAULT51_C_NORMAL', 1: 'BRAKE_HIGH_TEM_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_high_tem_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakehightemfault51c();

  // config detail: {'bit': 22, 'description': '制动液位过低', 'enum': {0: 'BRAKE_LUID_LEVEL_LOW51_C_NORMAL', 1: 'BRAKE_LUID_LEVEL_LOW51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_luid_level_low51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakeluidlevellow51c();

  // config detail: {'bit': 23, 'description': '电制动系统网络故障', 'enum': {0: 'BRAKE_NETWORK_FAULT51_C_NORMAL', 1: 'BRAKE_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakenetworkfault51c();

  // config detail: {'bit': 24, 'description': '驻车冗余系统硬件故障', 'enum': {0: 'PARK_HARDWARE_FAULT51_C_NORMAL', 1: 'PARK_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int parkhardwarefault51c();

  // config detail: {'bit': 25, 'description': '驻车冗余系统网络故障', 'enum': {0: 'PARK_NETWORK_FAULT51_C_NORMAL', 1: 'PARK_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int parknetworkfault51c();

  // config detail: {'bit': 26, 'description': '无线遥控器系统网络故障', 'enum': {0: 'RCU_NETWORK_FAULT51_C_NORMAL', 1: 'RCU_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rcunetworkfault51c();

  // config detail: {'bit': 27, 'description': '无线遥控器系统信号强度弱', 'enum': {0: 'RCU_WEAK_SIGNAL51_C_NORMAL', 1: 'RCU_WEAK_SIGNAL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_weak_signal51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rcuweaksignal51c();

  // config detail: {'bit': 28, 'description': '无线遥控电池电量报警', 'enum': {0: 'RCU_ELEC_LOW_ALARM51_C_NORMAL', 1: 'RCU_ELEC_LOW_ALARM51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_elec_low_alarm51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rcueleclowalarm51c();

  // config detail: {'bit': 29, 'description': '预留', 'enum': {0: 'SPARE151_C_NORMAL', 1: 'SPARE151_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare151_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare151c();

  // config detail: {'bit': 30, 'description': '预留', 'enum': {0: 'SPARE251_C_NORMAL', 1: 'SPARE251_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare251_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare251c();

  // config detail: {'bit': 31, 'description': 'BMS系统网络故障', 'enum': {0: 'BMS_NETWORK_FAULT51_C_NORMAL', 1: 'BMS_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsnetworkfault51c();

  // config detail: {'bit': 32, 'description': '绝缘报警', 'enum': {0: 'BMS_INSULATION_FAULT51_C_NORMAL', 1: 'BMS_INSULATION_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_insulation_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsinsulationfault51c();

  // config detail: {'bit': 33, 'description': '单体电压过压', 'enum': {0: 'BMS_OCV_CELL51_C_NORMAL', 1: 'BMS_OCV_CELL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_cell51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsocvcell51c();

  // config detail: {'bit': 34, 'description': '单体电压欠压', 'enum': {0: 'BMS_ODV_CELL51_C_NORMAL', 1: 'BMS_ODV_CELL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_cell51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsodvcell51c();

  // config detail: {'bit': 35, 'description': '总压过高', 'enum': {0: 'BMS_OCV_BATT51_C_NORMAL', 1: 'BMS_OCV_BATT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_batt51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsocvbatt51c();

  // config detail: {'bit': 36, 'description': '总压过低', 'enum': {0: 'BMS_ODV_BATT51_C_NORMAL', 1: 'BMS_ODV_BATT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_batt51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsodvbatt51c();

  // config detail: {'bit': 37, 'description': '压差过大', 'enum': {0: 'BMS_CELL_VOLT_DIFF51_C_NORMAL', 1: 'BMS_CELL_VOLT_DIFF51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_cell_volt_diff51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmscellvoltdiff51c();

  // config detail: {'bit': 38, 'description': '电池温度过高', 'enum': {0: 'BMS_TEMP_H51_C_NORMAL', 1: 'BMS_TEMP_H51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_h51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstemph51c();

  // config detail: {'bit': 39, 'description': '电池温度过低', 'enum': {0: 'BMS_TEMP_L51_C_NORMAL', 1: 'BMS_TEMP_L51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_l51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstempl51c();

  // config detail: {'bit': 40, 'description': '温差过大', 'enum': {0: 'BMS_TEMP_DIFF51_C_NORMAL', 1: 'BMS_TEMP_DIFF51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_diff51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstempdiff51c();

  // config detail: {'bit': 41, 'description': '回馈过流', 'enum': {0: 'BMS_WAR_CHG_OVERCURRENT51_C_NORMAL', 1: 'BMS_WAR_CHG_OVERCURRENT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_chg_overcurrent51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmswarchgovercurrent51c();

  // config detail: {'bit': 42, 'description': 'SOC过高', 'enum': {0: 'BMS_SOC_H51_C_NORMAL', 1: 'BMS_SOC_H51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_h51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmssoch51c();

  // config detail: {'bit': 43, 'description': 'SOC过低', 'enum': {0: 'BMS_SOC_L51_C_NORMAL', 1: 'BMS_SOC_L51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_l51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmssocl51c();

  // config detail: {'bit': 44, 'description': '充电加热超时', 'enum': {0: 'BMS_TIME_OF_HEATING_TOO_LONG51_C_NORMAL', 1: 'BMS_TIME_OF_HEATING_TOO_LONG51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_time_of_heating_too_long51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstimeofheatingtoolong51c();

  // config detail: {'bit': 45, 'description': 'SOC跳变', 'enum': {0: 'BMS_SOC_BREAK51_C_NORMAL', 1: 'BMS_SOC_BREAK51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_break51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmssocbreak51c();

  // config detail: {'bit': 46, 'description': '放电过流', 'enum': {0: 'BMS_DIS_CHAR_OVER_CUR51_C_NORMAL', 1: 'BMS_DIS_CHAR_OVER_CUR51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_dis_char_over_cur51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsdischarovercur51c();

  // config detail: {'bit': 47, 'description': '慢充充电过流', 'enum': {0: 'BMS_CHAR_OVER_CUR_SLOW51_C_NORMAL', 1: 'BMS_CHAR_OVER_CUR_SLOW51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_char_over_cur_slow51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmscharovercurslow51c();

  // config detail: {'bit': 48, 'description': '快充充电过流', 'enum': {0: 'BMS_FAST_CHAR_OVER_CUR51_C_NORMAL', 1: 'BMS_FAST_CHAR_OVER_CUR51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_fast_char_over_cur51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsfastcharovercur51c();

  // config detail: {'bit': 49, 'description': '单体电压采集故障', 'enum': {0: 'BMS_ALM_SENSE_CELL51_C_NORMAL', 1: 'BMS_ALM_SENSE_CELL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_cell51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsalmsensecell51c();

  // config detail: {'bit': 50, 'description': '温度采集故障', 'enum': {0: 'BMS_ALM_SENSE_TEMP51_C_NORMAL', 1: 'BMS_ALM_SENSE_TEMP51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_temp51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsalmsensetemp51c();

  // config detail: {'bit': 51, 'description': '电流传感器故障', 'enum': {0: 'BMS_ALM_SENSE_CURR51_C_NORMAL', 1: 'BMS_ALM_SENSE_CURR51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_curr51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsalmsensecurr51c();

  // config detail: {'bit': 52, 'description': '高压互锁故障', 'enum': {0: 'BMS_HVIL51_C_NORMAL', 1: 'BMS_HVIL51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_hvil51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmshvil51c();

  // config detail: {'bit': 53, 'description': '内网通信', 'enum': {0: 'BMS_WAR_IN_CAN_FAULT51_C_NORMAL', 1: 'BMS_WAR_IN_CAN_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_in_can_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmswarincanfault51c();

  // config detail: {'bit': 54, 'description': '充电机通信中断', 'enum': {0: 'BMS_LST_COM_WITH_OBC51_C_NORMAL', 1: 'BMS_LST_COM_WITH_OBC51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_obc51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmslstcomwithobc51c();

  // config detail: {'bit': 55, 'description': '整车通信中断', 'enum': {0: 'BMS_LST_COM_WITH_VCU51_C_NORMAL', 1: 'BMS_LST_COM_WITH_VCU51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_vcu51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmslstcomwithvcu51c();

  // config detail: {'bit': 56, 'description': '预充失败', 'enum': {0: 'BMS_PRECHARGER_FAULT51_C_NORMAL', 1: 'BMS_PRECHARGER_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_precharger_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsprechargerfault51c();

  // config detail: {'bit': 57, 'description': '总正继电器黏连', 'enum': {0: 'BMS_POS_RELAY_CONGLUTINATION51_C_NORMAL', 1: 'BMS_POS_RELAY_CONGLUTINATION51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_pos_relay_conglutination51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsposrelayconglutination51c();

  // config detail: {'bit': 58, 'description': '总负继电器黏连', 'enum': {0: 'BMS_NEG_RELAY_CONGLUTINATION51_C_NORMAL', 1: 'BMS_NEG_RELAY_CONGLUTINATION51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_neg_relay_conglutination51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsnegrelayconglutination51c();

  // config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE351_C_NORMAL', 1: 'SPARE351_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare351_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare351c();

  // config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE451_C_NORMAL', 1: 'SPARE451_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare451_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare451c();

  // config detail: {'bit': 61, 'description': 'DCDC系统过温故障', 'enum': {0: 'DCDC_HIGH_TEM_ALARM51_C_NORMAL', 1: 'DCDC_HIGH_TEM_ALARM51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_high_tem_alarm51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcdchightemalarm51c();

  // config detail: {'bit': 62, 'description': 'DCDC系统硬件故障', 'enum': {0: 'DCDC_HARDWARE_FAULT51_C_NORMAL', 1: 'DCDC_HARDWARE_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_hardware_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcdchardwarefault51c();

  // config detail: {'bit': 63, 'description': 'DCDC系统网络故障', 'enum': {0: 'DCDC_NETWORK_FAULT51_C_NORMAL', 1: 'DCDC_NETWORK_FAULT51_C_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_network_fault51_c', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcdcnetworkfault51c();
};



