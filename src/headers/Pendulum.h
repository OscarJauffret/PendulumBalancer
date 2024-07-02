//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_PENDULUM_H
#define PENDULUMBALANCERAI_PENDULUM_H


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
    const float trackWidth = 600;
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

    void update(Time timePerFrame);
    void applyGravity(const Time &timePerFrame);
    void checkCollision();
    void updatePosition(const Time &timePerFrame);

    void draw(RenderWindow& window);
    float getTipY() const;

    float getPendulumLength() const;
    float getPosition();
    float getAngularVelocity();
    float getAngleCos();
    float getAngleSin();
    float getAcceleration();

    float getVelocity();
};


#endif //PENDULUMBALANCERAI_PENDULUM_H
