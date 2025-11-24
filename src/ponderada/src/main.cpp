#include "rclcpp/rclcpp.hpp"
#include "Solution.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    
    // Criar a solução
    auto solution = std::make_shared<Solution>();
    
    // Inicializar (agora o shared_from_this() funcionará)
    solution->init();
    
    // Manter o nó vivo por um tempo
    rclcpp::spin_some(solution);
    
    rclcpp::shutdown();
    return 0;
}
