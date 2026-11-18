#include "rm_oop_demo/keyboard_teleop_node.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <memory>

namespace rm_oop_demo
{

KeyboardTeleopNode::KeyboardTeleopNode(const rclcpp::NodeOptions & options)
: Node("keyboard_teleop_node", options)
{
  linear_speed_ = declare_parameter<double>("linear_speed", 0.5);
  angular_speed_ = declare_parameter<double>("angular_speed", 1.0);
  const double publish_rate = declare_parameter<double>("publish_rate", 20.0);

  cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", rclcpp::QoS(10));
  enableRawMode();

  timer_ = create_wall_timer(
    std::chrono::duration<double>(1.0 / publish_rate),
    std::bind(&KeyboardTeleopNode::processKeys, this));

  std::printf(
    "\n键盘遥控节点已启动：\n"
    "  w/s：前进 / 后退    a/d：左转 / 右转\n"
    "  x 或空格：停止      q：退出\n\n");
  std::fflush(stdout);
}

KeyboardTeleopNode::~KeyboardTeleopNode()
{
  restoreTerminal();
}

void KeyboardTeleopNode::enableRawMode()
{
  stdin_flags_ = fcntl(STDIN_FILENO, F_GETFL, 0);
  if (stdin_flags_ >= 0) {
    fcntl(STDIN_FILENO, F_SETFL, stdin_flags_ | O_NONBLOCK);
    flags_changed_ = true;
  }

  if (!isatty(STDIN_FILENO)) {
    return;
  }

  tcgetattr(STDIN_FILENO, &cooked_);
  termios raw = cooked_;
  raw.c_lflag &= ~(ICANON | ECHO);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
  raw_mode_enabled_ = true;
}

void KeyboardTeleopNode::restoreTerminal()
{
  if (raw_mode_enabled_) {
    tcsetattr(STDIN_FILENO, TCSANOW, &cooked_);
    raw_mode_enabled_ = false;
  }
  if (flags_changed_) {
    fcntl(STDIN_FILENO, F_SETFL, stdin_flags_);
    flags_changed_ = false;
  }
}

void KeyboardTeleopNode::processKeys()
{
  char key = 0;
  while (::read(STDIN_FILENO, &key, 1) == 1) {
    switch (key) {
      case 'w':
      case 'W':
        linear_cmd_ = linear_speed_;
        break;
      case 's':
      case 'S':
        linear_cmd_ = -linear_speed_;
        break;
      case 'a':
      case 'A':
        angular_cmd_ = angular_speed_;
        break;
      case 'd':
      case 'D':
        angular_cmd_ = -angular_speed_;
        break;
      case 'x':
      case 'X':
      case ' ':
        linear_cmd_ = 0.0;
        angular_cmd_ = 0.0;
        break;
      case 'q':
      case 'Q':
        RCLCPP_INFO(get_logger(), "收到退出指令，停止键盘遥控");
        rclcpp::shutdown();
        return;
      default:
        break;
    }
  }

  publishCommand();
}

void KeyboardTeleopNode::publishCommand()
{
  geometry_msgs::msg::Twist cmd;
  cmd.linear.x = linear_cmd_;
  cmd.angular.z = angular_cmd_;
  cmd_vel_pub_->publish(cmd);
}

}  // namespace rm_oop_demo

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rm_oop_demo::KeyboardTeleopNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
