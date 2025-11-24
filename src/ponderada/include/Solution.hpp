#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "rclcpp/rclcpp.hpp"
#include "cg_interfaces/srv/move_cmd.hpp"
#include "Mapa.hpp"
#include "Pathfinder.hpp"

class Solution : public rclcpp::Node {
public:
    Solution();
    void init();

private:
    std::shared_ptr<Mapa> mapa_;
    std::shared_ptr<Pathfinder> pathfinder_;
    rclcpp::Client<cg_interfaces::srv::MoveCmd>::SharedPtr client_;

    void solve();
    void sendMove(const std::string &cmd);
};

#endif
