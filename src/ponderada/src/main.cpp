#include "rclcpp/rclcpp.hpp"
#include "Mapa.hpp"
#include "Robot.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("solution_test");

    Mapa mapa(node);
    Robot robo(node);

    // Obter o mapa (retorna flat + shape)
    auto [flat_map, shape] = mapa.getMaze();
    
    // Reshape o mapa para uma matriz 2D
    auto matrix = mapa.reshapeFlattenedMap(flat_map, shape);

    RCLCPP_INFO(node->get_logger(), "Mapa tem %zu linhas e %zu colunas", matrix.size(), 
                matrix.size() > 0 ? matrix[0].size() : 0);

    // Imprimir o mapa
    mapa.printMap(matrix);

    auto robot_pos = mapa.findRobotPosition(matrix);
    auto target_pos = mapa.findTargetPosition(matrix);

    RCLCPP_INFO(node->get_logger(), "Robô está em (%d, %d)", robot_pos.first, robot_pos.second);
    RCLCPP_INFO(node->get_logger(), "Alvo está em (%d, %d)", target_pos.first, target_pos.second);

    // TESTE: mover para a direita
    robo.move("right");

    rclcpp::shutdown();
    return 0;
}
