#include "Algoritmo.hpp"
#include "Mapa.hpp"
#include "Robo.hpp"
#include <queue>

Algoritmo::Algoritmo(rclcpp::Node::SharedPtr node) : node_(node) {
    
}

Posicao Algoritmo::encontrarPosicao(std::vector<std::vector<char>>& mapa, char marca) {
    for (size_t i = 0; i < mapa.size(); i++) {
        for (size_t j = 0; j < mapa[i].size(); j++) {
            if (mapa[i][j] == marca) {
                return {(int)i, (int)j};
            }
        }
    }
    return {-1, -1};
}

std::vector<Posicao> Algoritmo::menorCaminho(std::vector<std::vector<char>>& mapa, Posicao inicio, Posicao destino) {


/*
Pseudocódigo de funcionamento do BFS: 

create a queue Q 
mark v as visited and put v into Q 
while Q is non-empty 
    remove the head u of Q 
    mark and enqueue all (unvisited) neighbours of u

*/


    int h = mapa.size();
    int w = mapa[0].size();
    
    std::vector<std::vector<bool>> visitado(h, std::vector<bool>(w, false));
    std::vector<std::vector<Posicao>> anterior(h, std::vector<Posicao>(w, {-1, -1}));
    std::queue<Posicao> fila;
    
    visitado[inicio.linha][inicio.coluna] = true;
    fila.push(inicio);
    
    int direcoes[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (!fila.empty()) {
        Posicao u = fila.front();
        fila.pop();
        
        if (u.linha == destino.linha && u.coluna == destino.coluna) {
            std::vector<Posicao> caminho;
            Posicao pos = destino;
            while (pos.linha != -1) {
                caminho.insert(caminho.begin(), pos);
                pos = anterior[pos.linha][pos.coluna];
            }
            return caminho;
        }
        
        for (int i = 0; i < 4; i++) {
            int nl = u.linha + direcoes[i][0];
            int nc = u.coluna + direcoes[i][1];
            
            if (nl >= 0 && nl < h && nc >= 0 && nc < w && !visitado[nl][nc] && mapa[nl][nc] != 'b') {
                visitado[nl][nc] = true;
                anterior[nl][nc] = u;
                fila.push({nl, nc});
            }
        }
    }
    
    return std::vector<Posicao>();
}

std::vector<std::string> Algoritmo::caminhoLista(const std::vector<Posicao>& caminho) {
    std::vector<std::string> comandos;
    
    for (size_t i = 0; i < caminho.size() - 1; i++) {
        int dl = caminho[i+1].linha - caminho[i].linha;
        int dc = caminho[i+1].coluna - caminho[i].coluna;
        
        if (dl == -1) comandos.push_back("up");
        else if (dl == 1) comandos.push_back("down");
        else if (dc == -1) comandos.push_back("left");
        else if (dc == 1) comandos.push_back("right");
    }
    
    return comandos;
}

std::vector<std::string> Algoritmo::gerarComandos() {
    Mapa mapa_obj(node_);
    std::vector<std::vector<char>> mapa = mapa_obj.receberMapa();
    
    if (mapa.empty()) return std::vector<std::string>();
    
    Posicao inicio = encontrarPosicao(mapa, 'r');
    Posicao destino = encontrarPosicao(mapa, 't');
    
    if (inicio.linha == -1 || destino.linha == -1) return std::vector<std::string>();
    
    std::vector<Posicao> caminho = menorCaminho(mapa, inicio, destino);
    
    if (caminho.empty()) return std::vector<std::string>();
    
    return caminhoLista(caminho);
}