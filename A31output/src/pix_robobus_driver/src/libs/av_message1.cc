#include <libs/av_message1.hpp>

int32_t AvMessage1::ID = 0x5FA;

// public
AvMessage1::AvMessage1() { Reset(); }

void AvMessage1::UpdateData(int defrost_ctrl, int air_cod_ctrl, int air_cod_gear_ctrl, int air_cod_mod_ctrl, int air_cod_temp_ctrl, int in_loop_mod_ctrl, int reserve) {
  set_p_defrost_ctrl(defrost_ctrl);
  set_p_air_cod_ctrl(air_cod_ctrl);
  set_p_air_cod_gear_ctrl(air_cod_gear_ctrl);
  set_p_air_cod_mod_ctrl(air_cod_mod_ctrl);
  set_p_air_cod_temp_ctrl(air_cod_temp_ctrl);
  set_p_in_loop_mod_ctrl(in_loop_mod_ctrl);
  set_p_reserve(reserve);
}

void AvMessage1::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvMessage1::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '除霜控制', 'enum': {0: 'DEFROST_CTRL_OFF_关闭', 1: 'DEFROST_CTRL_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'defrost_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvMessage1::set_p_defrost_ctrl(int defrost_ctrl) {
  int x = defrost_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '空调开关控制', 'enum': {0: 'AIR_COD_CTRL_OFF_关闭', 1: 'AIR_COD_CTRL_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvMessage1::set_p_air_cod_ctrl(int air_cod_ctrl) {
  int x = air_cod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'description': '空调风量控制', 'enum': {0: 'AIR_COD_GEAR_CTRL_OFF_关闭', 1: 'AIR_COD_GEAR_CTRL_GEAR1_1档', 2: 'AIR_COD_GEAR_CTRL_GEAR2_2档', 3: 'AIR_COD_GEAR_CTRL_GEAR3_3档', 4: 'AIR_COD_GEAR_CTRL_GEAR4_4档', 5: 'AIR_COD_GEAR_CTRL_GEAR5_5档', 6: 'AIR_COD_GEAR_CTRL_GEAR6_6档', 7: 'AIR_COD_GEAR_CTRL_GEAR7_7档', 8: 'AIR_COD_GEAR_CTRL_GEAR8_8档'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_gear_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvMessage1::set_p_air_cod_gear_ctrl(int air_cod_gear_ctrl) {
  int x = air_cod_gear_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 24, 'description': '自动空调控制', 'enum': {0: 'AIR_COD_MOD_CTRL_OFF_关闭', 1: 'AIR_COD_MOD_CTRL_ON_开启'}, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvMessage1::set_p_air_cod_mod_ctrl(int air_cod_mod_ctrl) {
  int x = air_cod_mod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[3] += to_set.return_byte_t();
  
}

// config detail: {'bit': 32, 'description': '空调温度设定', 'is_signed_var': False, 'len': 8, 'name': 'air_cod_temp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[16|32]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
void AvMessage1::set_p_air_cod_temp_ctrl(int air_cod_temp_ctrl) {
  // air_cod_temp_ctrl = ProtocolData::BoundedValue(16, 32, air_cod_temp_ctrl);
  int x = air_cod_temp_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[4] += to_set.return_byte_t();
  
}

// config detail: {'bit': 48, 'description': '内外循环模式控制', 'enum': {0: 'IN_LOOP_MOD_CTRL_INVALID', 1: 'IN_LOOP_MOD_CTRL_RECIRCULATION_内循环', 2: 'IN_LOOP_MOD_CTRL_FRESHAIR_外循环'}, 'is_signed_var': False, 'len': 8, 'name': 'in_loop_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvMessage1::set_p_in_loop_mod_ctrl(int in_loop_mod_ctrl) {
  int x = in_loop_mod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvMessage1::set_p_reserve(int reserve) {
  // reserve = ProtocolData::BoundedValue(0, 255, reserve);
  int x = reserve;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


