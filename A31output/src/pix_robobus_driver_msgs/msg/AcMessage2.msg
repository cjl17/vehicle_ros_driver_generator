std_msgs/Header header 
# 预留 [V] [0|65535]
float32 reserve 
# 蒸发风扇温度 [℃] [-40|255]
int32 fan_temp 
# 车外温度 [℃] [-40|255]
int32 ac_out_temp 
# 车内温度 [℃] [-40|255]
int32 ac_in_temp 
# 空调硬件版本 [] [0|255]
int32 ac_hardware 
# 空调软件版本 [] [0|255]
int32 ac_software 
