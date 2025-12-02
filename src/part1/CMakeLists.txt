cmake_minimum_required(VERSION 3.8)
project(part1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cg_interfaces REQUIRED)

# additional dependencies needed for linking (spdlog used by rcl_logging_spdlog, and system numa)
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)

# try to locate libnuma (some systems name it 'numa' or 'libnuma')
find_library(NUMA_LIB NAMES numa libnuma)
if(NUMA_LIB)
  message(STATUS "Found libnuma: ${NUMA_LIB}")
else()
  message(WARNING "libnuma not found - you may need to install libnuma (e.g. libnuma-dev) or add its path to LD_LIBRARY_PATH")
endif()

# create executable with all source files
add_executable(main 
  src/Main.cpp 
  src/Mapa.cpp
  src/Robo.cpp
  src/Algoritmo.cpp
)

# include directories for the project
target_include_directories(main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# link ROS2 dependencies
ament_target_dependencies(main
  rclcpp
  std_msgs
  cg_interfaces
)

# link external libraries: spdlog, fmt, threads, and numa (if available)
target_link_libraries(main 
  spdlog::spdlog 
  fmt::fmt
  Threads::Threads 
  ${NUMA_LIB}
)

# set C++ standard
set_target_properties(main PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  INSTALL_RPATH "/opt/ros/jazzy/lib;$ORIGIN/../lib"
)

install(TARGETS main
  DESTINATION lib/${PROJECT_NAME})

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

ament_package()
