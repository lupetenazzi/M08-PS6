#include "rclcpp/rclcpp.hpp"
#include "Mapa.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <sstream>

Mapa::Mapa(rclcpp::Node::SharedPtr node) {
    node_ = node;
    client_ = node_->create_client<cg_interfaces::srv::GetMap>("get_map");
}

std::vector<std::vector<char>> Mapa::receberMapa() {
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Não foi possível conectar ao serviço de mapa.");
            return std::vector<std::vector<char>>();
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Aguardando pelo serviço");
    }

    auto request = std::make_shared<cg_interfaces::srv::GetMap::Request>();

    auto result_request = client_->async_send_request(request);

    if (rclcpp::spin_until_future_complete(node_, result_request) ==
        rclcpp::FutureReturnCode::SUCCESS) {

        auto response = result_request.get();
        int altura = static_cast<int>(response->occupancy_grid_shape[0]);
        int largura = static_cast<int>(response->occupancy_grid_shape[1]);

        std::string matriz_string;
        for (const auto& val : response->occupancy_grid_flattened) {
            matriz_string += val;
        }
    
        std::vector<std::vector<char>> mapa_formatado = formatarMapa(matriz_string, altura, largura);

        return mapa_formatado;
        
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Falha ao chamar o serviço de mapa");
        return std::vector<std::vector<char>>(); 
    }
    
}

std::vector<std::vector<char>> Mapa::formatarMapa(const std::string dados, int altura, int largura) {
    std::vector<std::vector<char>> mapa(altura, std::vector<char>(largura));
    
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            mapa[i][j] = dados[i * largura + j];
        }
    }
   
    return mapa;
}

