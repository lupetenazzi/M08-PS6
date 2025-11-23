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

    // Função que chama o service e pega o mapa (flat + shape)
    std::pair<std::vector<std::string>, std::vector<uint8_t>> getMaze();

    // Converte o vetor flattened + shape em matriz de caracteres
    std::vector<std::vector<char>> reshapeFlattenedMap(
        const std::vector<std::string>& flat,
        const std::vector<uint8_t>& shape);

    // Converte o vetor de strings em matriz de caracteres (método legado)
    std::vector<std::vector<char>> convertToMatrix(const std::vector<std::string>& raw_map);

    // Encontra o robô (caractere 'r' no mapa)
    std::pair<int,int> findRobotPosition(const std::vector<std::vector<char>>& matrix);

    // Encontra o alvo (caractere 't' no mapa)
    std::pair<int,int> findTargetPosition(const std::vector<std::vector<char>>& matrix);

    // Imprime o mapa no terminal para visualização
    void printMap(const std::vector<std::vector<char>>& matrix);

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<cg_interfaces::srv::GetMap>::SharedPtr client_;
};

#endif
