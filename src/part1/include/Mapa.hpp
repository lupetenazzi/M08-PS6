#ifndef PART1_MAPA_HPP
#define PART1_MAPA_HPP

#include <vector>
#include <string>
#include <utility> 
#include "rclcpp/rclcpp.hpp"
#include "cg_interfaces/srv/get_map.hpp"
#include <chrono>
#include <cstdlib>
#include <memory>

class Mapa {
public:
    Mapa(rclcpp::Node::SharedPtr node);

    std::vector<std::vector<char>> receberMapa();

   
private:
    std::vector<std::vector<char>> formatarMapa(const std::string dados, int altura, int largura);

    rclcpp::Client<cg_interfaces::srv::GetMap>::SharedPtr client_;
    rclcpp::Node::SharedPtr node_;
};



#endif