//
// Created by oscar on 02/07/2024.
//

#include "../headers/Pendulum.h"

#define M_PI 3.14159265358979323846

using std::cout; using std::endl;

Pendulum::Pendulum(Vector2f startPosition) {
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

    initializeShape(startPosition);

}

float Pendulum::getTrackPositionY() const {
    return trackPosition.y;

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

void Pendulum::stop() {
    baseAcceleration = 0;
}

void Pendulum::update(Time timePerFrame) {
    applyGravity(timePerFrame);
    updatePosition(timePerFrame);

    // Mettre à jour les positions des composants du pendule
    bar.setRotation(-angle * 180 / M_PI);
    bar.setPosition(Vector2f(trackPosition.x + basePosition, trackPosition.y));
    baseBall.setPosition(bar.getPosition().x, bar.getPosition().y);
    tipBall.setPosition(baseBall.getPosition().x + length * sin(angle),
                        baseBall.getPosition().y + length * cos(angle));
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

void Pendulum::draw(RenderWindow& window) {
    window.draw(track);
    window.draw(bar);
    window.draw(tipBall);
    window.draw(baseBall);
}

float Pendulum::getTipY() const {
    return tipBall.getPosition().y;
}

float Pendulum::getPendulumLength() const {
    return length;
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