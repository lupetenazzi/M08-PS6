#include "Pathfinder.hpp"

bool Pathfinder::isValid(const std::vector<std::vector<char>>& maze, int x, int y) {
    return x >= 0 && x < (int)maze.size() &&
           y >= 0 && y < (int)maze[0].size() &&
           maze[x][y] != 'b'; // 'b' = parede (blocked)
}

std::vector<std::string> Pathfinder::findPath(
        const std::vector<std::vector<char>>& maze,
        std::pair<int,int> start,
        std::pair<int,int> goal)
{
    int cols = maze[0].size();

    std::queue<std::pair<int,int>> q;
    std::unordered_map<int, std::pair<int,int>> parent;

    q.push(start);

    std::unordered_map<int, bool> visited;
    visited[start.first * cols + start.second] = true;

    std::vector<std::pair<int,int>> directions = {
        {-1, 0}, // up
        {1, 0},  // down
        {0, -1}, // left
        {0, 1}   // right
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (std::make_pair(x, y) == goal) {
            break;
        }

        for (auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (isValid(maze, nx, ny)) {
                int id = nx * cols + ny;

                if (!visited[id]) {
                    visited[id] = true;
                    parent[id] = {x, y};
                    q.push({nx, ny});
                }
            }
        }
    }

    std::vector<std::string> moves;
    int gx = goal.first, gy = goal.second;

    if (!visited[gx * cols + gy]) {
        return {}; 
    }

    std::vector<std::pair<int,int>> path;

    while (std::make_pair(gx, gy) != start) {
        path.push_back({gx, gy});
        auto p = parent[gx * cols + gy];
        gx = p.first;
        gy = p.second;
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    for (size_t i = 1; i < path.size(); i++) {
        int x1 = path[i-1].first;
        int y1 = path[i-1].second;
        int x2 = path[i].first;
        int y2 = path[i].second;

        if (x2 == x1 - 1) moves.push_back("up");
        else if (x2 == x1 + 1) moves.push_back("down");
        else if (y2 == y1 - 1) moves.push_back("left");
        else if (y2 == y1 + 1) moves.push_back("right");
    }

    return moves;
}
