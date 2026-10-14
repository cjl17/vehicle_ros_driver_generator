std_msgs/Header header 
# AEB功能状态 [] [0|2]
int8 acu_aeb_work_sta 
# AEB制动请求状态 [] [0|1]
int8 acu_aeb_active_request 
# FCW前向碰撞预警 [] [0|1]
int8 acu_fcw_active_request 
# AEB制动控制使能 [] [0|1]
int8 acu_aeb_brake_en 
# 制动踏板请求 [%] [0|100]
int32 acu_aeb_brake_pedal_target 
# 循环计数0~15 [] [0|15]
int32 acu_aeb_brake_life_sig 
# 校验sum=byte0 xor byte1 xor...byte6 [] [0|255]
int32 acu_check_sum121 
