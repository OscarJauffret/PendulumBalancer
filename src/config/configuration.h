//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_CONFIGURATION_H
#define PENDULUMBALANCERAI_CONFIGURATION_H

#include <SFML/Graphics/Color.hpp>
#include <string>
using std::string;

using sf::Color;

namespace config {

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

    namespace colors {
        const Color backgroundColor = Color(0, 0, 0);
        const Color barColor = Color(255, 255, 255);
        const Color ballColor = Color(208, 100, 75);
        const Color ballOutlineColor = Color(255, 255, 255);
        const Color trackFillColor = Color(0, 0, 0);
        const Color trackOutlineColor = Color(255, 255, 255);
        [[maybe_unused]] const Color thresholdColor = Color(80, 80, 80);
        const Color inputRectColor = Color(80, 80, 80);
    }

    namespace assets {
        const string fontPath = "assets/fonts/arial.ttf";
    }
}

#endif //PENDULUMBALANCERAI_CONFIGURATION_H
