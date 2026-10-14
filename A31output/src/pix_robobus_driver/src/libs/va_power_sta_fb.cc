#include <libs/va_power_sta_fb.hpp>


VaPowerStaFb::VaPowerStaFb() {}

void VaPowerStaFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaPowerStaFb::Parse() {
  vcu_chassis_bms_reserved1_ = vcuchassisbmsreserved1();
  vcu_chassis_power_charge_sta_ = vcuchassispowerchargesta();
  vcu_chassis_power_charge_sock_sta_ = vcuchassispowerchargesocksta();
  vcu_chassis_power_soc_fb_ = vcuchassispowersocfb();
  vcu_chassis_power_volt_fb_ = vcuchassispowervoltfb();
  vcu_chassis_power_curr_fb_ = vcuchassispowercurrfb();
  vcu_chassis_bms_max_temp_ = vcuchassisbmsmaxtemp();
  vcu_chassis_bms_reserved2_ = vcuchassisbmsreserved2();
}


// config detail: {'bit': 0, 'description': '预留', 'is_signed_var': False, 'len': 4, 'name': 'vcu_chassis_bms_reserved1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaPowerStaFb::vcuchassisbmsreserved1() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 4, 'description': '车辆充电状态', 'enum': {0: 'VCU_CHASSIS_POWER_CHARGE_STA_NOCHARGE', 1: 'VCU_CHASSIS_POWER_CHARGE_STA_CHARGE', 2: 'VCU_CHASSIS_POWER_CHARGE_STA_CHARGEFULL'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_power_charge_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaPowerStaFb::vcuchassispowerchargesta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 6, 'description': '充电枪连接状态', 'enum': {0: 'VCU_CHASSIS_POWER_CHARGE_SOCK_STA_CHARGEGUNNOTCONNECT', 1: 'VCU_CHASSIS_POWER_CHARGE_SOCK_STA_CHARGEGUNISCONNECT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_power_charge_sock_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaPowerStaFb::vcuchassispowerchargesocksta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '车辆动力电池电量', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_power_soc_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 1.0, 'type': 'int'}
int VaPowerStaFb::vcuchassispowersocfb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 16, 'description': '车辆动力电池电压', 'is_signed_var': False, 'len': 16, 'name': 'vcu_chassis_power_volt_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
double VaPowerStaFb::vcuchassispowervoltfb() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 32, 'description': '车辆动力电池电流', 'is_signed_var': False, 'len': 16, 'name': 'vcu_chassis_power_curr_fb', 'offset': -1000.0, 'order': 'intel', 'physical_range': '[-1000|1000]', 'physical_unit': 'A', 'precision': 0.1, 'type': 'double'}
double VaPowerStaFb::vcuchassispowercurrfb() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000 + -1000.000000;
  return ret;
}

// config detail: {'bit': 48, 'description': 'BMS最高单体温度', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_bms_max_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|80]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int VaPowerStaFb::vcuchassisbmsmaxtemp() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 56, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_bms_reserved2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaPowerStaFb::vcuchassisbmsreserved2() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

