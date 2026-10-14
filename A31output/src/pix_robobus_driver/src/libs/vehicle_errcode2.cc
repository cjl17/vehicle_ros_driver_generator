#include <libs/vehicle_errcode2.hpp>


VehicleErrcode2::VehicleErrcode2() {}

void VehicleErrcode2::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VehicleErrcode2::Parse() {
  obc_network_fault_ = obcnetworkfault();
  obc_hardware_fault_ = obchardwarefault();
  spare5_ = spare5();
  spare6_ = spare6();
  spare7_ = spare7();
  spare8_ = spare8();
  dp_hardware_fault_ = dphardwarefault();
  dp_network_fault_ = dpnetworkfault();
  spare9_ = spare9();
  spare10_ = spare10();
  spare11_ = spare11();
  spare12_ = spare12();
  spare13_ = spare13();
  spare14_ = spare14();
  bcm_hardware_fault_ = bcmhardwarefault();
  bcm_network_fault_ = bcmnetworkfault();
  spare15_ = spare15();
  spare16_ = spare16();
  spare17_ = spare17();
  spare18_ = spare18();
  spare19_ = spare19();
  spare20_ = spare20();
  dcu_network_fault_ = dcunetworkfault();
  dcu_hardware_fault_ = dcuhardwarefault();
  spare21_ = spare21();
  avas_network_fault_ = avasnetworkfault();
  avas_hardware_fault_ = avashardwarefault();
  spare22_ = spare22();
  spare23_ = spare23();
  iis_hardware_fault_ = iishardwarefault();
  iis_network_fault_ = iisnetworkfault();
  spare24_ = spare24();
  spare25_ = spare25();
  spare26_ = spare26();
  spare27_ = spare27();
  spare28_ = spare28();
  spare29_ = spare29();
  spare30_ = spare30();
  ac_hardware_fault_ = achardwarefault();
  ac_network_fault_ = acnetworkfault();
  spare31_ = spare31();
  spare32_ = spare32();
  spare33_ = spare33();
  spare34_ = spare34();
  spare35_ = spare35();
  spare36_ = spare36();
  lv_battery_low_voltage_fault_ = lvbatterylowvoltagefault();
  lv_battery_high_voltage_fault_ = lvbatteryhighvoltagefault();
  spare37_ = spare37();
  spare38_ = spare38();
  spare39_ = spare39();
  spare40_ = spare40();
  spare41_ = spare41();
  spare42_ = spare42();
  spare43_ = spare43();
  spare44_ = spare44();
  spare45_ = spare45();
  spare46_ = spare46();
  spare47_ = spare47();
  spare48_ = spare48();
  spare49_ = spare49();
  spare50_ = spare50();
  spare51_ = spare51();
  spare52_ = spare52();
}


// config detail: {'bit': 0, 'description': 'OBC网络故障', 'enum': {0: 'OBC_NETWORK_FAULT_NORMAL', 1: 'OBC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::obcnetworkfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': 'OBC硬件故障', 'enum': {0: 'OBC_HARDWARE_FAULT_NORMAL', 1: 'OBC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'obc_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::obchardwarefault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '预留', 'enum': {0: 'SPARE5_NORMAL', 1: 'SPARE5_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare5() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 3, 'description': '预留', 'enum': {0: 'SPARE6_NORMAL', 1: 'SPARE6_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare6() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '预留', 'enum': {0: 'SPARE7_NORMAL', 1: 'SPARE7_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare7', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare7() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 5, 'description': '预留', 'enum': {0: 'SPARE8_NORMAL', 1: 'SPARE8_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare8', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare8() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': '数字电源硬件故障', 'enum': {0: 'DP_HARDWARE_FAULT_NORMAL', 1: 'DP_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::dphardwarefault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '数字电源网络故障', 'enum': {0: 'DP_NETWORK_FAULT_NORMAL', 1: 'DP_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dp_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::dpnetworkfault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '预留', 'enum': {0: 'SPARE9_NORMAL', 1: 'SPARE9_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare9', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare9() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': '预留', 'enum': {0: 'SPARE10_NORMAL', 1: 'SPARE10_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare10', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare10() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': '预留', 'enum': {0: 'SPARE11_NORMAL', 1: 'SPARE11_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare11', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare11() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 11, 'description': '预留', 'enum': {0: 'SPARE12_NORMAL', 1: 'SPARE12_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare12', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare12() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 12, 'description': '预留', 'enum': {0: 'SPARE13_NORMAL', 1: 'SPARE13_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare13', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare13() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 13, 'description': '预留', 'enum': {0: 'SPARE14_NORMAL', 1: 'SPARE14_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare14', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare14() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 14, 'description': 'BCM系统硬件故障', 'enum': {0: 'BCM_HARDWARE_FAULT_NORMAL', 1: 'BCM_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::bcmhardwarefault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': 'BCM系统网络故障', 'enum': {0: 'BCM_NETWORK_FAULT_NORMAL', 1: 'BCM_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'bcm_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::bcmnetworkfault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '预留', 'enum': {0: 'SPARE15_NORMAL', 1: 'SPARE15_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare15', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare15() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 17, 'description': '预留', 'enum': {0: 'SPARE16_NORMAL', 1: 'SPARE16_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare16', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare16() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 18, 'description': '预留', 'enum': {0: 'SPARE17_NORMAL', 1: 'SPARE17_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare17', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare17() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 19, 'description': '预留', 'enum': {0: 'SPARE18_NORMAL', 1: 'SPARE18_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare18', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare18() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': '预留', 'enum': {0: 'SPARE19_NORMAL', 1: 'SPARE19_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare19', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare19() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 21, 'description': '预留', 'enum': {0: 'SPARE20_NORMAL', 1: 'SPARE20_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare20', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare20() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 22, 'description': '门控系统网络故障', 'enum': {0: 'DCU_NETWORK_FAULT_NORMAL', 1: 'DCU_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::dcunetworkfault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 23, 'description': '门控系统硬件故障', 'enum': {0: 'DCU_HARDWARE_FAULT_NORMAL', 1: 'DCU_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'dcu_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::dcuhardwarefault() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '预留', 'enum': {0: 'SPARE21_NORMAL', 1: 'SPARE21_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare21', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare21() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 25, 'description': '低速提示器网络故障', 'enum': {0: 'AVAS_NETWORK_FAULT_NORMAL', 1: 'AVAS_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::avasnetworkfault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': '低速提示器硬件故障', 'enum': {0: 'AVAS_HARDWARE_FAULT_NORMAL', 1: 'AVAS_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'avas_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::avashardwarefault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 27, 'description': '预留', 'enum': {0: 'SPARE22_NORMAL', 1: 'SPARE22_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare22', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare22() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '预留', 'enum': {0: 'SPARE23_NORMAL', 1: 'SPARE23_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare23', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare23() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 29, 'description': '交互屏系统硬件故障', 'enum': {0: 'IIS_HARDWARE_FAULT_NORMAL', 1: 'IIS_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::iishardwarefault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '交互屏系统网络故障', 'enum': {0: 'IIS_NETWORK_FAULT_NORMAL', 1: 'IIS_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'iis_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::iisnetworkfault() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 31, 'description': '预留', 'enum': {0: 'SPARE24_NORMAL', 1: 'SPARE24_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare24', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare24() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '预留', 'enum': {0: 'SPARE25_NORMAL', 1: 'SPARE25_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare25', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare25() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 33, 'description': '预留', 'enum': {0: 'SPARE26_NORMAL', 1: 'SPARE26_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare26', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare26() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': '预留', 'enum': {0: 'SPARE27_NORMAL', 1: 'SPARE27_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare27', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare27() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 35, 'description': '预留', 'enum': {0: 'SPARE28_NORMAL', 1: 'SPARE28_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare28', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare28() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 36, 'description': '预留', 'enum': {0: 'SPARE29_NORMAL', 1: 'SPARE29_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare29', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare29() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 37, 'description': '预留', 'enum': {0: 'SPARE30_NORMAL', 1: 'SPARE30_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare30', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare30() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 38, 'description': '空调系统硬件故障', 'enum': {0: 'AC_HARDWARE_FAULT_NORMAL', 1: 'AC_HARDWARE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_hardware_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::achardwarefault() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 39, 'description': '空调系统网络故障', 'enum': {0: 'AC_NETWORK_FAULT_NORMAL', 1: 'AC_NETWORK_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'ac_network_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::acnetworkfault() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '预留', 'enum': {0: 'SPARE31_NORMAL', 1: 'SPARE31_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare31', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare31() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 41, 'description': '预留', 'enum': {0: 'SPARE32_NORMAL', 1: 'SPARE32_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare32', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare32() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 42, 'description': '预留', 'enum': {0: 'SPARE33_NORMAL', 1: 'SPARE33_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare33', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare33() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 43, 'description': '预留', 'enum': {0: 'SPARE34_NORMAL', 1: 'SPARE34_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare34', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare34() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': '预留', 'enum': {0: 'SPARE35_NORMAL', 1: 'SPARE35_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare35', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare35() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 45, 'description': '预留', 'enum': {0: 'SPARE36_NORMAL', 1: 'SPARE36_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare36', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare36() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 46, 'description': '12V供电过低', 'enum': {0: 'LV_BATTERY_LOW_VOLTAGE_FAULT_NORMAL', 1: 'LV_BATTERY_LOW_VOLTAGE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_low_voltage_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::lvbatterylowvoltagefault() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 47, 'description': '12V供电过高', 'enum': {0: 'LV_BATTERY_HIGH_VOLTAGE_FAULT_NORMAL', 1: 'LV_BATTERY_HIGH_VOLTAGE_FAULT_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'lv_battery_high_voltage_fault', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::lvbatteryhighvoltagefault() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': '预留', 'enum': {0: 'SPARE37_NORMAL', 1: 'SPARE37_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare37', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare37() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 49, 'description': '预留', 'enum': {0: 'SPARE38_NORMAL', 1: 'SPARE38_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare38', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare38() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 50, 'description': '预留', 'enum': {0: 'SPARE39_NORMAL', 1: 'SPARE39_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare39', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare39() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 51, 'description': '预留', 'enum': {0: 'SPARE40_NORMAL', 1: 'SPARE40_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare40', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare40() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 52, 'description': '预留', 'enum': {0: 'SPARE41_NORMAL', 1: 'SPARE41_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare41', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare41() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 53, 'description': '预留', 'enum': {0: 'SPARE42_NORMAL', 1: 'SPARE42_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare42', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare42() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 54, 'description': '预留', 'enum': {0: 'SPARE43_NORMAL', 1: 'SPARE43_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare43', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare43() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 55, 'description': '预留', 'enum': {0: 'SPARE44_NORMAL', 1: 'SPARE44_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare44', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare44() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '预留', 'enum': {0: 'SPARE45_NORMAL', 1: 'SPARE45_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare45', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare45() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 57, 'description': '预留', 'enum': {0: 'SPARE46_NORMAL', 1: 'SPARE46_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare46', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare46() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 58, 'description': '预留', 'enum': {0: 'SPARE47_NORMAL', 1: 'SPARE47_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare47', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare47() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 59, 'description': '预留', 'enum': {0: 'SPARE48_NORMAL', 1: 'SPARE48_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare48', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare48() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 60, 'description': '预留', 'enum': {0: 'SPARE49_NORMAL', 1: 'SPARE49_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare49', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare49() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 61, 'description': '预留', 'enum': {0: 'SPARE50_NORMAL', 1: 'SPARE50_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare50', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare50() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 62, 'description': '预留', 'enum': {0: 'SPARE51_NORMAL', 1: 'SPARE51_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare51', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare51() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 63, 'description': '预留', 'enum': {0: 'SPARE52_NORMAL', 1: 'SPARE52_ABNORMAL'}, 'is_signed_var': False, 'len': 1, 'name': 'spare52', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VehicleErrcode2::spare52() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

