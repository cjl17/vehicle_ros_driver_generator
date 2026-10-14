#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

int main(int argc, char** argv)
{
  // 设置本地化
  setlocale(LC_ALL, "");
  rclcpp::init(argc, argv);

  auto node = std::make_shared<pixmoving::chassis::interface::PixmovingChassisInterfaceNode>(rclcpp::NodeOptions());

  // 改用多线程执行
  // rclcpp::executors::MultiThreadedExecutor executor;
  rclcpp::executors::SingleThreadedExecutor executor; //改用单线程执行器，避免多线程带来的复杂性
  RCLCPP_INFO(node->get_logger(), "Starting Pixmoving Chassis Interface Node with SingleThreadedExecutor");
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}