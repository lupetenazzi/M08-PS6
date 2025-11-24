#ifndef PONDERADA_MAPA_HPP
#define PONDERADA_MAPA_HPP

#include <vector>
#include <string>
#include <utility>  // std::pair
#include "rclcpp/rclcpp.hpp"
#include "cg_interfaces/srv/get_map.hpp"

class Mapa {
public:
    Mapa(rclcpp::Node::SharedPtr node);

    std::pair<std::vector<std::string>, std::vector<uint8_t>> getMaze();

    std::vector<std::vector<char>> reshapeFlattenedMap(
        const std::vector<std::string>& flat,
        const std::vector<uint8_t>& shape);

    std::vector<std::vector<char>> convertToMatrix(const std::vector<std::string>& raw_map);

    std::pair<int,int> findRobotPosition(const std::vector<std::vector<char>>& matrix);

    std::pair<int,int> findTargetPosition(const std::vector<std::vector<char>>& matrix);

    void printMap(const std::vector<std::vector<char>>& matrix);

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<cg_interfaces::srv::GetMap>::SharedPtr client_;
};

#endif
