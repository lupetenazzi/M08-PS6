#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <unordered_map>
#include <algorithm>

class Pathfinder {
public:
    /**
     * Encontra o caminho da posição start para goal usando BFS.
     * Retorna uma lista de movimentos: {"up", "down", "left", "right"}.
     */
    std::vector<std::string> findPath(
        const std::vector<std::vector<char>>& maze,
        std::pair<int,int> start,
        std::pair<int,int> goal
    );

private:
    bool isValid(const std::vector<std::vector<char>>& maze, int x, int y);
};

#endif
