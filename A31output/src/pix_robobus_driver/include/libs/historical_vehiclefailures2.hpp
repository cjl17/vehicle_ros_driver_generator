#pragma once

#include <libs/Byte.hpp>

class HistoricalVehiclefailures2 {
public:
  static const uint32_t ID = 0x51D;
  HistoricalVehiclefailures2();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int obc_network_fault51_d_;
  int obc_hardware_fault51_d_;
  int spare551_d_;
  int spare651_d_;
  int spare751_d_;
  int spare851_d_;
  int dp_hardware_fault51_d_;
  int dp_network_fault51_d_;
  int spare951_d_;
  int spare1051_d_;
  int spare1151_d_;
  int spare1251_d_;
  int spare1351_d_;
  int spare1451_d_;
  int bcm_hardware_fault51_d_;
  int bcm_network_fault51_d_;
  int spare1551_d_;
  int spare1651_d_;
  int spare1751_d_;
  int spare1851_d_;
  int spare1951_d_;
  int spare2051_d_;
  int dcu_network_fault51_d_;
  int dcu_hardware_fault51_d_;
  int spare2151_d_;
  int avas_network_fault51_d_;
  int avas_hardware_fault51_d_;
  int spare2251_d_;
  int spare2351_d_;
  int iis_hardware_fault51_d_;
  int iis_network_fault51_d_;
  int spare2451_d_;
  int spare2551_d_;
  int spare2651_d_;
  int spare2751_d_;
  int spare2851_d_;
  int spare2951_d_;
  int spare3051_d_;
  int ac_hardware_fault51_d_;
  int ac_network_fault51_d_;
  int spare3151_d_;
  int spare3251_d_;
  int spare3351_d_;
  int spare3451_d_;
  int spare3551_d_;
  int spare3651_d_;
  int lv_battery_low_voltage_fault51_d_;
  int lv_battery_high_voltage_fault51_d_;
  int spare3751_d_;
  int spare3851_d_;
  int spare3951_d_;
  int spare4051_d_;
  int spare4151_d_;
  int spare4251_d_;
  int spare4351_d_;
  int spare4451_d_;
  int spare4551_d_;
  int spare4651_d_;
  int spare4751_d_;
  int spare4851_d_;
  int spare4951_d_;
  int spare5051_d_;
  int spare5151_d_;
  int spare5251_d_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': 'OBC网络故障', 'enum': {0: 'OBC_NETWORK_FAULT51_D_NORMAL', 1: 'OBC_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int obcnetworkfault51d();

  // config detail: {'bit': 1, 'description': 'OBC硬件故障', 'enum': {0: 'OBC_HARDWARE_FAULT51_D_NORMAL', 1: 'OBC_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int obchardwarefault51d();

  // config detail: {'bit': 2, 'description': '预留', 'enum': {0: 'SPARE551_D_NORMAL', 1: 'SPARE551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare551d();

  // config detail: {'bit': 3, 'description': '预留', 'enum': {0: 'SPARE651_D_NORMAL', 1: 'SPARE651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare651d();

  // config detail: {'bit': 4, 'description': '预留', 'enum': {0: 'SPARE751_D_NORMAL', 1: 'SPARE751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare751d();

  // config detail: {'bit': 5, 'description': '预留', 'enum': {0: 'SPARE851_D_NORMAL', 1: 'SPARE851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare851d();

  // config detail: {'bit': 6, 'description': '数字电源硬件故障', 'enum': {0: 'DP_HARDWARE_FAULT51_D_NORMAL', 1: 'DP_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dphardwarefault51d();

  // config detail: {'bit': 7, 'description': '数字电源网络故障', 'enum': {0: 'DP_NETWORK_FAULT51_D_NORMAL', 1: 'DP_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dpnetworkfault51d();

  // config detail: {'bit': 8, 'description': '预留', 'enum': {0: 'SPARE951_D_NORMAL', 1: 'SPARE951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare951d();

  // config detail: {'bit': 9, 'description': '预留', 'enum': {0: 'SPARE1051_D_NORMAL', 1: 'SPARE1051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1051d();

  // config detail: {'bit': 10, 'description': '预留', 'enum': {0: 'SPARE1151_D_NORMAL', 1: 'SPARE1151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1151d();

  // config detail: {'bit': 11, 'description': '预留', 'enum': {0: 'SPARE1251_D_NORMAL', 1: 'SPARE1251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1251d();

  // config detail: {'bit': 12, 'description': '预留', 'enum': {0: 'SPARE1351_D_NORMAL', 1: 'SPARE1351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1351d();

  // config detail: {'bit': 13, 'description': '预留', 'enum': {0: 'SPARE1451_D_NORMAL', 1: 'SPARE1451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1451d();

  // config detail: {'bit': 14, 'description': 'BCM系统硬件故障', 'enum': {0: 'BCM_HARDWARE_FAULT51_D_NORMAL', 1: 'BCM_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bcmhardwarefault51d();

  // config detail: {'bit': 15, 'description': 'BCM系统网络故障', 'enum': {0: 'BCM_NETWORK_FAULT51_D_NORMAL', 1: 'BCM_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int bcmnetworkfault51d();

  // config detail: {'bit': 16, 'description': '预留', 'enum': {0: 'SPARE1551_D_NORMAL', 1: 'SPARE1551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1551d();

  // config detail: {'bit': 17, 'description': '预留', 'enum': {0: 'SPARE1651_D_NORMAL', 1: 'SPARE1651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1651d();

  // config detail: {'bit': 18, 'description': '预留', 'enum': {0: 'SPARE1751_D_NORMAL', 1: 'SPARE1751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1751d();

  // config detail: {'bit': 19, 'description': '预留', 'enum': {0: 'SPARE1851_D_NORMAL', 1: 'SPARE1851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1851d();

  // config detail: {'bit': 20, 'description': '预留', 'enum': {0: 'SPARE1951_D_NORMAL', 1: 'SPARE1951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare1951d();

  // config detail: {'bit': 21, 'description': '预留', 'enum': {0: 'SPARE2051_D_NORMAL', 1: 'SPARE2051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2051d();

  // config detail: {'bit': 22, 'description': '门控系统网络故障', 'enum': {0: 'DCU_NETWORK_FAULT51_D_NORMAL', 1: 'DCU_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcunetworkfault51d();

  // config detail: {'bit': 23, 'description': '门控系统硬件故障', 'enum': {0: 'DCU_HARDWARE_FAULT51_D_NORMAL', 1: 'DCU_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int dcuhardwarefault51d();

  // config detail: {'bit': 24, 'description': '预留', 'enum': {0: 'SPARE2151_D_NORMAL', 1: 'SPARE2151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2151d();

  // config detail: {'bit': 25, 'description': '低速提示器网络故障', 'enum': {0: 'AVAS_NETWORK_FAULT51_D_NORMAL', 1: 'AVAS_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int avasnetworkfault51d();

  // config detail: {'bit': 26, 'description': '低速提示器硬件故障', 'enum': {0: 'AVAS_HARDWARE_FAULT51_D_NORMAL', 1: 'AVAS_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int avashardwarefault51d();

  // config detail: {'bit': 27, 'description': '预留', 'enum': {0: 'SPARE2251_D_NORMAL', 1: 'SPARE2251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2251d();

  // config detail: {'bit': 28, 'description': '预留', 'enum': {0: 'SPARE2351_D_NORMAL', 1: 'SPARE2351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2351d();

  // config detail: {'bit': 29, 'description': '交互屏系统硬件故障', 'enum': {0: 'IIS_HARDWARE_FAULT51_D_NORMAL', 1: 'IIS_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int iishardwarefault51d();

  // config detail: {'bit': 30, 'description': '交互屏系统网络故障', 'enum': {0: 'IIS_NETWORK_FAULT51_D_NORMAL', 1: 'IIS_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int iisnetworkfault51d();

  // config detail: {'bit': 31, 'description': '预留', 'enum': {0: 'SPARE2451_D_NORMAL', 1: 'SPARE2451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2451d();

  // config detail: {'bit': 32, 'description': '预留', 'enum': {0: 'SPARE2551_D_NORMAL', 1: 'SPARE2551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2551d();

  // config detail: {'bit': 33, 'description': '预留', 'enum': {0: 'SPARE2651_D_NORMAL', 1: 'SPARE2651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2651d();

  // config detail: {'bit': 34, 'description': '预留', 'enum': {0: 'SPARE2751_D_NORMAL', 1: 'SPARE2751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2751d();

  // config detail: {'bit': 35, 'description': '预留', 'enum': {0: 'SPARE2851_D_NORMAL', 1: 'SPARE2851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2851d();

  // config detail: {'bit': 36, 'description': '预留', 'enum': {0: 'SPARE2951_D_NORMAL', 1: 'SPARE2951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare2951d();

  // config detail: {'bit': 37, 'description': '预留', 'enum': {0: 'SPARE3051_D_NORMAL', 1: 'SPARE3051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3051d();

  // config detail: {'bit': 38, 'description': '空调系统硬件故障', 'enum': {0: 'AC_HARDWARE_FAULT51_D_NORMAL', 1: 'AC_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int achardwarefault51d();

  // config detail: {'bit': 39, 'description': '空调系统网络故障', 'enum': {0: 'AC_NETWORK_FAULT51_D_NORMAL', 1: 'AC_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int acnetworkfault51d();

  // config detail: {'bit': 40, 'description': '预留', 'enum': {0: 'SPARE3151_D_NORMAL', 1: 'SPARE3151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3151d();

  // config detail: {'bit': 41, 'description': '预留', 'enum': {0: 'SPARE3251_D_NORMAL', 1: 'SPARE3251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3251d();

  // config detail: {'bit': 42, 'description': '预留', 'enum': {0: 'SPARE3351_D_NORMAL', 1: 'SPARE3351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3351d();

  // config detail: {'bit': 43, 'description': '预留', 'enum': {0: 'SPARE3451_D_NORMAL', 1: 'SPARE3451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3451d();

  // config detail: {'bit': 44, 'description': '预留', 'enum': {0: 'SPARE3551_D_NORMAL', 1: 'SPARE3551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3551d();

  // config detail: {'bit': 45, 'description': '预留', 'enum': {0: 'SPARE3651_D_NORMAL', 1: 'SPARE3651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3651d();

  // config detail: {'bit': 46, 'description': '12V供电过低', 'enum': {0: 'LV_BATTERY_LOW_VOLTAGE_FAULT51_D_NORMAL', 1: 'LV_BATTERY_LOW_VOLTAGE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_low_voltage_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int lvbatterylowvoltagefault51d();

  // config detail: {'bit': 47, 'description': '12V供电过高', 'enum': {0: 'LV_BATTERY_HIGH_VOLTAGE_FAULT51_D_NORMAL', 1: 'LV_BATTERY_HIGH_VOLTAGE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_high_voltage_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int lvbatteryhighvoltagefault51d();

  // config detail: {'bit': 48, 'description': '预留', 'enum': {0: 'SPARE3751_D_NORMAL', 1: 'SPARE3751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3751d();

  // config detail: {'bit': 49, 'description': '预留', 'enum': {0: 'SPARE3851_D_NORMAL', 1: 'SPARE3851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3851d();

  // config detail: {'bit': 50, 'description': '预留', 'enum': {0: 'SPARE3951_D_NORMAL', 1: 'SPARE3951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare3951d();

  // config detail: {'bit': 51, 'description': '预留', 'enum': {0: 'SPARE4051_D_NORMAL', 1: 'SPARE4051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4051d();

  // config detail: {'bit': 52, 'description': '预留', 'enum': {0: 'SPARE4151_D_NORMAL', 1: 'SPARE4151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4151d();

  // config detail: {'bit': 53, 'description': '预留', 'enum': {0: 'SPARE4251_D_NORMAL', 1: 'SPARE4251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4251d();

  // config detail: {'bit': 54, 'description': '预留', 'enum': {0: 'SPARE4351_D_NORMAL', 1: 'SPARE4351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4351d();

  // config detail: {'bit': 55, 'description': '预留', 'enum': {0: 'SPARE4451_D_NORMAL', 1: 'SPARE4451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4451d();

  // config detail: {'bit': 56, 'description': '预留', 'enum': {0: 'SPARE4551_D_NORMAL', 1: 'SPARE4551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4551d();

  // config detail: {'bit': 57, 'description': '预留', 'enum': {0: 'SPARE4651_D_NORMAL', 1: 'SPARE4651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4651d();

  // config detail: {'bit': 58, 'description': '预留', 'enum': {0: 'SPARE4751_D_NORMAL', 1: 'SPARE4751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4751d();

  // config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE4851_D_NORMAL', 1: 'SPARE4851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4851d();

  // config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE4951_D_NORMAL', 1: 'SPARE4951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare4951d();

  // config detail: {'bit': 61, 'description': '预留', 'enum': {0: 'SPARE5051_D_NORMAL', 1: 'SPARE5051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare5051d();

  // config detail: {'bit': 62, 'description': '预留', 'enum': {0: 'SPARE5151_D_NORMAL', 1: 'SPARE5151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare5151d();

  // config detail: {'bit': 63, 'description': '预留', 'enum': {0: 'SPARE5251_D_NORMAL', 1: 'SPARE5251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int spare5251d();
};



