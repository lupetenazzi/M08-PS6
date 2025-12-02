#ifndef PART1_ROBO_HPP
#define PART1_ROBO_HPP

#include <vector>
#include <string>
#include <utility> 
#include "rclcpp/rclcpp.hpp"
#include "cg_interfaces/srv/move_cmd.hpp"
#include <chrono>
#include <cstdlib>
#include <memory>

class Robo {
public:
    Robo(rclcpp::Node::SharedPtr node);

    bool movimentoRobo(std::string direction);

private:

    rclcpp::Client<cg_interfaces::srv::MoveCmd>::SharedPtr client_;
    rclcpp::Node::SharedPtr node_;

};



#endif