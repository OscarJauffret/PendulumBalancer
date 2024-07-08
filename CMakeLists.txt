cmake_minimum_required(VERSION 3.28)
project(PendulumBalancerAI)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/eigen-3.4.0/Eigen)

add_executable(PendulumBalancerAI src/main.cpp
        src/Engine/Engine.cpp
        src/Engine/headers/Engine.h
        src/Engine/Pendulum/Pendulum.cpp
        src/Engine/headers/Pendulum.h
        src/Engine/input.cpp
        src/config/configuration.h
        src/Network/headers/genome.h
        src/Network/headers/activation.hpp
        src/Network/Genome.cpp
        src/Network/networkdrawer.cpp
        src/Network/headers/networkdrawer.h
        src/Network/genetic.cpp
        src/Network/headers/genetic.h
        src/Render/renderer.cpp
        src/Render/headers/renderer.hpp
        src/Render/button.cpp
        src/Render/headers/button.hpp
        src/Render/pendulumrenderer.cpp
        src/Render/headers/pendulumrenderer.hpp
        src/Render/shapeinitializer.cpp
        src/Network/randomnumbergenerator.cpp
        src/Network/headers/randomnumbergenerator.hpp
        src/Network/mutator.cpp
        src/Network/headers/mutator.hpp
)

set(CMAKE_PREFIX_PATH "C:/SFML-2.6.1")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(PendulumBalancerAI sfml-graphics sfml-window sfml-system)