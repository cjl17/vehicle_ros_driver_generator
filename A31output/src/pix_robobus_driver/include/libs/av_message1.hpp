#pragma once
#include <libs/Byte.hpp>

class AvMessage1 {
public:
	static  int32_t ID;

	AvMessage1();
	void UpdateData(int defrost_ctrl, int air_cod_ctrl, int air_cod_gear_ctrl, int air_cod_mod_ctrl, int air_cod_temp_ctrl, int in_loop_mod_ctrl, int reserve);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '除霜控制', 'enum': {0: 'DEFROST_CTRL_OFF_关闭', 1: 'DEFROST_CTRL_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'defrost_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_defrost_ctrl(int defrost_ctrl);

  // config detail: {'bit': 8, 'description': '空调开关控制', 'enum': {0: 'AIR_COD_CTRL_OFF_关闭', 1: 'AIR_COD_CTRL_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_air_cod_ctrl(int air_cod_ctrl);

  // config detail: {'bit': 16, 'description': '空调风量控制', 'enum': {0: 'AIR_COD_GEAR_CTRL_OFF_关闭', 1: 'AIR_COD_GEAR_CTRL_GEAR1_1档', 2: 'AIR_COD_GEAR_CTRL_GEAR2_2档', 3: 'AIR_COD_GEAR_CTRL_GEAR3_3档', 4: 'AIR_COD_GEAR_CTRL_GEAR4_4档', 5: 'AIR_COD_GEAR_CTRL_GEAR5_5档', 6: 'AIR_COD_GEAR_CTRL_GEAR6_6档', 7: 'AIR_COD_GEAR_CTRL_GEAR7_7档', 8: 'AIR_COD_GEAR_CTRL_GEAR8_8档'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_gear_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_air_cod_gear_ctrl(int air_cod_gear_ctrl);

  // config detail: {'bit': 24, 'description': '自动空调控制', 'enum': {0: 'AIR_COD_MOD_CTRL_OFF_关闭', 1: 'AIR_COD_MOD_CTRL_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_air_cod_mod_ctrl(int air_cod_mod_ctrl);

  // config detail: {'bit': 32, 'description': '空调温度设定', 'is_signed_var': False, 'len': 8, 'name': 'air_cod_temp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[16|32]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  void set_p_air_cod_temp_ctrl(int air_cod_temp_ctrl);

  // config detail: {'bit': 48, 'description': '内外循环模式控制', 'enum': {0: 'IN_LOOP_MOD_CTRL_INVALID', 1: 'IN_LOOP_MOD_CTRL_RECIRCULATION_内循环', 2: 'IN_LOOP_MOD_CTRL_FRESHAIR_外循环'}, 'is_signed_var': False, 'len': 8, 'name': 'in_loop_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_in_loop_mod_ctrl(int in_loop_mod_ctrl);

  // config detail: {'bit': 56, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_reserve(int reserve);

private:
	uint8_t data[8];
};



