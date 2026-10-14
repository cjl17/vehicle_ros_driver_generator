std_msgs/Header header 
# 位置灯状态反馈 [] [0|1]
int8 vcu_vehicle_pos_lamp_fb 
# 近光灯状态反馈 [] [0|1]
int8 vcu_vehicle_head_lamp_fb 
# 左转向灯状态反馈 [] [0|1]
int8 vcu_vehicle_left_lamp_fb 
# 右转向灯状态反馈 [] [0|1]
int8 vcu_vehicle_right_lamp_fb 
# 远光灯状态反馈 [] [0|1]
int8 vcu_vehicle_high_beam_fb 
# 雾灯状态反馈 [] [0|1]
int8 vcu_vehicle_fog_lamp_fb 
# 危险警示灯开关状态 [] [0|1]
int8 vcu_vehicle_hazard_war_lamp_fb 
# 车外氛围灯状态反馈 [] [0|1]
int8 vcu_vehicle_body_lamp_fb 
# 车内灯光状态反馈 [] [0|1]
int8 vcu_vehicle_read_lamp_fb 
# 喇叭开启状态反馈 [] [0|1]
int8 vcu_vehicle_horn_st_fb 
# 车内车窗状态反馈（预留） [] [0|6]
int8 acu_vehicle_window_fb 
# 请求车辆开门的信号来源 [] [0|3]
int8 acu_vehicle_door_req_sig_fb 
# 车门状态反馈 [] [0|6]
int8 vcu_vehicle_door_sta_fb 
# 雨刮状态反馈(预留) [] [0|3]
int8 vcu_vehicle_wipers_sta_fb 
# 安全带状态1反馈 [] [0|3]
int8 vcu_vehicle_safety_belt1 
# 安全带状态2反馈 [] [0|3]
int8 vcu_vehicle_safety_belt2 
# 安全带状态3反馈 [] [0|3]
int8 vcu_vehicle_safety_belt3 
# 安全带状态4反馈 [] [0|3]
int8 vcu_vehicle_safety_belt4 
# 安全带状态5反馈 [] [0|3]
int8 vcu_vehicle_safety_belt5 
# 安全带状态6反馈 [] [0|3]
int8 vcu_vehicle_safety_belt6 
# VCU反馈的提醒信号(预留) [] [0|65535]
int32 vcu_vehicle_reserve_warning 
# 自动驾驶仪表显示的车速 [Km/h] [0|240]
int32 vcu_vehicle_display_speed 
