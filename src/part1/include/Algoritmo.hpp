#ifndef PART1_ALGORITMO_HPP
#define PART1_ALGORITMO_HPP

#include <vector>
#include <string>
#include <queue>
#include "rclcpp/rclcpp.hpp"

struct Posicao {

    int linha, coluna;

};

class Algoritmo {
public:

    Algoritmo(rclcpp::Node::SharedPtr node);
    std::vector<std::string> gerarComandos();

private:

    Posicao encontrarPosicao(std::vector<std::vector<char>>& mapa, char marca);
    std::vector<Posicao> menorCaminho(std::vector<std::vector<char>>& mapa, Posicao inicio, Posicao destino);
    std::vector<std::string> caminhoLista(const std::vector<Posicao>& caminho);
    rclcpp::Node::SharedPtr node_;

};

#endif