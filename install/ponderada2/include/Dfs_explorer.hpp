#ifndef PONDERADA2_DFS_EXPLORER_HPP
#define PONDERADA2_DFS_EXPLORER_HPP

#include <rclcpp/rclcpp.hpp>
#include "Types.hpp"
#include "Robot.hpp"
#include "Map_builder.hpp"

namespace ponderada2 {

class DFSExplorer {
public:
    DFSExplorer(rclcpp::Node::SharedPtr node,
                Robot &robot,
                MapBuilder &map);

    // início da exploração
    void explore();

private:
    rclcpp::Node::SharedPtr node_;
    Robot &robot_;
    MapBuilder &map_;

    // DFS real (pos = posição atual)
    void dfs(const Position &pos);

    // tenta mover para uma direção; se conseguir, retorna true
    bool tryMove(Direction d);

    // move de volta na direção oposta (backtracking)
    void moveBack(Direction d);
};

} // namespace ponderada2

#endif
