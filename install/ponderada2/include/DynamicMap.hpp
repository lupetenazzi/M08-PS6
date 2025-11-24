#pragma once
#include <vector>
#include <string>

class DynamicMap {
public:
    DynamicMap(int size = 100);

    void setCell(int x, int y, char value);
    char getCell(int x, int y) const;

    bool inBounds(int x, int y) const;

    void markRobot(int x, int y);
    void markTarget(int x, int y);
    void markWall(int x, int y);
    void markFree(int x, int y);

    void print() const;

    const std::vector<std::vector<char>>& getMatrix() const { return map_; }

private:
    int size_;
    int offset_;
    std::vector<std::vector<char>> map_;
};
