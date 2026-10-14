std_msgs/Header header 
# 位置灯控制 [] [0|1]
int8 acu_vehicle_pos_lamp_ctrl 
# 近光灯控制 [] [0|1]
int8 acu_vehicle_head_lamp_ctrl 
# 左转向灯控制 [] [0|1]
int8 acu_vehicle_left_lamp_ctrl 
# 右转向灯控制 [] [0|1]
int8 acu_vehicle_right_lamp_ctrl 
# 远光灯控制 [] [0|1]
int8 acu_vehicle_high_beam_ctrl 
# 雾灯控制 [] [0|1]
int8 acu_vehicle_fog_lamp_ctrl 
# 氛围灯控制 [] [0|1]
int8 acu_vehicle_body_light_ctrl 
# 车内灯光总控制 [] [0|1]
int8 acu_vehicle_read_light_ctrl 
# 提示音控制 [] [0|3]
int8 acu_vehicle_voice 
# 雨刮控制 [] [0|3]
int8 acu_vehicle_wipers_ctrl 
# 车门控制(触发型) [] [0|2]
int8 acu_vehicle_door_ctrl 
# 车窗控制（预留） [] [0|2]
int8 acu_vehicle_window_ctrl 
# 限速控制 [] [0|1]
int8 acu_chassis_speed_limite_mode 
# 电喇叭控制 (VCU限制单次开启时间不超过3秒,防止喇叭一直鸣叫) [] [0|1]
int8 acu_vehicle_horn_ctrl 
# 雨刮喷淋控制 (VCU限制单次喷淋时间不超过5秒) [] [0|1]
int8 acu_vehicle_spray_ctrl 
# 速度限制值 [m/s] [1|20]
float32 acu_chassis_speed_limite_val 
# 校验模式使能 (发1：disable可关闭校验，目前只校验0x130~132的life信号) [] [0|1]
int8 acu_check_sum_en 
