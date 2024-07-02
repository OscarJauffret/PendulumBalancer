cmake_minimum_required(VERSION 3.28)
project(PendulumBalancerAI)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/eigen-3.4.0/Eigen)

add_executable(PendulumBalancerAI src/main.cpp
        src/Engine/Engine.cpp
        src/headers/Engine.h
        src/Pendulum.cpp
        src/headers/Pendulum.h
        src/Engine/draw.cpp
        src/Engine/input.cpp
        src/Network/agent.cpp)

set(CMAKE_PREFIX_PATH "C:/SFML-2.6.1")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(PendulumBalancerAI sfml-graphics sfml-window sfml-system)