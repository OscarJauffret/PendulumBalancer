//
// Created by oscar on 02/07/2024.
//

#include "../headers/Pendulum.h"

using std::cout; using std::endl;

Pendulum::Pendulum(RenderWindow &window, Vector2f startPosition, bool render, PendulumRenderer &renderer)
        : renderer(renderer), render(render) {
    length = config::pendulum::dimensions::length;
    angle = config::pendulum::startAngle;

    damping = config::physics::damping;
    gravity = config::physics::gravity;
    friction = config::physics::friction;

    angularVelocity = config::pendulum::startAngularVelocity;
    angularAcceleration = config::pendulum::startAngularAcceleration;

    trackPosition = startPosition;
    basePosition = config::pendulum::startPosition;
    baseVelocity = config::pendulum::startVelocity;
    baseAcceleration = config::pendulum::startAcceleration;

    barPosition = startPosition;
    tipBallPosition = Vector2f(startPosition.x, startPosition.y + length);
    if (render) {
        renderer.resetAccelerations();
    }
}

void Pendulum::moveLeft() {
    if (basePosition != -(trackWidth / 2)) {
        baseAcceleration = -config::pendulum::acceleration;
    }
}

void Pendulum::moveRight() {
    if (basePosition != trackWidth / 2) {
        baseAcceleration = config::pendulum::acceleration;
    }
}

void Pendulum::setAcceleration(float acceleration) {
    if (acceleration > 0 && basePosition != trackWidth / 2) {
        baseAcceleration = acceleration;
    } else if (acceleration < 0 && basePosition != -(trackWidth / 2)) {
        baseAcceleration = acceleration;
    }
}

void Pendulum::stop() {
    baseAcceleration = 0;
}

void Pendulum::update(Time timePerFrame) {
    applyGravity(timePerFrame);
    updatePosition(timePerFrame);

    // Mettre à jour les positions des composants du pendule
    barPosition = Vector2f(trackPosition.x + basePosition, trackPosition.y);
    tipBallPosition = Vector2f(barPosition.x + length * sin(angle), barPosition.y + length * cos(angle));
}

void Pendulum::applyGravity(const Time &timePerFrame) {
    angularAcceleration = -gravity / length * sin(angle) - baseAcceleration / length * cos(angle) - damping / length * angularVelocity;
    angularVelocity += angularAcceleration * timePerFrame.asSeconds();
    angle += angularVelocity * timePerFrame.asSeconds();
}

void Pendulum::updatePosition(const Time &timePerFrame) {
    baseVelocity += baseAcceleration * timePerFrame.asSeconds();
    baseVelocity -= friction * baseVelocity * timePerFrame.asSeconds();
    basePosition += baseVelocity * timePerFrame.asSeconds();
    checkCollision();
}

void Pendulum::checkCollision() {
    if (basePosition < -(trackWidth / 2)) {
        basePosition = -(trackWidth / 2);
        baseAcceleration = 0;
        baseVelocity = 0;
    } else if (basePosition > trackWidth / 2) {
        basePosition = trackWidth / 2;
        baseAcceleration = 0;
        baseVelocity = 0;
    }
}

void Pendulum::draw(float fitness, int keyPressed, Mode mode) {
    if (render) {
        renderer.setPendulumInfo(barPosition, angle, baseAcceleration, tipBallPosition, fitness, keyPressed, mode);
    }
}

float Pendulum::getTipY() const {
    return tipBallPosition.y;
}

float Pendulum::getPosition() const {
    return basePosition;
}

float Pendulum::getAngularVelocity() const {
    return angularVelocity;
}

float Pendulum::getAngleCos() const {
    return cos(angle);
}

float Pendulum::getAngleSin() const {
    return sin(angle);
}

float Pendulum::getAcceleration() const {
    return baseAcceleration;
}

float Pendulum::getVelocity() const {
    return baseVelocity;
}

void Pendulum::askToRender(RenderWindow& window) {
    renderer.drawManualMode(window);
}
