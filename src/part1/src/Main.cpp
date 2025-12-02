#include "rclcpp/rclcpp.hpp"
#include "Mapa.hpp"
#include "Robo.hpp"
#include <iostream>

int main(int argc, char **argv){
    // Configurar opções de QoS para compatibilidade
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

    Robo robo(node);
    bool success = robo.movimentoRobo("down");

    std::cout << "Movimento realizado com sucesso: " << std::boolalpha << success << std::endl;

    rclcpp::shutdown();
    return 0;

}


