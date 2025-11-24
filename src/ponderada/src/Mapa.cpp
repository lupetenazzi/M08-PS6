#include "Mapa.hpp"

Mapa::Mapa(rclcpp::Node::SharedPtr node) : node_(node) {
    client_ = node_->create_client<cg_interfaces::srv::GetMap>("get_map");
}

std::pair<std::vector<std::string>, std::vector<uint8_t>> Mapa::getMaze() {
    auto request = std::make_shared<cg_interfaces::srv::GetMap::Request>();

    if (!client_->wait_for_service(std::chrono::seconds(5))) {
        RCLCPP_ERROR(node_->get_logger(), "Service get_map não está disponível!");
        return {};
    }

    RCLCPP_INFO(node_->get_logger(), "Chamando o service get_map...");

    auto future = client_->async_send_request(request);

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node_);

    if (executor.spin_until_future_complete(future) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(node_->get_logger(), "Mapa recebido com sucesso!");

        auto response = future.get();
        auto flat = response->occupancy_grid_flattened;
        auto shape_raw = response->occupancy_grid_shape;
        
        std::vector<uint8_t> shape(shape_raw.begin(), shape_raw.end());

        return {flat, shape};
    } 
    else {
        RCLCPP_ERROR(node_->get_logger(), "Falha ao receber o mapa!");
        return {};
    }
}


std::vector<std::vector<char>> Mapa::convertToMatrix(const std::vector<std::string>& raw_map) {
    std::vector<std::vector<char>> matrix;

    for (const auto& line : raw_map) {
        matrix.push_back(std::vector<char>(line.begin(), line.end()));
    }

    return matrix;
}

std::vector<std::vector<char>> Mapa::reshapeFlattenedMap(
        const std::vector<std::string>& flat,
        const std::vector<uint8_t>& shape)
{
    std::vector<std::vector<char>> matrix;

    if (shape.size() != 2) {
        RCLCPP_ERROR(node_->get_logger(), "Formato inválido de shape recebido!");
        return matrix;
    }

    int rows = shape[0];
    int cols = shape[1];

    if ((int)flat.size() != rows * cols) {
        RCLCPP_ERROR(node_->get_logger(),
            "Dimensões inconsistentes! Esperado %d elementos, recebido %ld",
            rows * cols, flat.size());
        return matrix;
    }

    matrix.resize(rows, std::vector<char>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = flat[i * cols + j][0];  // pega 1 char de cada string
        }
    }

    return matrix;
}


std::pair<int,int> Mapa::findRobotPosition(const std::vector<std::vector<char>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 'r') {  // robô = 'r'
                return {static_cast<int>(i), static_cast<int>(j)};
            }
        }
    }
    return {-1, -1};
}

std::pair<int,int> Mapa::findTargetPosition(const std::vector<std::vector<char>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 't') {  // alvo = 't'
                return {static_cast<int>(i), static_cast<int>(j)};
            }
        }
    }
    return {-1, -1};
}

void Mapa::printMap(const std::vector<std::vector<char>>& matrix) {
    RCLCPP_INFO(node_->get_logger(), "\n========== MAPA ==========");
    
    std::string header = "     ";
    for (size_t j = 0; j < matrix[0].size(); j++) {
        header += std::to_string(j % 10);
    }
    RCLCPP_INFO(node_->get_logger(), "%s", header.c_str());
    
    for (size_t i = 0; i < matrix.size(); i++) {
        std::string line = std::to_string(i);
        line += "    ";
        for (size_t j = 0; j < matrix[i].size(); j++) {
            char cell = matrix[i][j];
            if (cell == 'b') line += "#";      // parede
            else if (cell == 'f') line += " ";  // caminho livre
            else if (cell == 'r') line += "R";  // robô
            else if (cell == 't') line += "T";  // alvo
            else line += cell;
        }
        RCLCPP_INFO(node_->get_logger(), "%s", line.c_str());
    }
    
    RCLCPP_INFO(node_->get_logger(), "=========================\n");
    RCLCPP_INFO(node_->get_logger(), "Legenda: # = parede, espaço = livre, R = robô, T = alvo");
}

