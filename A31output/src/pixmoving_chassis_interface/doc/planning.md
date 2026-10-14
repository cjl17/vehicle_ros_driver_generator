1. 订阅 `/planning/planning_evaluator/metrics`，消息类型为 `tier4_metric_msgs/msg/MetricArray`。对应消息定义可在 Autoware 依赖中的 `tier4_metric_msgs` 包查看。
2. 分析 `autoware_planning_evaluator` 包内的 README 和相关说明文档，整理舒适性与轨迹突变指标定义。
3. 基于上述订阅数据，在 `pkg/collectors/pixmoving_chassis_interface` 包内新增处理逻辑，得到舒适性和轨迹突变结果并进行输出验证。
