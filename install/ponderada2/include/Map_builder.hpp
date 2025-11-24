#ifndef PONDERADA2_MAP_BUILDER_HPP
#define PONDERADA2_MAP_BUILDER_HPP

#include <vector>
#include <string>

#include "Types.hpp"
#include <cg_interfaces/msg/robot_sensors.hpp>

namespace ponderada2 {

class MapBuilder {
public:
    MapBuilder(int rows = 29, int cols = 29);

    // Marca a posição atual do robô no mapa
    void markRobot(const Position &pos);

    // Usa sensores para marcar paredes e espaços próximos
    void updateWithSensors(const Position &pos, const cg_interfaces::msg::RobotSensors &sensors);

    // Marca que uma célula foi visitada (importante p/ DFS)
    void markVisited(const Position &pos);

    // Verifica se célula está dentro do mapa
    bool inBounds(const Position &p) const;

    // Retorna se é parede
    bool isWall(const Position &p) const;

    // Retorna se já visitou
    bool isVisited(const Position &p) const;

    // Retorna se espaço é desconhecido ('?')
    bool isUnknown(const Position &p) const;

    // Marca parede
    void markWall(const Position &p);

    // Marca espaço vazio
    void markFree(const Position &p);

    // Acesso geral
    const std::vector<std::vector<char>>& getMap() const { return map_; }

    // Debug: imprime o mapa
    void print() const;

private:
    int rows_, cols_;
    std::vector<std::vector<char>> map_;
};

} // namespace ponderada2

#endif
