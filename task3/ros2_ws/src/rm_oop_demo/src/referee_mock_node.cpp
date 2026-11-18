#include "rm_oop_demo/referee_mock_node.hpp"

#include <algorithm>
#include <chrono>
#include <memory>
#include <string>

namespace rm_oop_demo
{

RefereeMockNode::RefereeMockNode(const rclcpp::NodeOptions & options)
: Node("referee_mock_node", options)
{
  robot_id_ = static_cast<uint8_t>(declare_parameter<int>("robot_id", 1));
  max_hp_ = static_cast<uint16_t>(declare_parameter<int>("max_hp", 200));
  current_hp_ = static_cast<uint16_t>(declare_parameter<int>("initial_hp", 120));
  remaining_ammo_ = static_cast<uint16_t>(declare_parameter<int>("initial_ammo", 100));
  stage_seconds_ = declare_parameter<int>("stage_seconds", 180);
  hp_decay_per_sec_ = declare_parameter<int>("hp_decay_per_sec", 1);
  ammo_consume_period_ = declare_parameter<int>("ammo_consume_period", 2);

  game_status_pub_ = create_publisher<rm_oop_demo::msg::GameStatus>(
    "referee/game_status", rclcpp::QoS(10));
  robot_status_pub_ = create_publisher<rm_oop_demo::msg::RobotStatus>(
    "referee/robot_status", rclcpp::QoS(10));
  ammo_status_pub_ = create_publisher<rm_oop_demo::msg::AmmoStatus>(
    "referee/ammo_status", rclcpp::QoS(10));

  supply_hp_srv_ = create_service<rm_oop_demo::srv::SupplyHp>(
    "supplyhp",
    std::bind(
      &RefereeMockNode::handleSupplyHp, this,
      std::placeholders::_1, std::placeholders::_2));

  timer_ = create_wall_timer(
    std::chrono::seconds(1), std::bind(&RefereeMockNode::tick, this));

  RCLCPP_INFO(
    get_logger(), "裁判模拟节点已启动：血量 %u/%u，弹量 %u，阶段时长 %d s",
    static_cast<unsigned int>(current_hp_),
    static_cast<unsigned int>(max_hp_),
    static_cast<unsigned int>(remaining_ammo_),
    stage_seconds_);
}

void RefereeMockNode::tick()
{
  ++ticks_;

  game_progress_ = stage_seconds_ - ticks_ > 0 ? 4 : 5;

  if (game_progress_ == 4) {
    current_hp_ = static_cast<uint16_t>(
      std::max(0, static_cast<int>(current_hp_) - hp_decay_per_sec_));

    const int consume_period = std::max(1, ammo_consume_period_);
    if (ticks_ % consume_period == 0) {
      remaining_ammo_ = static_cast<uint16_t>(
        std::max(0, static_cast<int>(remaining_ammo_) - 1));
    }
  }

  publishRefereeData();
}

void RefereeMockNode::publishRefereeData()
{
  const rclcpp::Time stamp = now();

  rm_oop_demo::msg::GameStatus game_status;
  game_status.header.stamp = stamp;
  game_status.header.frame_id = "referee";
  game_status.game_progress = game_progress_;
  game_status.stage_remain_time = static_cast<uint16_t>(
    std::max(0, stage_seconds_ - ticks_));
  game_status.current_round = 1;
  game_status.total_rounds = 3;
  game_status_pub_->publish(game_status);

  rm_oop_demo::msg::RobotStatus robot_status;
  robot_status.header.stamp = stamp;
  robot_status.header.frame_id = "referee";
  robot_status.robot_id = robot_id_;
  robot_status.current_hp = current_hp_;
  robot_status.max_hp = max_hp_;
  robot_status_pub_->publish(robot_status);

  rm_oop_demo::msg::AmmoStatus ammo_status;
  ammo_status.header.stamp = stamp;
  ammo_status.header.frame_id = "referee";
  ammo_status.robot_id = robot_id_;
  ammo_status.remaining_ammo = remaining_ammo_;
  ammo_status_pub_->publish(ammo_status);
}

void RefereeMockNode::handleSupplyHp(
  const std::shared_ptr<rm_oop_demo::srv::SupplyHp::Request> request,
  std::shared_ptr<rm_oop_demo::srv::SupplyHp::Response> response)
{
  if (request->amount == 0) {
    response->success = false;
    response->current_hp = current_hp_;
    response->message = "回血量必须大于 0";
    RCLCPP_WARN(get_logger(), "/supplyhp 请求无效：amount = 0");
    return;
  }

  const int healed = std::min(
    static_cast<int>(max_hp_),
    static_cast<int>(current_hp_) + static_cast<int>(request->amount));
  current_hp_ = static_cast<uint16_t>(healed);

  response->success = true;
  response->current_hp = current_hp_;
  response->message = "回血成功";

  RCLCPP_INFO(
    get_logger(), "/supplyhp 回血 %u，当前血量 %u/%u",
    static_cast<unsigned int>(request->amount),
    static_cast<unsigned int>(current_hp_),
    static_cast<unsigned int>(max_hp_));

  publishRefereeData();
}

}  // namespace rm_oop_demo

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rm_oop_demo::RefereeMockNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
