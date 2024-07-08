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

    PendulumRenderer renderer;

public:
    explicit Pendulum(RenderWindow &window, float yThreshold, Vector2f startPosition, bool render);

    void moveLeft();
    void moveRight();
    void setAcceleration(float acceleration);
    void stop();

    void update(Time timePerFrame);
    void applyGravity(const Time &timePerFrame);
    void checkCollision();
    void updatePosition(const Time &timePerFrame);

    void draw(int fitness, int keyPressed, Mode mode);

    float getTipY() const;

    float getPosition() const;
    float getAngularVelocity() const;
    float getAngleCos() const;
    float getAngleSin() const;
    float getAcceleration() const;
    float getVelocity() const;
};


#endif //PENDULUMBALANCERAI_PENDULUM_H
