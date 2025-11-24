#pragma once

#include <rclcpp/rclcpp.hpp>
#include <cg_interfaces/srv/move_cmd.hpp>
#include "DynamicMap.hpp"

class Explorer {
public:
    Explorer(rclcpp::Node::SharedPtr node);

    void startExploration();

private:
    // ROS
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<cg_interfaces::srv::MoveCmd>::SharedPtr move_client_;

    // Mapa dinâmico
    DynamicMap map_;

    // Estado atual
    int rx_, ry_;
    bool target_found_;

    // DFS
    bool dfsExplore(int x, int y);

    // Movimento real
    bool moveTo(int nx, int ny);

    // Direções (dx, dy)
    const std::vector<std::pair<int,int>> directions_ = {
        {0, 1},   // direita
        {1, 0},   // baixo
        {0, -1},  // esquerda
        {-1, 0}   // cima
    };
};
