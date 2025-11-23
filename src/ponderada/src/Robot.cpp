#include "Robot.hpp"

Robot::Robot(rclcpp::Node::SharedPtr node) : node_(node) {
    client_ = node_->create_client<cg_interfaces::srv::MoveCmd>("move_command");
}

bool Robot::move(const std::string &direction) {
    auto request = std::make_shared<cg_interfaces::srv::MoveCmd::Request>();
    request->direction = direction; 

    // Espera o serviço ficar disponível
    if (!client_->wait_for_service(std::chrono::seconds(2))) {
        RCLCPP_ERROR(node_->get_logger(), "Service move_command não disponível!");
        return false;
    }

    auto future = client_->async_send_request(request);

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node_);

    if (executor.spin_until_future_complete(future) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        bool result = future.get()->success;
        if (!result) {
            RCLCPP_WARN(node_->get_logger(), "Movimento falhou: %s", direction.c_str());
        }
        return result;
    }

    RCLCPP_ERROR(node_->get_logger(), "Falha ao enviar comando de movimento!");
    return false;
}
