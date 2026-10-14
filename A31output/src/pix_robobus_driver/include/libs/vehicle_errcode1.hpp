#pragma once

#include <libs/Byte.hpp>

class VehicleErrcode1 {
public:
  static const uint32_t ID = 0x51A;
  VehicleErrcode1();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int flmc_hardware_fault_;
  int flmc_tem_fault_;
  int flm_tem_fault_;
  int rlmc_hardware_fault_;
  int rlmc_tem_fault_;
  int rlm_tem_fault_;
  int frmc_hardware_fault_;
  int frmc_tem_fault_;
  int frm_tem_fault_;
  int rrmc_hardware_fault_;
  int rrmc_tem_fault_;
  int rrm_tem_fault_;
  int flmc_network_fault_;
  int frmc_network_fault_;
  int rlmc_network_fault_;
  int rrmc_network_fault_;
  int fr_steer_hardware_fault_;
  int rr_steer_hardware_fault_;
  int fr_steer_network_fault_;
  int rr_steer_network_fault_;
  int brake_hardware_fault_;
  int brake_high_tem_fault_;
  int brake_luid_level_low_;
  int brake_network_fault_;
  int park_hardware_fault_;
  int park_network_fault_;
  int rcu_network_fault_;
  int rcu_weak_signal_;
  int rcu_elec_low_alarm_;
  int spare1_;
  int spare2_;
  int bms_network_fault_;
  int bms_insulation_fault_;
  int bms_ocv_cell_;
  int bms_odv_cell_;
  int bms_ocv_batt_;
  int bms_odv_batt_;
  int bms_cell_volt_diff_;
  int bms_temp_h_;
  int bms_temp_l_;
  int bms_temp_diff_;
  int bms_war_chg_overcurrent_;
  int bms_soc_h_;
  int bms_soc_l_;
  int bms_time_of_heating_too_long_;
  int bms_soc_break_;
  int bms_dis_char_over_cur_;
  int bms_char_over_cur_slow_;
  int bms_fast_char_over_cur_;
  int bms_alm_sense_cell_;
  int bms_alm_sense_temp_;
  int bms_alm_sense_curr_;
  int bms_hvil_;
  int bms_war_in_can_fault_;
  int bms_lst_com_with_obc_;
  int bms_lst_com_with_vcu_;
  int bms_precharger_fault_;
  int bms_pos_relay_conglutination_;
  int bms_neg_relay_conglutination_;
  int spare3_;
  int spare4_;
  int dcdc_high_tem_alarm_;
  int dcdc_hardware_fault_;
  int dcdc_network_fault_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '前左电控硬件故障', 'enum': {0: 'FLMC_HARDWARE_FAULT_NORMAL', 1: 'FLMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmchardwarefault();

  // config detail: {'bit': 1, 'description': '前左电控温度故障', 'enum': {0: 'FLMC_TEM_FAULT_NORMAL', 1: 'FLMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmctemfault();

  // config detail: {'bit': 2, 'description': '前左电机温度故障', 'enum': {0: 'FLM_TEM_FAULT_NORMAL', 1: 'FLM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmtemfault();

  // config detail: {'bit': 3, 'description': '后左电控硬件故障', 'enum': {0: 'RLMC_HARDWARE_FAULT_NORMAL', 1: 'RLMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmchardwarefault();

  // config detail: {'bit': 4, 'description': '后左电控温度故障', 'enum': {0: 'RLMC_TEM_FAULT_NORMAL', 1: 'RLMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmctemfault();

  // config detail: {'bit': 5, 'description': '后左电机温度故障', 'enum': {0: 'RLM_TEM_FAULT_NORMAL', 1: 'RLM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmtemfault();

  // config detail: {'bit': 6, 'description': '前右电控硬件故障', 'enum': {0: 'FRMC_HARDWARE_FAULT_NORMAL', 1: 'FRMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmchardwarefault();

  // config detail: {'bit': 7, 'description': '前右电控温度故障', 'enum': {0: 'FRMC_TEM_FAULT_NORMAL', 1: 'FRMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmctemfault();

  // config detail: {'bit': 8, 'description': '前右电机温度故障', 'enum': {0: 'FRM_TEM_FAULT_NORMAL', 1: 'FRM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmtemfault();

  // config detail: {'bit': 9, 'description': '后右电控硬件故障', 'enum': {0: 'RRMC_HARDWARE_FAULT_NORMAL', 1: 'RRMC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmchardwarefault();

  // config detail: {'bit': 10, 'description': '后右电控温度故障', 'enum': {0: 'RRMC_TEM_FAULT_NORMAL', 1: 'RRMC_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmctemfault();

  // config detail: {'bit': 11, 'description': '后右电机温度故障', 'enum': {0: 'RRM_TEM_FAULT_NORMAL', 1: 'RRM_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrm_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmtemfault();

  // config detail: {'bit': 12, 'description': '前左电控网络故障', 'enum': {0: 'FLMC_NETWORK_FAULT_NORMAL', 1: 'FLMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'flmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int flmcnetworkfault();

  // config detail: {'bit': 13, 'description': '前右电控网络故障', 'enum': {0: 'FRMC_NETWORK_FAULT_NORMAL', 1: 'FRMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'frmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frmcnetworkfault();

  // config detail: {'bit': 14, 'description': '后左电控网络故障', 'enum': {0: 'RLMC_NETWORK_FAULT_NORMAL', 1: 'RLMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rlmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rlmcnetworkfault();

  // config detail: {'bit': 15, 'description': '后右电控网络故障', 'enum': {0: 'RRMC_NETWORK_FAULT_NORMAL', 1: 'RRMC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rrmc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrmcnetworkfault();

  // config detail: {'bit': 16, 'description': '前电子转向硬件故障', 'enum': {0: 'FR_STEER_HARDWARE_FAULT_NORMAL', 1: 'FR_STEER_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frsteerhardwarefault();

  // config detail: {'bit': 17, 'description': '后电子转向硬件故障', 'enum': {0: 'RR_STEER_HARDWARE_FAULT_NORMAL', 1: 'RR_STEER_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrsteerhardwarefault();

  // config detail: {'bit': 18, 'description': '前电子转向网络故障', 'enum': {0: 'FR_STEER_NETWORK_FAULT_NORMAL', 1: 'FR_STEER_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'fr_steer_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int frsteernetworkfault();

  // config detail: {'bit': 19, 'description': '后电子转向网络故障', 'enum': {0: 'RR_STEER_NETWORK_FAULT_NORMAL', 1: 'RR_STEER_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rr_steer_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rrsteernetworkfault();

  // config detail: {'bit': 20, 'description': '电制动系统硬件故障', 'enum': {0: 'BRAKE_HARDWARE_FAULT_NORMAL', 1: 'BRAKE_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakehardwarefault();

  // config detail: {'bit': 21, 'description': '电制动系统高温故障', 'enum': {0: 'BRAKE_HIGH_TEM_FAULT_NORMAL', 1: 'BRAKE_HIGH_TEM_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_high_tem_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakehightemfault();

  // config detail: {'bit': 22, 'description': '制动液位过低', 'enum': {0: 'BRAKE_LUID_LEVEL_LOW_NORMAL', 1: 'BRAKE_LUID_LEVEL_LOW_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_luid_level_low', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakeluidlevellow();

  // config detail: {'bit': 23, 'description': '电制动系统网络故障', 'enum': {0: 'BRAKE_NETWORK_FAULT_NORMAL', 1: 'BRAKE_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'brake_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int brakenetworkfault();

  // config detail: {'bit': 24, 'description': '驻车冗余系统硬件故障', 'enum': {0: 'PARK_HARDWARE_FAULT_NORMAL', 1: 'PARK_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int parkhardwarefault();

  // config detail: {'bit': 25, 'description': '驻车冗余系统网络故障', 'enum': {0: 'PARK_NETWORK_FAULT_NORMAL', 1: 'PARK_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'park_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int parknetworkfault();

  // config detail: {'bit': 26, 'description': '无线遥控器系统网络故障', 'enum': {0: 'RCU_NETWORK_FAULT_NORMAL', 1: 'RCU_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rcunetworkfault();

  // config detail: {'bit': 27, 'description': '无线遥控器系统信号强度弱', 'enum': {0: 'RCU_WEAK_SIGNAL_NORMAL', 1: 'RCU_WEAK_SIGNAL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_weak_signal', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rcuweaksignal();

  // config detail: {'bit': 28, 'description': '无线遥控电池电量报警', 'enum': {0: 'RCU_ELEC_LOW_ALARM_NORMAL', 1: 'RCU_ELEC_LOW_ALARM_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'rcu_elec_low_alarm', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int rcueleclowalarm();

  // config detail: {'bit': 29, 'description': '预留', 'enum': {0: 'SPARE1_NORMAL', 1: 'SPARE1_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1();

  // config detail: {'bit': 30, 'description': '预留', 'enum': {0: 'SPARE2_NORMAL', 1: 'SPARE2_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2();

  // config detail: {'bit': 31, 'description': 'BMS系统网络故障', 'enum': {0: 'BMS_NETWORK_FAULT_NORMAL', 1: 'BMS_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsnetworkfault();

  // config detail: {'bit': 32, 'description': '绝缘报警', 'enum': {0: 'BMS_INSULATION_FAULT_NORMAL', 1: 'BMS_INSULATION_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_insulation_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsinsulationfault();

  // config detail: {'bit': 33, 'description': '单体电压过压', 'enum': {0: 'BMS_OCV_CELL_NORMAL', 1: 'BMS_OCV_CELL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_cell', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsocvcell();

  // config detail: {'bit': 34, 'description': '单体电压欠压', 'enum': {0: 'BMS_ODV_CELL_NORMAL', 1: 'BMS_ODV_CELL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_cell', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsodvcell();

  // config detail: {'bit': 35, 'description': '总压过高', 'enum': {0: 'BMS_OCV_BATT_NORMAL', 1: 'BMS_OCV_BATT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_ocv_batt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsocvbatt();

  // config detail: {'bit': 36, 'description': '总压过低', 'enum': {0: 'BMS_ODV_BATT_NORMAL', 1: 'BMS_ODV_BATT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_odv_batt', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsodvbatt();

  // config detail: {'bit': 37, 'description': '压差过大', 'enum': {0: 'BMS_CELL_VOLT_DIFF_NORMAL', 1: 'BMS_CELL_VOLT_DIFF_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_cell_volt_diff', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmscellvoltdiff();

  // config detail: {'bit': 38, 'description': '电池温度过高', 'enum': {0: 'BMS_TEMP_H_NORMAL', 1: 'BMS_TEMP_H_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_h', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstemph();

  // config detail: {'bit': 39, 'description': '电池温度过低', 'enum': {0: 'BMS_TEMP_L_NORMAL', 1: 'BMS_TEMP_L_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_l', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstempl();

  // config detail: {'bit': 40, 'description': '温差过大', 'enum': {0: 'BMS_TEMP_DIFF_NORMAL', 1: 'BMS_TEMP_DIFF_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_temp_diff', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstempdiff();

  // config detail: {'bit': 41, 'description': '回馈过流', 'enum': {0: 'BMS_WAR_CHG_OVERCURRENT_NORMAL', 1: 'BMS_WAR_CHG_OVERCURRENT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_chg_overcurrent', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmswarchgovercurrent();

  // config detail: {'bit': 42, 'description': 'SOC过高', 'enum': {0: 'BMS_SOC_H_NORMAL', 1: 'BMS_SOC_H_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_h', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmssoch();

  // config detail: {'bit': 43, 'description': 'SOC过低', 'enum': {0: 'BMS_SOC_L_NORMAL', 1: 'BMS_SOC_L_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_l', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmssocl();

  // config detail: {'bit': 44, 'description': '充电加热超时', 'enum': {0: 'BMS_TIME_OF_HEATING_TOO_LONG_NORMAL', 1: 'BMS_TIME_OF_HEATING_TOO_LONG_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_time_of_heating_too_long', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmstimeofheatingtoolong();

  // config detail: {'bit': 45, 'description': 'SOC跳变', 'enum': {0: 'BMS_SOC_BREAK_NORMAL', 1: 'BMS_SOC_BREAK_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_soc_break', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmssocbreak();

  // config detail: {'bit': 46, 'description': '放电过流', 'enum': {0: 'BMS_DIS_CHAR_OVER_CUR_NORMAL', 1: 'BMS_DIS_CHAR_OVER_CUR_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_dis_char_over_cur', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsdischarovercur();

  // config detail: {'bit': 47, 'description': '慢充充电过流', 'enum': {0: 'BMS_CHAR_OVER_CUR_SLOW_NORMAL', 1: 'BMS_CHAR_OVER_CUR_SLOW_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_char_over_cur_slow', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmscharovercurslow();

  // config detail: {'bit': 48, 'description': '快充充电过流', 'enum': {0: 'BMS_FAST_CHAR_OVER_CUR_NORMAL', 1: 'BMS_FAST_CHAR_OVER_CUR_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_fast_char_over_cur', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsfastcharovercur();

  // config detail: {'bit': 49, 'description': '单体电压采集故障', 'enum': {0: 'BMS_ALM_SENSE_CELL_NORMAL', 1: 'BMS_ALM_SENSE_CELL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_cell', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsalmsensecell();

  // config detail: {'bit': 50, 'description': '温度采集故障', 'enum': {0: 'BMS_ALM_SENSE_TEMP_NORMAL', 1: 'BMS_ALM_SENSE_TEMP_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_temp', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsalmsensetemp();

  // config detail: {'bit': 51, 'description': '电流传感器故障', 'enum': {0: 'BMS_ALM_SENSE_CURR_NORMAL', 1: 'BMS_ALM_SENSE_CURR_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_alm_sense_curr', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsalmsensecurr();

  // config detail: {'bit': 52, 'description': '高压互锁故障', 'enum': {0: 'BMS_HVIL_NORMAL', 1: 'BMS_HVIL_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_hvil', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmshvil();

  // config detail: {'bit': 53, 'description': '内网通信', 'enum': {0: 'BMS_WAR_IN_CAN_FAULT_NORMAL', 1: 'BMS_WAR_IN_CAN_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_war_in_can_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmswarincanfault();

  // config detail: {'bit': 54, 'description': '充电机通信中断', 'enum': {0: 'BMS_LST_COM_WITH_OBC_NORMAL', 1: 'BMS_LST_COM_WITH_OBC_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_obc', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmslstcomwithobc();

  // config detail: {'bit': 55, 'description': '整车通信中断', 'enum': {0: 'BMS_LST_COM_WITH_VCU_NORMAL', 1: 'BMS_LST_COM_WITH_VCU_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_lst_com_with_vcu', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmslstcomwithvcu();

  // config detail: {'bit': 56, 'description': '预充失败', 'enum': {0: 'BMS_PRECHARGER_FAULT_NORMAL', 1: 'BMS_PRECHARGER_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_precharger_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsprechargerfault();

  // config detail: {'bit': 57, 'description': '总正继电器黏连', 'enum': {0: 'BMS_POS_RELAY_CONGLUTINATION_NORMAL', 1: 'BMS_POS_RELAY_CONGLUTINATION_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_pos_relay_conglutination', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsposrelayconglutination();

  // config detail: {'bit': 58, 'description': '总负继电器黏连', 'enum': {0: 'BMS_NEG_RELAY_CONGLUTINATION_NORMAL', 1: 'BMS_NEG_RELAY_CONGLUTINATION_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bms_neg_relay_conglutination', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bmsnegrelayconglutination();

  // config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE3_NORMAL', 1: 'SPARE3_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3();

  // config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE4_NORMAL', 1: 'SPARE4_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4();

  // config detail: {'bit': 61, 'description': 'DCDC系统过温故障', 'enum': {0: 'DCDC_HIGH_TEM_ALARM_NORMAL', 1: 'DCDC_HIGH_TEM_ALARM_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_high_tem_alarm', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcdchightemalarm();

  // config detail: {'bit': 62, 'description': 'DCDC系统硬件故障', 'enum': {0: 'DCDC_HARDWARE_FAULT_NORMAL', 1: 'DCDC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcdchardwarefault();

  // config detail: {'bit': 63, 'description': 'DCDC系统网络故障', 'enum': {0: 'DCDC_NETWORK_FAULT_NORMAL', 1: 'DCDC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcdc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcdcnetworkfault();
};



