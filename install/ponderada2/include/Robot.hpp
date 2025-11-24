#ifndef PONDERADA2_ROBOT_HPP
#define PONDERADA2_ROBOT_HPP

#include <rclcpp/rclcpp.hpp>
// updated msg/srv names from cg_interfaces
#include <cg_interfaces/srv/move_cmd.hpp>
#include <cg_interfaces/msg/robot_sensors.hpp>

#include "Types.hpp"

namespace ponderada2 {

class Robot {
public:
    explicit Robot(rclcpp::Node::SharedPtr node);

    // Movimenta para frente na direção atual
    bool moveForward();

    // Gira esquerda/direita
    void turnLeft();
    void turnRight();

    // Move em uma direction (faz as rotações necessárias e avança)
    bool move(Direction d);

    // Sensores
    cg_interfaces::msg::RobotSensors readSensors();

    // Getters
    Position getPosition() const { return pos_; }
    Direction getDirection() const { return dir_; }

private:
    rclcpp::Node::SharedPtr node_;

    rclcpp::Client<cg_interfaces::srv::MoveCmd>::SharedPtr move_client_;
    rclcpp::Subscription<cg_interfaces::msg::RobotSensors>::SharedPtr sensor_sub_;

    cg_interfaces::msg::RobotSensors last_sensor_msg_;

    Position pos_;
    Direction dir_;

    // Funções auxiliares
    bool callMoveService(const std::string &cmd);
    void updatePositionForward();
};

} // namespace ponderada2

#endif
