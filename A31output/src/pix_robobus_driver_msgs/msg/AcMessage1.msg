std_msgs/Header header 
# 除霜状态反馈 [] [0|255]
int8 defrost_fdk 
# 空调开关状态 [] [0|255]
int8 air_cod_sta 
# 空调风量状态 [] [0|255]
int8 air_cod_gear_sta 
# 通风模式状态 [] [0|255]
int8 air_cod_mod_sta 
# 空调温度设定状态 [℃] [16|32]
int32 air_cod_temp_sta 
# 内外循环模式状态 [] [0|255]
int8 in_loop_mod_sta 
# 预留 [] [0|255]
int32 reserve 
