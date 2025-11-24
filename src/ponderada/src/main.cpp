#include "rclcpp/rclcpp.hpp"
#include "Solution.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    
    auto solution = std::make_shared<Solution>();
    
    solution->init();
    
    rclcpp::spin_some(solution);
    
    rclcpp::shutdown();
    return 0;
}
