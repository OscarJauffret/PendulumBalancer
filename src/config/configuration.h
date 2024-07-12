//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_CONFIGURATION_H
#define PENDULUMBALANCERAI_CONFIGURATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
using std::string;
using sf::Color;
using std::cout; using std::endl;
using std::thread;

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

        constexpr float acceleration = 1500.0f;

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
            constexpr float spaceBetweenBars = 2.0f;
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
            constexpr float originY = 400.0f;
            constexpr float backgroundWidth = 900.0f;
            constexpr float backgroundHeight = 300.0f;
            constexpr float bgOutlineThickness = 3.0f;
            constexpr float controlledInfoBgWidth = 120.0f;
            constexpr float controlledInfoBgHeight = 40.0f;

            namespace accel {
                constexpr float originX = score::originX + score::width + 10.0f;
                constexpr float originY = score::originY;
                constexpr float width = 600.0f;
                constexpr float height = 300.0f;
                constexpr float bgOutlineThickness = score::bgOutlineThickness;
                constexpr float rightPadding = 50.0f;
            }
        }

        namespace info {
            constexpr float originX = generation::originX;
            constexpr float originY = generation::originY + generation::height + 10.0f;
            constexpr float width = generation::width;
            constexpr float height = 50.0f;
            constexpr float bgOutlineThickness = 3.0f;
            constexpr float widgetRadius = 5.0f;
        }
    }

    namespace score {
        constexpr int timeLimit = 60;
        constexpr float lengthThreshold = 0.8f;
        constexpr float timeAboveThresholdToScore = 1.0f;
        constexpr float yThreshold = layout::pendulum::originY - (pendulum::dimensions::length * lengthThreshold);
    }

    namespace colors {
        const Color textColor = Color(255, 255, 255);

        namespace pendulum {
            const Color barColor = Color(255, 255, 255);
            const Color ballColor = Color(208, 100, 75);
            const Color ballOutlineColor = Color(255, 255, 255);
            const Color trackFillColor = Color::Transparent;
            const Color trackOutlineColor = Color(255, 255, 255);
            const Color thresholdColor = Color(80, 80, 80);
            const Color bgOutlineColor = Color(255, 255, 255);
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
            const Color darkerBackgroundColor = Color(50, 50, 50);
            const Color scoreOutlineColor = Color(200, 98, 76);
            const Color generationOutlineColor = Color(255, 255, 255);
            const Color scoreLineColor = Color(200, 98, 76);
            const Color controlledInfoBgColor = Color(39, 143, 39);
            const Color infoOutlineColor = Color(255, 255, 255);
            const Color activatedWidgetColor = Color(136, 209, 138);
            const Color deactivatedWidgetColor = Color(255, 116, 119);
            const Color accelChartOutlineColor = Color(66, 149, 245);
        }
    }

    namespace assets {
        const string fontPath = "../src/assets/Roboto-Regular.ttf";
    }

    namespace netrender {
        constexpr float nodeRadius = 10.0f;
        constexpr float nodeOutlineThickness = 3.0f;
        constexpr float maximumConnectionThickness = 10.0f;
        constexpr float minimumConnectionThickness = 0.0f;
    }

    namespace net {
        constexpr int inputSize = 6;
    }

    namespace genetic {
        constexpr int populationSize = 1120;
        constexpr int numberOfMutations = 6;
        constexpr float elitismRate = 0.25f;
        const size_t numThreads = thread::hardware_concurrency();
        constexpr float gameAccelerationFactor = 200.0f;

        namespace mut {
            constexpr float newNodeProba = 0.2f;
            constexpr float newConnectionProba = 0.8f;
            constexpr float weightAndBiasMutRate = 0.25f;
            constexpr float weightMutProportion = 0.5f;
            constexpr float newValueProba = 0.2f;
            constexpr float smallWeightRate = 0.01f;
            constexpr float addValueProba = 0.25f;
        }
    }
}

#endif //PENDULUMBALANCERAI_CONFIGURATION_H
