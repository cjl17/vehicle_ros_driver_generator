#include <libs/ac_message1.hpp>


AcMessage1::AcMessage1() {}

void AcMessage1::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void AcMessage1::Parse() {
  defrost_fdk_ = defrostfdk();
  air_cod_sta_ = aircodsta();
  air_cod_gear_sta_ = aircodgearsta();
  air_cod_mod_sta_ = aircodmodsta();
  air_cod_temp_sta_ = aircodtempsta();
  in_loop_mod_sta_ = inloopmodsta();
  reserve_ = reserve();
}


// config detail: {'bit': 0, 'description': '除霜状态反馈', 'enum': {0: 'DEFROST_FDK_OFF_关闭', 1: 'DEFROST_FDK_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'defrost_fdk', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int AcMessage1::defrostfdk() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '空调开关状态', 'enum': {0: 'AIR_COD_STA_OFF_关闭', 1: 'AIR_COD_STA_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int AcMessage1::aircodsta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '空调风量状态', 'enum': {0: 'AIR_COD_GEAR_STA_OFF_关闭', 1: 'AIR_COD_GEAR_STA_GEAR1_1档', 2: 'AIR_COD_GEAR_STA_GEAR2_2档', 3: 'AIR_COD_GEAR_STA_GEAR3_3档', 4: 'AIR_COD_GEAR_STA_GEAR4_4档', 5: 'AIR_COD_GEAR_STA_GEAR5_5档', 6: 'AIR_COD_GEAR_STA_GEAR6_6档', 7: 'AIR_COD_GEAR_STA_GEAR7_7档', 8: 'AIR_COD_GEAR_STA_GEAR8_8档'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_gear_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int AcMessage1::aircodgearsta() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '通风模式状态', 'enum': {0: 'AIR_COD_MOD_STA_OFF_关闭', 1: 'AIR_COD_MOD_STA_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_mod_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int AcMessage1::aircodmodsta() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '空调温度设定状态', 'is_signed_var': False, 'len': 8, 'name': 'air_cod_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[16|32]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int AcMessage1::aircodtempsta() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'description': '内外循环模式状态', 'enum': {0: 'IN_LOOP_MOD_STA_INVALID', 1: 'IN_LOOP_MOD_STA_RECIRCULATION_内循环', 2: 'IN_LOOP_MOD_STA_FRESHAIR_外循环'}, 'is_signed_var': False, 'len': 8, 'name': 'in_loop_mod_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int AcMessage1::inloopmodsta() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 56, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AcMessage1::reserve() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

