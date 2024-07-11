cmake_minimum_required(VERSION 3.28)
project(PendulumBalancerAI)

set(CMAKE_CXX_STANDARD 20)

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
        src/Render/networkrenderer.cpp
        src/Render/headers/networkrenderer.h
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
        src/Network/genomejsonrepository.cpp
        src/Network/headers/genomejsonrepository.hpp
        src/Render/generationrender.cpp
        src/Render/scoresrender.cpp
        src/Network/headers/threadpool.hpp
        src/Render/headers/card.hpp
        src/Render/inforender.cpp
)

set(CMAKE_PREFIX_PATH "C:/SFML-2.6.1")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(PendulumBalancerAI sfml-graphics sfml-window sfml-system)