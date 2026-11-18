#ifndef RM_OOP_DEMO__KEYBOARD_TELEOP_NODE_HPP_
#define RM_OOP_DEMO__KEYBOARD_TELEOP_NODE_HPP_

#include <termios.h>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace rm_oop_demo
{

/// 键盘遥控节点：读取终端按键（w/s/a/d），向 /cmd_vel 发布速度指令。
class KeyboardTeleopNode : public rclcpp::Node
{
public:
  explicit KeyboardTeleopNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~KeyboardTeleopNode() override;

private:
  void enableRawMode();
  void restoreTerminal();
  void processKeys();
  void publishCommand();

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  termios cooked_{};
  bool raw_mode_enabled_{false};
  int stdin_flags_{0};
  bool flags_changed_{false};

  double linear_speed_{0.5};
  double angular_speed_{1.0};
  double linear_cmd_{0.0};
  double angular_cmd_{0.0};
};

}  // namespace rm_oop_demo

#endif  // RM_OOP_DEMO__KEYBOARD_TELEOP_NODE_HPP_
