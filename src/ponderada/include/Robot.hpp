#ifndef PONDERADA_ROBOT_HPP
#define PONDERADA_ROBOT_HPP

#include <string>
#include "rclcpp/rclcpp.hpp"
#include "cg_interfaces/srv/move_cmd.hpp"

class Robot {
public:
    Robot(rclcpp::Node::SharedPtr node);

    // Envia um comando de movimento: 'up', 'down', 'left', 'right'
    bool move(const std::string &direction);

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<cg_interfaces::srv::MoveCmd>::SharedPtr client_;
};

#endif
