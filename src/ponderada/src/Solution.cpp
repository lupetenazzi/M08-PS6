#include "rclcpp/rclcpp.hpp"
#include "Solution.hpp"
#include "Mapa.hpp"
#include "Pathfinder.hpp"
#include "cg_interfaces/srv/move_cmd.hpp"

Solution::Solution() : Node("solution_node") {
    RCLCPP_INFO(this->get_logger(), "Solution node criado (inicialização adiada)");
}

void Solution::init() {
    mapa_ = std::make_shared<Mapa>(shared_from_this());
    pathfinder_ = std::make_shared<Pathfinder>();

    client_ = this->create_client<cg_interfaces::srv::MoveCmd>("move_command");

    RCLCPP_INFO(this->get_logger(), "Solution node inicializado!");
    
    // Dar tempo para o client se registrar
    rclcpp::sleep_for(std::chrono::milliseconds(500));
    
    solve();
}

void Solution::solve() {
    RCLCPP_INFO(this->get_logger(), "=== Iniciando solve() ===");
    
    // 1. Ler o mapa
    RCLCPP_INFO(this->get_logger(), "Lendo o mapa...");
    auto [flat, shape] = mapa_->getMaze();
    if (flat.empty()) {
        RCLCPP_ERROR(this->get_logger(), "❌ Não foi possível carregar o mapa");
        return;
    }

    RCLCPP_INFO(this->get_logger(), "Mapa carregado: %zu elementos", flat.size());
    
    auto maze = mapa_->reshapeFlattenedMap(flat, shape);
    RCLCPP_INFO(this->get_logger(), "Mapa reformatado: %zu x %zu", maze.size(), 
                maze.size() > 0 ? maze[0].size() : 0);

    // Imprimir mapa para debug
    mapa_->printMap(maze);

    // 2. Encontrar posições
    auto start = mapa_->findRobotPosition(maze);
    auto goal  = mapa_->findTargetPosition(maze);

    RCLCPP_INFO(this->get_logger(), "🤖 Robô em: (%d, %d)", start.first, start.second);
    RCLCPP_INFO(this->get_logger(), "🎯 Alvo em: (%d, %d)", goal.first, goal.second);
    
    if (start.first == -1 || goal.first == -1) {
        RCLCPP_ERROR(this->get_logger(), "❌ Não foi possível encontrar robô ou alvo");
        return;
    }

    // 3. Calcular caminho
    RCLCPP_INFO(this->get_logger(), "Calculando caminho...");
    auto moves = pathfinder_->findPath(maze, start, goal);

    if (moves.empty()) {
        RCLCPP_ERROR(this->get_logger(), "❌ Não existe caminho até o alvo!");
        return;
    }

    RCLCPP_INFO(this->get_logger(), "✓ Caminho encontrado com %ld passos", moves.size());
    
    // Debug: mostrar os primeiros movimentos
    RCLCPP_INFO(this->get_logger(), "Primeiros 5 movimentos:");
    for (size_t i = 0; i < std::min(size_t(5), moves.size()); i++) {
        RCLCPP_INFO(this->get_logger(), "  %ld. %s", i + 1, moves[i].c_str());
    }

    // 4. Executar movimentos
    RCLCPP_INFO(this->get_logger(), "🚀 Iniciando execução dos %ld movimentos...", moves.size());
    
    for (size_t i = 0; i < moves.size(); i++) {
        RCLCPP_INFO(this->get_logger(), "[%ld/%ld] Movendo: %s", 
                   i + 1, moves.size(), moves[i].c_str());
        sendMove(moves[i]);
        rclcpp::sleep_for(std::chrono::milliseconds(500)); // pausa entre movimentos
    }

    RCLCPP_INFO(this->get_logger(), "✓✓✓ ROBÔ CHEGOU AO ALVO! ✓✓✓");
}

void Solution::sendMove(const std::string &cmd) {
    RCLCPP_DEBUG(this->get_logger(), "sendMove() chamado com: %s", cmd.c_str());
    
    if (!client_->wait_for_service(std::chrono::seconds(2))) {
        RCLCPP_ERROR(this->get_logger(), "❌ Service move_command não disponível!");
        return;
    }

    auto request = std::make_shared<cg_interfaces::srv::MoveCmd::Request>();
    request->direction = cmd;

    RCLCPP_DEBUG(this->get_logger(), "Enviando requisição para: %s", cmd.c_str());
    auto future = client_->async_send_request(request);
    
    // Usar executor para aguardar resposta
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(shared_from_this());
    
    auto status = executor.spin_until_future_complete(future, std::chrono::seconds(10));
    
    if (status != rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_ERROR(this->get_logger(), "❌ Timeout aguardando resposta para: %s", cmd.c_str());
        return;
    }

    try {
        auto response = future.get();
        if (response->success) {
            RCLCPP_INFO(this->get_logger(), "✓ Movimento '%s' executado com sucesso", cmd.c_str());
        } else {
            RCLCPP_WARN(this->get_logger(), "⚠️  Movimento '%s' falhou", cmd.c_str());
        }
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "❌ Erro ao executar movimento '%s': %s", 
                     cmd.c_str(), e.what());
    }
}
