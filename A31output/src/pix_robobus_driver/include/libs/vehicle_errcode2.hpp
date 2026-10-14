#pragma once

#include <libs/Byte.hpp>

class VehicleErrcode2 {
public:
  static const uint32_t ID = 0x51B;
  VehicleErrcode2();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int obc_network_fault_;
  int obc_hardware_fault_;
  int spare5_;
  int spare6_;
  int spare7_;
  int spare8_;
  int dp_hardware_fault_;
  int dp_network_fault_;
  int spare9_;
  int spare10_;
  int spare11_;
  int spare12_;
  int spare13_;
  int spare14_;
  int bcm_hardware_fault_;
  int bcm_network_fault_;
  int spare15_;
  int spare16_;
  int spare17_;
  int spare18_;
  int spare19_;
  int spare20_;
  int dcu_network_fault_;
  int dcu_hardware_fault_;
  int spare21_;
  int avas_network_fault_;
  int avas_hardware_fault_;
  int spare22_;
  int spare23_;
  int iis_hardware_fault_;
  int iis_network_fault_;
  int spare24_;
  int spare25_;
  int spare26_;
  int spare27_;
  int spare28_;
  int spare29_;
  int spare30_;
  int ac_hardware_fault_;
  int ac_network_fault_;
  int spare31_;
  int spare32_;
  int spare33_;
  int spare34_;
  int spare35_;
  int spare36_;
  int lv_battery_low_voltage_fault_;
  int lv_battery_high_voltage_fault_;
  int spare37_;
  int spare38_;
  int spare39_;
  int spare40_;
  int spare41_;
  int spare42_;
  int spare43_;
  int spare44_;
  int spare45_;
  int spare46_;
  int spare47_;
  int spare48_;
  int spare49_;
  int spare50_;
  int spare51_;
  int spare52_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': 'OBC网络故障', 'enum': {0: 'OBC_NETWORK_FAULT_NORMAL', 1: 'OBC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int obcnetworkfault();

  // config detail: {'bit': 1, 'description': 'OBC硬件故障', 'enum': {0: 'OBC_HARDWARE_FAULT_NORMAL', 1: 'OBC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int obchardwarefault();

  // config detail: {'bit': 2, 'description': '预留', 'enum': {0: 'SPARE5_NORMAL', 1: 'SPARE5_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare5();

  // config detail: {'bit': 3, 'description': '预留', 'enum': {0: 'SPARE6_NORMAL', 1: 'SPARE6_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare6();

  // config detail: {'bit': 4, 'description': '预留', 'enum': {0: 'SPARE7_NORMAL', 1: 'SPARE7_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare7', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare7();

  // config detail: {'bit': 5, 'description': '预留', 'enum': {0: 'SPARE8_NORMAL', 1: 'SPARE8_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare8', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare8();

  // config detail: {'bit': 6, 'description': '数字电源硬件故障', 'enum': {0: 'DP_HARDWARE_FAULT_NORMAL', 1: 'DP_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dphardwarefault();

  // config detail: {'bit': 7, 'description': '数字电源网络故障', 'enum': {0: 'DP_NETWORK_FAULT_NORMAL', 1: 'DP_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dpnetworkfault();

  // config detail: {'bit': 8, 'description': '预留', 'enum': {0: 'SPARE9_NORMAL', 1: 'SPARE9_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare9', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare9();

  // config detail: {'bit': 9, 'description': '预留', 'enum': {0: 'SPARE10_NORMAL', 1: 'SPARE10_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare10', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare10();

  // config detail: {'bit': 10, 'description': '预留', 'enum': {0: 'SPARE11_NORMAL', 1: 'SPARE11_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare11', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare11();

  // config detail: {'bit': 11, 'description': '预留', 'enum': {0: 'SPARE12_NORMAL', 1: 'SPARE12_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare12', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare12();

  // config detail: {'bit': 12, 'description': '预留', 'enum': {0: 'SPARE13_NORMAL', 1: 'SPARE13_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare13', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare13();

  // config detail: {'bit': 13, 'description': '预留', 'enum': {0: 'SPARE14_NORMAL', 1: 'SPARE14_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare14', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare14();

  // config detail: {'bit': 14, 'description': 'BCM系统硬件故障', 'enum': {0: 'BCM_HARDWARE_FAULT_NORMAL', 1: 'BCM_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bcmhardwarefault();

  // config detail: {'bit': 15, 'description': 'BCM系统网络故障', 'enum': {0: 'BCM_NETWORK_FAULT_NORMAL', 1: 'BCM_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bcmnetworkfault();

  // config detail: {'bit': 16, 'description': '预留', 'enum': {0: 'SPARE15_NORMAL', 1: 'SPARE15_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare15', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare15();

  // config detail: {'bit': 17, 'description': '预留', 'enum': {0: 'SPARE16_NORMAL', 1: 'SPARE16_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare16', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare16();

  // config detail: {'bit': 18, 'description': '预留', 'enum': {0: 'SPARE17_NORMAL', 1: 'SPARE17_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare17', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare17();

  // config detail: {'bit': 19, 'description': '预留', 'enum': {0: 'SPARE18_NORMAL', 1: 'SPARE18_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare18', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare18();

  // config detail: {'bit': 20, 'description': '预留', 'enum': {0: 'SPARE19_NORMAL', 1: 'SPARE19_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare19', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare19();

  // config detail: {'bit': 21, 'description': '预留', 'enum': {0: 'SPARE20_NORMAL', 1: 'SPARE20_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare20', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare20();

  // config detail: {'bit': 22, 'description': '门控系统网络故障', 'enum': {0: 'DCU_NETWORK_FAULT_NORMAL', 1: 'DCU_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcunetworkfault();

  // config detail: {'bit': 23, 'description': '门控系统硬件故障', 'enum': {0: 'DCU_HARDWARE_FAULT_NORMAL', 1: 'DCU_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcuhardwarefault();

  // config detail: {'bit': 24, 'description': '预留', 'enum': {0: 'SPARE21_NORMAL', 1: 'SPARE21_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare21', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare21();

  // config detail: {'bit': 25, 'description': '低速提示器网络故障', 'enum': {0: 'AVAS_NETWORK_FAULT_NORMAL', 1: 'AVAS_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int avasnetworkfault();

  // config detail: {'bit': 26, 'description': '低速提示器硬件故障', 'enum': {0: 'AVAS_HARDWARE_FAULT_NORMAL', 1: 'AVAS_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int avashardwarefault();

  // config detail: {'bit': 27, 'description': '预留', 'enum': {0: 'SPARE22_NORMAL', 1: 'SPARE22_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare22', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare22();

  // config detail: {'bit': 28, 'description': '预留', 'enum': {0: 'SPARE23_NORMAL', 1: 'SPARE23_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare23', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare23();

  // config detail: {'bit': 29, 'description': '交互屏系统硬件故障', 'enum': {0: 'IIS_HARDWARE_FAULT_NORMAL', 1: 'IIS_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int iishardwarefault();

  // config detail: {'bit': 30, 'description': '交互屏系统网络故障', 'enum': {0: 'IIS_NETWORK_FAULT_NORMAL', 1: 'IIS_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int iisnetworkfault();

  // config detail: {'bit': 31, 'description': '预留', 'enum': {0: 'SPARE24_NORMAL', 1: 'SPARE24_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare24', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare24();

  // config detail: {'bit': 32, 'description': '预留', 'enum': {0: 'SPARE25_NORMAL', 1: 'SPARE25_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare25', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare25();

  // config detail: {'bit': 33, 'description': '预留', 'enum': {0: 'SPARE26_NORMAL', 1: 'SPARE26_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare26', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare26();

  // config detail: {'bit': 34, 'description': '预留', 'enum': {0: 'SPARE27_NORMAL', 1: 'SPARE27_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare27', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare27();

  // config detail: {'bit': 35, 'description': '预留', 'enum': {0: 'SPARE28_NORMAL', 1: 'SPARE28_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare28', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare28();

  // config detail: {'bit': 36, 'description': '预留', 'enum': {0: 'SPARE29_NORMAL', 1: 'SPARE29_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare29', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare29();

  // config detail: {'bit': 37, 'description': '预留', 'enum': {0: 'SPARE30_NORMAL', 1: 'SPARE30_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare30', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare30();

  // config detail: {'bit': 38, 'description': '空调系统硬件故障', 'enum': {0: 'AC_HARDWARE_FAULT_NORMAL', 1: 'AC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int achardwarefault();

  // config detail: {'bit': 39, 'description': '空调系统网络故障', 'enum': {0: 'AC_NETWORK_FAULT_NORMAL', 1: 'AC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int acnetworkfault();

  // config detail: {'bit': 40, 'description': '预留', 'enum': {0: 'SPARE31_NORMAL', 1: 'SPARE31_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare31', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare31();

  // config detail: {'bit': 41, 'description': '预留', 'enum': {0: 'SPARE32_NORMAL', 1: 'SPARE32_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare32', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare32();

  // config detail: {'bit': 42, 'description': '预留', 'enum': {0: 'SPARE33_NORMAL', 1: 'SPARE33_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare33', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare33();

  // config detail: {'bit': 43, 'description': '预留', 'enum': {0: 'SPARE34_NORMAL', 1: 'SPARE34_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare34', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare34();

  // config detail: {'bit': 44, 'description': '预留', 'enum': {0: 'SPARE35_NORMAL', 1: 'SPARE35_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare35', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare35();

  // config detail: {'bit': 45, 'description': '预留', 'enum': {0: 'SPARE36_NORMAL', 1: 'SPARE36_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare36', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare36();

  // config detail: {'bit': 46, 'description': '12V供电过低', 'enum': {0: 'LV_BATTERY_LOW_VOLTAGE_FAULT_NORMAL', 1: 'LV_BATTERY_LOW_VOLTAGE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_low_voltage_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int lvbatterylowvoltagefault();

  // config detail: {'bit': 47, 'description': '12V供电过高', 'enum': {0: 'LV_BATTERY_HIGH_VOLTAGE_FAULT_NORMAL', 1: 'LV_BATTERY_HIGH_VOLTAGE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_high_voltage_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int lvbatteryhighvoltagefault();

  // config detail: {'bit': 48, 'description': '预留', 'enum': {0: 'SPARE37_NORMAL', 1: 'SPARE37_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare37', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare37();

  // config detail: {'bit': 49, 'description': '预留', 'enum': {0: 'SPARE38_NORMAL', 1: 'SPARE38_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare38', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare38();

  // config detail: {'bit': 50, 'description': '预留', 'enum': {0: 'SPARE39_NORMAL', 1: 'SPARE39_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare39', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare39();

  // config detail: {'bit': 51, 'description': '预留', 'enum': {0: 'SPARE40_NORMAL', 1: 'SPARE40_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare40', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare40();

  // config detail: {'bit': 52, 'description': '预留', 'enum': {0: 'SPARE41_NORMAL', 1: 'SPARE41_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare41', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare41();

  // config detail: {'bit': 53, 'description': '预留', 'enum': {0: 'SPARE42_NORMAL', 1: 'SPARE42_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare42', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare42();

  // config detail: {'bit': 54, 'description': '预留', 'enum': {0: 'SPARE43_NORMAL', 1: 'SPARE43_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare43', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare43();

  // config detail: {'bit': 55, 'description': '预留', 'enum': {0: 'SPARE44_NORMAL', 1: 'SPARE44_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare44', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare44();

  // config detail: {'bit': 56, 'description': '预留', 'enum': {0: 'SPARE45_NORMAL', 1: 'SPARE45_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare45', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare45();

  // config detail: {'bit': 57, 'description': '预留', 'enum': {0: 'SPARE46_NORMAL', 1: 'SPARE46_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare46', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare46();

  // config detail: {'bit': 58, 'description': '预留', 'enum': {0: 'SPARE47_NORMAL', 1: 'SPARE47_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare47', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare47();

  // config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE48_NORMAL', 1: 'SPARE48_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare48', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare48();

  // config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE49_NORMAL', 1: 'SPARE49_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare49', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare49();

  // config detail: {'bit': 61, 'description': '预留', 'enum': {0: 'SPARE50_NORMAL', 1: 'SPARE50_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare50', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare50();

  // config detail: {'bit': 62, 'description': '预留', 'enum': {0: 'SPARE51_NORMAL', 1: 'SPARE51_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare51', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare51();

  // config detail: {'bit': 63, 'description': '预留', 'enum': {0: 'SPARE52_NORMAL', 1: 'SPARE52_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare52', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare52();
};



