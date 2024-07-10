//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_PENDULUM_H
#define PENDULUMBALANCERAI_PENDULUM_H

#include "../../config/configuration.h"
#include "../../Render/headers/pendulumrenderer.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace sf;

class Pendulum {
    float length;
    double angle;
    float damping;
    float gravity;
    float friction;

    Vector2f trackPosition;
    const float trackWidth = config::pendulum::dimensions::trackWidth;
    float basePosition;
    float baseVelocity;     //The speed is in px/s
    float baseAcceleration; //The acceleration is in px/s^2

    float angularVelocity;
    float angularAcceleration;

    Vector2f barPosition;
    Vector2f tipBallPosition;

    bool render;
    PendulumRenderer& renderer;

public:
    explicit Pendulum(RenderWindow &window, Vector2f startPosition, bool render, PendulumRenderer &renderer);

    void moveLeft();
    void moveRight();
    void setAcceleration(float acceleration);
    void stop();

    void update(Time timePerFrame);
    void applyGravity(const Time &timePerFrame);
    void checkCollision();
    void updatePosition(const Time &timePerFrame);

    void draw(int fitness, int keyPressed, Mode mode);

    [[nodiscard]] float getTipY() const;

    [[nodiscard]] float getPosition() const;
    [[nodiscard]] float getAngularVelocity() const;
    [[nodiscard]] float getAngleCos() const;
    [[nodiscard]] float getAngleSin() const;
    [[nodiscard]] float getAcceleration() const;
    [[nodiscard]] float getVelocity() const;
};


#endif //PENDULUMBALANCERAI_PENDULUM_H
