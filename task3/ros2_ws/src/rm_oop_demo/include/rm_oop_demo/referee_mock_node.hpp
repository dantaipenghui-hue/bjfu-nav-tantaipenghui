#ifndef RM_OOP_DEMO__REFEREE_MOCK_NODE_HPP_
#define RM_OOP_DEMO__REFEREE_MOCK_NODE_HPP_

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rm_oop_demo/msg/ammo_status.hpp"
#include "rm_oop_demo/msg/game_status.hpp"
#include "rm_oop_demo/msg/robot_status.hpp"
#include "rm_oop_demo/srv/supply_hp.hpp"

namespace rm_oop_demo
{

/// 裁判系统模拟节点：发布比赛阶段 / 血量 / 弹量，并提供 /supplyhp 回血服务。
class RefereeMockNode : public rclcpp::Node
{
public:
  explicit RefereeMockNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

private:
  void tick();
  void publishRefereeData();
  void handleSupplyHp(
    const std::shared_ptr<rm_oop_demo::srv::SupplyHp::Request> request,
    std::shared_ptr<rm_oop_demo::srv::SupplyHp::Response> response);

  rclcpp::Publisher<rm_oop_demo::msg::GameStatus>::SharedPtr game_status_pub_;
  rclcpp::Publisher<rm_oop_demo::msg::RobotStatus>::SharedPtr robot_status_pub_;
  rclcpp::Publisher<rm_oop_demo::msg::AmmoStatus>::SharedPtr ammo_status_pub_;
  rclcpp::Service<rm_oop_demo::srv::SupplyHp>::SharedPtr supply_hp_srv_;
  rclcpp::TimerBase::SharedPtr timer_;

  uint8_t robot_id_{1};
  uint16_t max_hp_{200};
  uint16_t current_hp_{120};
  uint16_t remaining_ammo_{100};

  int stage_seconds_{180};
  int ticks_{0};
  int hp_decay_per_sec_{1};
  int ammo_consume_period_{2};
  uint8_t game_progress_{4};
};

}  // namespace rm_oop_demo

#endif  // RM_OOP_DEMO__REFEREE_MOCK_NODE_HPP_
