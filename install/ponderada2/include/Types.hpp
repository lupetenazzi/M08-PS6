#ifndef PONDERADA2_TYPES_HPP
#define PONDERADA2_TYPES_HPP

#include <cstdint>
#include <array>
#include <string>
#include <utility>

namespace ponderada2 {

/**
 * Direction: ordem usada consistentemente em DFS/explorer
 * NOTE: manter a ordem (UP, RIGHT, DOWN, LEFT) facilita operações com índices.
 */
enum class Direction : uint8_t {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

/**
 * Converte Direction para string (para logs e envio de comandos)
 */
inline std::string to_string(Direction d) {
    switch (d) {
        case Direction::UP: return "up";
        case Direction::RIGHT: return "right";
        case Direction::DOWN: return "down";
        case Direction::LEFT: return "left";
    }
    return "unknown";
}

/**
 * Posição no grid (linha, coluna)
 */
struct Position {
    int r;
    int c;
    Position() : r(-1), c(-1) {}
    Position(int rr, int cc) : r(rr), c(cc) {}

    bool operator==(const Position &o) const noexcept {
        return r == o.r && c == o.c;
    }
    bool operator!=(const Position &o) const noexcept {
        return !(*this == o);
    }

    // adicionar um deslocamento (dr, dc)
    Position moved(int dr, int dc) const noexcept {
        return Position(r + dr, c + dc);
    }
};

/**
 * Vetor de deslocamentos correspondentes a Direction na mesma ordem do enum:
 * UP, RIGHT, DOWN, LEFT
 */
static constexpr std::array<std::pair<int,int>,4> DIR_OFFSETS = {{
    {-1, 0}, // UP
    { 0, 1}, // RIGHT
    { 1, 0}, // DOWN
    { 0,-1}  // LEFT
}};

/**
 * Retorna a direção oposta (útil para backtracking)
 */
inline Direction opposite(Direction d) noexcept {
    switch (d) {
        case Direction::UP: return Direction::DOWN;
        case Direction::RIGHT: return Direction::LEFT;
        case Direction::DOWN: return Direction::UP;
        case Direction::LEFT: return Direction::RIGHT;
    }
    return Direction::UP;
}

} // namespace ponderada2

#endif // PONDERADA2_TYPES_HPP
