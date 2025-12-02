#include "rclcpp/rclcpp.hpp"
#include "Robo.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <sstream>


Robo::Robo(rclcpp::Node::SharedPtr node) {
    node_ = node;
    
    rclcpp::QoS qos = rclcpp::ServicesQoS();
    
    client_ = node_->create_client<cg_interfaces::srv::MoveCmd>(
        "/move_command",
        qos
    );
}


bool Robo::movimentoRobo(std::string direction) {
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Não foi possível conectar ao serviço de movimento.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Aguardando pelo serviço de movimento");
    }

    auto request = std::make_shared<cg_interfaces::srv::MoveCmd::Request>();
    request->direction = direction;

    auto result_request = client_->async_send_request(request);

    if (rclcpp::spin_until_future_complete(node_, result_request) ==
        rclcpp::FutureReturnCode::SUCCESS) {

        auto response = result_request.get();
        return response->success;
        
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Falha ao chamar o serviço de movimento");
        return false; 
    }
    
}


