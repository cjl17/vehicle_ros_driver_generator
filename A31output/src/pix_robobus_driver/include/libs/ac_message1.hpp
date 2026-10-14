#pragma once

#include <libs/Byte.hpp>

class AcMessage1 {
public:
  static const uint32_t ID = 0x2F8;
  AcMessage1();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int defrost_fdk_;
  int air_cod_sta_;
  int air_cod_gear_sta_;
  int air_cod_mod_sta_;
  int air_cod_temp_sta_;
  int in_loop_mod_sta_;
  int reserve_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '除霜状态反馈', 'enum': {0: 'DEFROST_FDK_OFF_关闭', 1: 'DEFROST_FDK_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'defrost_fdk', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int defrostfdk();

  // config detail: {'bit': 8, 'description': '空调开关状态', 'enum': {0: 'AIR_COD_STA_OFF_关闭', 1: 'AIR_COD_STA_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int aircodsta();

  // config detail: {'bit': 16, 'description': '空调风量状态', 'enum': {0: 'AIR_COD_GEAR_STA_OFF_关闭', 1: 'AIR_COD_GEAR_STA_GEAR1_1档', 2: 'AIR_COD_GEAR_STA_GEAR2_2档', 3: 'AIR_COD_GEAR_STA_GEAR3_3档', 4: 'AIR_COD_GEAR_STA_GEAR4_4档', 5: 'AIR_COD_GEAR_STA_GEAR5_5档', 6: 'AIR_COD_GEAR_STA_GEAR6_6档', 7: 'AIR_COD_GEAR_STA_GEAR7_7档', 8: 'AIR_COD_GEAR_STA_GEAR8_8档'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_gear_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int aircodgearsta();

  // config detail: {'bit': 24, 'description': '通风模式状态', 'enum': {0: 'AIR_COD_MOD_STA_OFF_关闭', 1: 'AIR_COD_MOD_STA_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_mod_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int aircodmodsta();

  // config detail: {'bit': 32, 'description': '空调温度设定状态', 'is_signed_var': False, 'len': 8, 'name': 'air_cod_temp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[16|32]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int aircodtempsta();

  // config detail: {'bit': 48, 'description': '内外循环模式状态', 'enum': {0: 'IN_LOOP_MOD_STA_INVALID', 1: 'IN_LOOP_MOD_STA_RECIRCULATION_内循环', 2: 'IN_LOOP_MOD_STA_FRESHAIR_外循环'}, 'is_signed_var': False, 'len': 8, 'name': 'in_loop_mod_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int inloopmodsta();

  // config detail: {'bit': 56, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int reserve();
};



