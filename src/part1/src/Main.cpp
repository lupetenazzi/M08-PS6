#include "rclcpp/rclcpp.hpp"
#include "Mapa.hpp"
#include <iostream>

int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("node_part1");

    Mapa mapa(node);
    std::vector<std::vector<char>> mapa_formatado = mapa.receberMapa();

    for (const auto& linha : mapa_formatado) {
        for (const auto& elemento : linha) {
            std::cout << elemento;
        }
        std::cout << std::endl;
    }

}