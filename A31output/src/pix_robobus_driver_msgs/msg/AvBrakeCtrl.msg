std_msgs/Header header 
# 车辆刹车控制使能 [] [0|1]
int8 acu_chassis_brake_en 
# 车辆刹车灯控制 [] [0|1]
int8 acu_chassis_brake_lamp_ctrl 
# AEB使能（预留，自动驾驶实现） [] [0|1]
int8 acu_chassis_aeb_ctrl 
# 车辆刹车控制 [%] [0|100]
float32 acu_chassis_brake_pdl_target 
# 驻车控制（触发型控制） [] [0|2]
int8 acu_chassis_epb_ctrl 
# 循环计数0~15 [] [0|15]
int32 acu_brake_life_sig 
# 校验sum=byte0 xor byte1 xor...byte6 [] [0|255]
int32 acu_check_sum131 
