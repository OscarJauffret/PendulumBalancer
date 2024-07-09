//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_CONFIGURATION_H
#define PENDULUMBALANCERAI_CONFIGURATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using std::string;
using sf::Color;
using std::cout; using std::endl;

#define M_PI 3.14159265358979323846
#define M_PHI 1.61803398874989484820

enum class Mode {
    Manual,
    Ai
};

namespace config {

    namespace window {
        constexpr int width = 1920;
        constexpr int height = 1080;
        constexpr int fps = 60;
        constexpr unsigned int style = sf::Style::Fullscreen;
        const string title = "Pendulum Balancer AI";
    }

    namespace physics {
        constexpr float gravity = 400.0f;
        constexpr float damping = 20.0f;
        constexpr float friction = 2.0f;
    }

    namespace pendulum {
        constexpr float startAngle = 0.0f;
        constexpr float startAngularVelocity = 0.0f;
        constexpr float startAngularAcceleration = 0.0f;

        constexpr float startPosition = 0.0f;
        constexpr float startVelocity = 0.0f;
        constexpr float startAcceleration = 0.0f;

        constexpr float acceleration = 500.0f;

        namespace dimensions {
            constexpr float length = 100.0f;
            constexpr float barWidth = 5.0f;
            constexpr float ballRadius = 10.0f;
            constexpr float ballOutlineThickness = 3.0f;
            constexpr float trackWidth = 600.0f;
            constexpr float trackHeight = 5.0f;
            constexpr float trackOutlineThickness = 2.0f;
        }
    }

    namespace layout {
        namespace net {
            constexpr float height = 300.0f;
            constexpr float width = 300.0f;
            constexpr float originX = 10.0f;
            constexpr float originY = window::height - height - 10.0f;
        }

        namespace score {
            constexpr float originX = net::originX + net::width + 10.0f;
            constexpr float originY = net::originY;
            constexpr float width = 300.0f;
            constexpr float height = 300.0f;
            constexpr float barWidth = 15.0f;
            constexpr float spaceBetweenBars = 5.0f;
            constexpr float bgOutlineThickness = 3.0f;
        }

        namespace generation {
            constexpr float originX = 10.0f;
            constexpr float originY = 10.0f;
            constexpr float width = 150.0f;
            constexpr float height = 100.0f;
            constexpr float bgOutlineThickness = 3.0f;
        }

        namespace pendulum {
            constexpr float originX = window::width / 2;
            constexpr float originY = 200.0f;
        }
    }

    namespace score {
        constexpr int timeLimit = 60;
        constexpr float lengthThreshold = 0.2f;
        constexpr float timeAboveThresholdToScore = 0.5f;
    }

    namespace colors {
        const Color textColor = Color(255, 255, 255);

        namespace pendulum {
            const Color barColor = Color(255, 255, 255);
            const Color ballColor = Color(208, 100, 75);
            const Color ballOutlineColor = Color(255, 255, 255);
            const Color trackFillColor = Color::Transparent;
            const Color trackOutlineColor = Color(255, 255, 255);
            [[maybe_unused]] const Color thresholdColor = Color(80, 80, 80);
        }

        namespace net {
            const Color nodeColor = Color(24, 49, 79);
            const Color nodeOutlineColor = Color(255, 248, 243);
            const Color connectionColor = Color(255, 248, 243);
        }

        namespace buttons {
            const Color normal = Color(66, 108, 245);
            const Color outline = Color(255, 255, 255);
        }

        namespace layout {
            const Color backgroundColor = Color(80, 80, 80);
            const Color scoreBackgroundColor = Color(50, 50, 50);
            const Color generationBackgroundColor = Color(50, 50, 50);
            const Color scoreOutlineColor = Color(200, 98, 76);
            const Color generationOutlineColor = Color(255, 255, 255);
            const Color scoreLineColor = Color(200, 98, 76);
            const Color inputRectColor = Color(80, 80, 80);
        }
    }

    namespace assets {
        const string fontPath = "../src/assets/Roboto-Regular.ttf";
    }

    namespace netrender {
        constexpr float nodeRadius = 10.0f;
        constexpr float nodeOutlineThickness = 3.0f;
        constexpr float maximumConnectionThickness = 10.0f;
    }

    namespace net {
        constexpr int inputSize = 6;
    }

    namespace genetic {
        constexpr int populationSize = 100;
        constexpr int batchSize = 10;
        constexpr int numberOfMutations = 4;
        constexpr float elitismRate = 0.25f;
    }
}

#endif //PENDULUMBALANCERAI_CONFIGURATION_H
