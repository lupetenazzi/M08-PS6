#include "rclcpp/rclcpp.hpp"
#include "Mapa.hpp"
#include "Robo.hpp"
#include "Algoritmo.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char **argv) {
    
    rclcpp::NodeOptions node_options;
    node_options.use_intra_process_comms(true);
    
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("node_part1", node_options);

    Mapa mapa(node);
    std::vector<std::vector<char>> mapa_formatado = mapa.receberMapa();

    for (const auto& linha : mapa_formatado) {
        for (const auto& elemento : linha) {
            std::cout << elemento;
        }
        std::cout << std::endl;
    }

    Algoritmo algoritmo(node);
    auto comandos = algoritmo.gerarComandos();

    Robo robo(node);
    for (const auto& cmd : comandos) {
        robo.movimentoRobo(cmd);
        rclcpp::sleep_for(std::chrono::milliseconds(500));
    }

    rclcpp::shutdown();
    return 0;
}


