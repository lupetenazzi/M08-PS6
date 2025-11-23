cmake_minimum_required(VERSION 3.8...3.27)
project(ponderada)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cg_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Add library for Mapa class
add_library(mapa_lib src/Mapa.cpp)
ament_target_dependencies(mapa_lib rclcpp cg_interfaces)
target_include_directories(mapa_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Add library for Robot class
add_library(robot_lib src/Robot.cpp)
ament_target_dependencies(robot_lib rclcpp cg_interfaces)
target_include_directories(robot_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Install library
install(TARGETS mapa_lib robot_lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Add executable for main
add_executable(solution_tester src/main.cpp)
ament_target_dependencies(solution_tester rclcpp)
target_link_libraries(solution_tester mapa_lib robot_lib)
target_include_directories(solution_tester PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Install executable
install(TARGETS solution_tester DESTINATION lib/${PROJECT_NAME})

ament_package()
