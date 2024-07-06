#include "../headers/Pendulum.h"

void Pendulum::initializeShape(const Vector2f &startPosition) {
    initializeBar();
    initializeBalls();
    initializeTrack(startPosition);
}

void Pendulum::initializeBalls() {
    initializeBall(tipBall, config::pendulum::dimensions::ballRadius,
                   config::colors::pendulum::ballColor, config::pendulum::dimensions::ballOutlineThickness,
                   config::colors::pendulum::ballOutlineColor,
                   bar.getPosition().x, bar.getPosition().y + bar.getSize().y);

    initializeBall(baseBall, config::pendulum::dimensions::ballRadius, config::colors::pendulum::ballColor,
                   config::pendulum::dimensions::ballOutlineThickness, config::colors::pendulum::ballOutlineColor,
                   bar.getPosition().x, bar.getPosition().y);
}

void Pendulum::initializeTrack(const Vector2f &startPosition) {
    track.setSize(Vector2f(trackWidth, config::pendulum::dimensions::trackHeight));
    track.setFillColor(config::colors::pendulum::trackFillColor);
    track.setOutlineThickness(config::pendulum::dimensions::trackOutlineThickness);
    track.setOutlineColor(config::colors::pendulum::trackOutlineColor);
    track.setOrigin(Vector2f(track.getSize().x / 2, track.getSize().y / 2));
    track.setPosition(startPosition);
}

void Pendulum::initializeBall(CircleShape& ball, float radius, Color color, float outlineThickness, Color outlineColor,
                              float positionX, float positionY) {
    ball.setRadius(radius);
    ball.setFillColor(color);
    ball.setOutlineThickness(outlineThickness);
    ball.setOutlineColor(outlineColor);
    ball.setOrigin(tipBall.getRadius(), tipBall.getRadius());
    ball.setPosition(positionX, positionY);
}

void Pendulum::initializeBar() {
    bar.setSize(Vector2f(config::pendulum::dimensions::barWidth, length));
    bar.setFillColor(config::colors::pendulum::barColor);
    bar.setOrigin(Vector2f(bar.getSize().x / 2, 0));
    bar.setPosition(trackPosition.x, trackPosition.y);
}
