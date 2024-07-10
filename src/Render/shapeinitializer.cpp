#include "headers/shapeinitializer.hpp"
#include <iostream>

ShapeInitializer::ShapeInitializer(float yThreshold, Vector2f startPosition)
    : yThreshold(yThreshold), startPosition(startPosition) {
}

void ShapeInitializer::initializeShapes(CircleShape &baseBall, CircleShape &tipBall, RectangleShape &track,
                                        RectangleShape &threshold,
                                        RectangleShape &bar, RectangleShape &background, RectangleShape &controlledInfoBackground) {
    initializeBall(baseBall, config::pendulum::dimensions::ballRadius, config::colors::pendulum::ballColor,
                   config::pendulum::dimensions::ballOutlineThickness, config::colors::pendulum::ballOutlineColor,
                   startPosition.x, startPosition.y);

    initializeBall(tipBall, config::pendulum::dimensions::ballRadius,
                   config::colors::pendulum::ballColor, config::pendulum::dimensions::ballOutlineThickness,
                   config::colors::pendulum::ballOutlineColor,
                   startPosition.x, startPosition.y + config::pendulum::dimensions::length);

    Vector2f tSize = Vector2f(config::pendulum::dimensions::trackWidth, config::pendulum::dimensions::trackHeight);
    initializeRectangle(track, tSize, config::colors::pendulum::trackFillColor,
                        config::pendulum::dimensions::trackOutlineThickness,
                        config::colors::pendulum::trackOutlineColor, startPosition);
    initializeRectangle(threshold, tSize, config::colors::pendulum::thresholdColor,
                        0, Color(),
                        Vector2f(config::window::width / 2, yThreshold));

    initializeBar(bar);
    initializeRectangle(background, Vector2f(config::layout::pendulum::backgroundWidth, config::layout::pendulum::backgroundHeight),
                        config::colors::layout::darkerBackgroundColor, config::layout::pendulum::bgOutlineThickness,
                        config::colors::pendulum::bgOutlineColor, startPosition);

    initializeRectangle(controlledInfoBackground, Vector2f(config::layout::pendulum::controlledInfoBgWidth, config::layout::pendulum::controlledInfoBgHeight),
                        config::colors::layout::controlledInfoBgColor, 0,Color(),
                        Vector2f(config::layout::pendulum::originX + config::layout::pendulum::backgroundWidth / 2 - config::layout::pendulum::controlledInfoBgWidth / 2 - 5,
                                 config::layout::pendulum::originY - config::layout::pendulum::backgroundHeight / 2 + config::layout::pendulum::controlledInfoBgHeight / 2 + 5));
}

void ShapeInitializer::initializeBall(CircleShape &ball, float radius, Color color, float outlineThickness, Color outlineColor,
                                      float positionX, float positionY) {
    ball.setRadius(radius);
    ball.setFillColor(color);
    ball.setOutlineThickness(outlineThickness);
    ball.setOutlineColor(outlineColor);
    ball.setOrigin(radius, radius);
    ball.setPosition(positionX, positionY);
}

void ShapeInitializer::initializeRectangle(RectangleShape &rectangleShape, Vector2f size, Color fillColor,
                                           float outlineThickness, Color outlineColor, Vector2f position) {
    rectangleShape.setSize(size);
    rectangleShape.setFillColor(fillColor);
    rectangleShape.setOutlineThickness(outlineThickness);
    rectangleShape.setOutlineColor(outlineColor);
    rectangleShape.setOrigin(Vector2f(size.x / 2, size.y / 2));
    rectangleShape.setPosition(position);
}

void ShapeInitializer::initializeBar(RectangleShape &bar) {
    bar.setSize(Vector2f(config::pendulum::dimensions::barWidth, config::pendulum::dimensions::length));
    bar.setFillColor(config::colors::pendulum::barColor);
    bar.setOrigin(Vector2f(bar.getSize().x / 2, 0));
    bar.setPosition(startPosition);
}
