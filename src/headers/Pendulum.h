//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_PENDULUM_H
#define PENDULUMBALANCERAI_PENDULUM_H

#include "../config/configuration.h"

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

    RectangleShape bar;
    CircleShape tipBall;
    CircleShape baseBall;
    RectangleShape track;

public:
    explicit Pendulum(Vector2f startPosition);

    void moveLeft();
    void moveRight();
    void stop();

    float getTrackPositionY() const;

    void update(Time timePerFrame);
    void applyGravity(const Time &timePerFrame);
    void checkCollision();
    void updatePosition(const Time &timePerFrame);

    void draw(RenderWindow& window);

    float getTipY() const;
    float getPendulumLength() const;

    float getPosition() const;
    float getAngularVelocity() const;
    float getAngleCos() const;
    float getAngleSin() const;
    float getAcceleration() const;
    float getVelocity() const;

    void initializeShape(const Vector2f &startPosition);
    void initializeBar();
    void initializeBall(CircleShape& ball, float radius, Color color, float outlineThickness, Color outlineColor, float positionX, float positionY);
    void initializeTrack(const Vector2f &startPosition);

    void initializeBalls();
};


#endif //PENDULUMBALANCERAI_PENDULUM_H
