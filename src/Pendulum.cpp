//
// Created by oscar on 02/07/2024.
//

#include "headers/Pendulum.h"
#define M_PI 3.14159265358979323846

using std::cout; using std::endl;

Pendulum::Pendulum(Vector2f startPosition) {
    // Initialize the pendulum with default values
    length = 100.0;
    angle = 0.0;
    angularVelocity = 0.0;
    angularAcceleration = 0.0;
    damping = 20.0;
    gravity = 400;
    friction = 2;

    trackPosition = startPosition;
    basePosition = 0.0;
    baseVelocity = 0.0;
    baseAcceleration = 0.0;

    // Initialize the pendulum's shape
    bar.setSize(Vector2f(5, length));
    bar.setFillColor(Color::White);
    bar.setOrigin(Vector2f(bar.getSize().x / 2, 0));
    bar.setPosition(trackPosition.x, trackPosition.y);

    tipBall.setRadius(10);
    tipBall.setFillColor(Color(208, 100, 75));
    tipBall.setOutlineThickness(3);
    tipBall.setOutlineColor(Color::White);
    tipBall.setOrigin(tipBall.getRadius(), tipBall.getRadius());
    tipBall.setPosition(bar.getPosition().x, bar.getPosition().y + bar.getSize().y);

    baseBall.setRadius(10);
    baseBall.setFillColor(Color(208, 100, 75));
    baseBall.setOutlineThickness(3);
    baseBall.setOutlineColor(Color::White);
    baseBall.setOrigin(baseBall.getRadius(), baseBall.getRadius());
    baseBall.setPosition(bar.getPosition().x, bar.getPosition().y);

    track.setSize(Vector2f(trackWidth, 5));
    track.setFillColor(Color::Black);
    track.setOutlineThickness(2);
    track.setOutlineColor(Color::White);
    track.setOrigin(Vector2f(track.getSize().x / 2, track.getSize().y / 2));
    track.setPosition(startPosition);
}

void Pendulum::moveLeft() {
    if (basePosition != -(trackWidth / 2)) {
        baseAcceleration = -500;
    }
}

void Pendulum::moveRight() {
    if (basePosition != trackWidth / 2) {
        baseAcceleration = 500;
    }
}

void Pendulum::stop() {
    baseAcceleration = 0;
}

void Pendulum::update(Time timePerFrame) {
    applyGravity(timePerFrame);
    updatePosition(timePerFrame);
    //updateAngle(timePerFrame);

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
    cout << "Angular velocity: " << angularVelocity << endl;
    angle += angularVelocity * timePerFrame.asSeconds();
}

void Pendulum::updatePosition(const Time &timePerFrame) {
    baseVelocity += baseAcceleration * timePerFrame.asSeconds();
    baseVelocity -= friction * baseVelocity * timePerFrame.asSeconds();
    cout << "Base velocity: " << baseVelocity << endl;
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

float Pendulum::getPosition() {
    return basePosition;
}

float Pendulum::getAngularVelocity() {
    return angularVelocity;
}

float Pendulum::getAngleCos() {
    return cos(angle);
}

float Pendulum::getAngleSin() {
    return sin(angle);
}

float Pendulum::getAcceleration() {
    return baseAcceleration;
}

float Pendulum::getVelocity() {
    return baseVelocity;
}