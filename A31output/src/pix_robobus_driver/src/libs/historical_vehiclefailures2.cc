#include <libs/historical_vehiclefailures2.hpp>


HistoricalVehiclefailures2::HistoricalVehiclefailures2() {}

void HistoricalVehiclefailures2::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void HistoricalVehiclefailures2::Parse() {
  obc_network_fault51_d_ = obcnetworkfault51d();
  obc_hardware_fault51_d_ = obchardwarefault51d();
  spare551_d_ = spare551d();
  spare651_d_ = spare651d();
  spare751_d_ = spare751d();
  spare851_d_ = spare851d();
  dp_hardware_fault51_d_ = dphardwarefault51d();
  dp_network_fault51_d_ = dpnetworkfault51d();
  spare951_d_ = spare951d();
  spare1051_d_ = spare1051d();
  spare1151_d_ = spare1151d();
  spare1251_d_ = spare1251d();
  spare1351_d_ = spare1351d();
  spare1451_d_ = spare1451d();
  bcm_hardware_fault51_d_ = bcmhardwarefault51d();
  bcm_network_fault51_d_ = bcmnetworkfault51d();
  spare1551_d_ = spare1551d();
  spare1651_d_ = spare1651d();
  spare1751_d_ = spare1751d();
  spare1851_d_ = spare1851d();
  spare1951_d_ = spare1951d();
  spare2051_d_ = spare2051d();
  dcu_network_fault51_d_ = dcunetworkfault51d();
  dcu_hardware_fault51_d_ = dcuhardwarefault51d();
  spare2151_d_ = spare2151d();
  avas_network_fault51_d_ = avasnetworkfault51d();
  avas_hardware_fault51_d_ = avashardwarefault51d();
  spare2251_d_ = spare2251d();
  spare2351_d_ = spare2351d();
  iis_hardware_fault51_d_ = iishardwarefault51d();
  iis_network_fault51_d_ = iisnetworkfault51d();
  spare2451_d_ = spare2451d();
  spare2551_d_ = spare2551d();
  spare2651_d_ = spare2651d();
  spare2751_d_ = spare2751d();
  spare2851_d_ = spare2851d();
  spare2951_d_ = spare2951d();
  spare3051_d_ = spare3051d();
  ac_hardware_fault51_d_ = achardwarefault51d();
  ac_network_fault51_d_ = acnetworkfault51d();
  spare3151_d_ = spare3151d();
  spare3251_d_ = spare3251d();
  spare3351_d_ = spare3351d();
  spare3451_d_ = spare3451d();
  spare3551_d_ = spare3551d();
  spare3651_d_ = spare3651d();
  lv_battery_low_voltage_fault51_d_ = lvbatterylowvoltagefault51d();
  lv_battery_high_voltage_fault51_d_ = lvbatteryhighvoltagefault51d();
  spare3751_d_ = spare3751d();
  spare3851_d_ = spare3851d();
  spare3951_d_ = spare3951d();
  spare4051_d_ = spare4051d();
  spare4151_d_ = spare4151d();
  spare4251_d_ = spare4251d();
  spare4351_d_ = spare4351d();
  spare4451_d_ = spare4451d();
  spare4551_d_ = spare4551d();
  spare4651_d_ = spare4651d();
  spare4751_d_ = spare4751d();
  spare4851_d_ = spare4851d();
  spare4951_d_ = spare4951d();
  spare5051_d_ = spare5051d();
  spare5151_d_ = spare5151d();
  spare5251_d_ = spare5251d();
}


// config detail: {'bit': 0, 'description': 'OBC网络故障', 'enum': {0: 'OBC_NETWORK_FAULT51_D_NORMAL', 1: 'OBC_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::obcnetworkfault51d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': 'OBC硬件故障', 'enum': {0: 'OBC_HARDWARE_FAULT51_D_NORMAL', 1: 'OBC_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::obchardwarefault51d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '预留', 'enum': {0: 'SPARE551_D_NORMAL', 1: 'SPARE551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare551d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': '预留', 'enum': {0: 'SPARE651_D_NORMAL', 1: 'SPARE651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare651d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '预留', 'enum': {0: 'SPARE751_D_NORMAL', 1: 'SPARE751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare751d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 5, 'description': '预留', 'enum': {0: 'SPARE851_D_NORMAL', 1: 'SPARE851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare851d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': '数字电源硬件故障', 'enum': {0: 'DP_HARDWARE_FAULT51_D_NORMAL', 1: 'DP_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::dphardwarefault51d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '数字电源网络故障', 'enum': {0: 'DP_NETWORK_FAULT51_D_NORMAL', 1: 'DP_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::dpnetworkfault51d() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '预留', 'enum': {0: 'SPARE951_D_NORMAL', 1: 'SPARE951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare951d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': '预留', 'enum': {0: 'SPARE1051_D_NORMAL', 1: 'SPARE1051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1051d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': '预留', 'enum': {0: 'SPARE1151_D_NORMAL', 1: 'SPARE1151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1151d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 11, 'description': '预留', 'enum': {0: 'SPARE1251_D_NORMAL', 1: 'SPARE1251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1251d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': '预留', 'enum': {0: 'SPARE1351_D_NORMAL', 1: 'SPARE1351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1351d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 13, 'description': '预留', 'enum': {0: 'SPARE1451_D_NORMAL', 1: 'SPARE1451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1451d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': 'BCM系统硬件故障', 'enum': {0: 'BCM_HARDWARE_FAULT51_D_NORMAL', 1: 'BCM_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::bcmhardwarefault51d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': 'BCM系统网络故障', 'enum': {0: 'BCM_NETWORK_FAULT51_D_NORMAL', 1: 'BCM_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::bcmnetworkfault51d() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '预留', 'enum': {0: 'SPARE1551_D_NORMAL', 1: 'SPARE1551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1551d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 17, 'description': '预留', 'enum': {0: 'SPARE1651_D_NORMAL', 1: 'SPARE1651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1651d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': '预留', 'enum': {0: 'SPARE1751_D_NORMAL', 1: 'SPARE1751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1751d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 19, 'description': '预留', 'enum': {0: 'SPARE1851_D_NORMAL', 1: 'SPARE1851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1851d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': '预留', 'enum': {0: 'SPARE1951_D_NORMAL', 1: 'SPARE1951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare1951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare1951d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 21, 'description': '预留', 'enum': {0: 'SPARE2051_D_NORMAL', 1: 'SPARE2051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2051d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 22, 'description': '门控系统网络故障', 'enum': {0: 'DCU_NETWORK_FAULT51_D_NORMAL', 1: 'DCU_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::dcunetworkfault51d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 23, 'description': '门控系统硬件故障', 'enum': {0: 'DCU_HARDWARE_FAULT51_D_NORMAL', 1: 'DCU_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::dcuhardwarefault51d() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '预留', 'enum': {0: 'SPARE2151_D_NORMAL', 1: 'SPARE2151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2151d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 25, 'description': '低速提示器网络故障', 'enum': {0: 'AVAS_NETWORK_FAULT51_D_NORMAL', 1: 'AVAS_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::avasnetworkfault51d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': '低速提示器硬件故障', 'enum': {0: 'AVAS_HARDWARE_FAULT51_D_NORMAL', 1: 'AVAS_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::avashardwarefault51d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 27, 'description': '预留', 'enum': {0: 'SPARE2251_D_NORMAL', 1: 'SPARE2251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2251d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '预留', 'enum': {0: 'SPARE2351_D_NORMAL', 1: 'SPARE2351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2351d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 29, 'description': '交互屏系统硬件故障', 'enum': {0: 'IIS_HARDWARE_FAULT51_D_NORMAL', 1: 'IIS_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::iishardwarefault51d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '交互屏系统网络故障', 'enum': {0: 'IIS_NETWORK_FAULT51_D_NORMAL', 1: 'IIS_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::iisnetworkfault51d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 31, 'description': '预留', 'enum': {0: 'SPARE2451_D_NORMAL', 1: 'SPARE2451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2451d() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '预留', 'enum': {0: 'SPARE2551_D_NORMAL', 1: 'SPARE2551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2551d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 33, 'description': '预留', 'enum': {0: 'SPARE2651_D_NORMAL', 1: 'SPARE2651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2651d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': '预留', 'enum': {0: 'SPARE2751_D_NORMAL', 1: 'SPARE2751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2751d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 35, 'description': '预留', 'enum': {0: 'SPARE2851_D_NORMAL', 1: 'SPARE2851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2851d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': '预留', 'enum': {0: 'SPARE2951_D_NORMAL', 1: 'SPARE2951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare2951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare2951d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 37, 'description': '预留', 'enum': {0: 'SPARE3051_D_NORMAL', 1: 'SPARE3051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3051d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 38, 'description': '空调系统硬件故障', 'enum': {0: 'AC_HARDWARE_FAULT51_D_NORMAL', 1: 'AC_HARDWARE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_hardware_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::achardwarefault51d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 39, 'description': '空调系统网络故障', 'enum': {0: 'AC_NETWORK_FAULT51_D_NORMAL', 1: 'AC_NETWORK_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_network_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::acnetworkfault51d() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '预留', 'enum': {0: 'SPARE3151_D_NORMAL', 1: 'SPARE3151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3151d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 41, 'description': '预留', 'enum': {0: 'SPARE3251_D_NORMAL', 1: 'SPARE3251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3251d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': '预留', 'enum': {0: 'SPARE3351_D_NORMAL', 1: 'SPARE3351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3351d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 43, 'description': '预留', 'enum': {0: 'SPARE3451_D_NORMAL', 1: 'SPARE3451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3451d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': '预留', 'enum': {0: 'SPARE3551_D_NORMAL', 1: 'SPARE3551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3551d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 45, 'description': '预留', 'enum': {0: 'SPARE3651_D_NORMAL', 1: 'SPARE3651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3651d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 46, 'description': '12V供电过低', 'enum': {0: 'LV_BATTERY_LOW_VOLTAGE_FAULT51_D_NORMAL', 1: 'LV_BATTERY_LOW_VOLTAGE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_low_voltage_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::lvbatterylowvoltagefault51d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 47, 'description': '12V供电过高', 'enum': {0: 'LV_BATTERY_HIGH_VOLTAGE_FAULT51_D_NORMAL', 1: 'LV_BATTERY_HIGH_VOLTAGE_FAULT51_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_high_voltage_fault51_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::lvbatteryhighvoltagefault51d() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': '预留', 'enum': {0: 'SPARE3751_D_NORMAL', 1: 'SPARE3751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3751d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 49, 'description': '预留', 'enum': {0: 'SPARE3851_D_NORMAL', 1: 'SPARE3851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3851d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 50, 'description': '预留', 'enum': {0: 'SPARE3951_D_NORMAL', 1: 'SPARE3951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare3951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare3951d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 51, 'description': '预留', 'enum': {0: 'SPARE4051_D_NORMAL', 1: 'SPARE4051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4051d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 52, 'description': '预留', 'enum': {0: 'SPARE4151_D_NORMAL', 1: 'SPARE4151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4151d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 53, 'description': '预留', 'enum': {0: 'SPARE4251_D_NORMAL', 1: 'SPARE4251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4251d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 54, 'description': '预留', 'enum': {0: 'SPARE4351_D_NORMAL', 1: 'SPARE4351_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4351_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4351d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 55, 'description': '预留', 'enum': {0: 'SPARE4451_D_NORMAL', 1: 'SPARE4451_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4451_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4451d() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '预留', 'enum': {0: 'SPARE4551_D_NORMAL', 1: 'SPARE4551_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4551_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4551d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 57, 'description': '预留', 'enum': {0: 'SPARE4651_D_NORMAL', 1: 'SPARE4651_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4651_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4651d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 58, 'description': '预留', 'enum': {0: 'SPARE4751_D_NORMAL', 1: 'SPARE4751_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4751_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4751d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE4851_D_NORMAL', 1: 'SPARE4851_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4851_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4851d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE4951_D_NORMAL', 1: 'SPARE4951_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare4951_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare4951d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 61, 'description': '预留', 'enum': {0: 'SPARE5051_D_NORMAL', 1: 'SPARE5051_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5051_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare5051d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 62, 'description': '预留', 'enum': {0: 'SPARE5151_D_NORMAL', 1: 'SPARE5151_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5151_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare5151d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 63, 'description': '预留', 'enum': {0: 'SPARE5251_D_NORMAL', 1: 'SPARE5251_D_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5251_d', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int HistoricalVehiclefailures2::spare5251d() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

