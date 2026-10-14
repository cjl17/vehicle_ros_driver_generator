std_msgs/Header header 
# AEB可用时人工驾驶的限速开关 [] [0|1]
int8 acu_aeb_usable_manual_limit 
# AEB不可用时人工驾驶的限速开关 [] [0|1]
int8 acu_aeb_unusable_manual_limit 
# AEB可用时人工驾驶的限速值 [m/s] [0|20]
float32 acu_aeb_usable_manual_spd_set 
# AEB不可用时人工驾驶的限速值 [m/s] [0|10]
float32 acu_aeb_unusable_manual_spd_set 
