//
// Created by oscar on 07/07/2024.
//

#include "headers/pendulumrenderer.hpp"
#include "headers/shapeinitializer.hpp"

PendulumRenderer::PendulumRenderer() {
    angle = 0;
    fitness = 0;
    keyPressed = 0;
    mode = Mode::Manual;
}

PendulumRenderer::PendulumRenderer(float yThreshold, Vector2f startPosition) {
    initializeShapes(yThreshold, startPosition);
}

void PendulumRenderer::initializeShapes(float yThreshold, sf::Vector2f startPosition) {
    shapeInitializer = ShapeInitializer(yThreshold, startPosition);
    barPosition = startPosition;
    tipBallPosition = Vector2f(startPosition.x, startPosition.y + config::pendulum::dimensions::length);
    shapeInitializer.initializeShapes(baseBall, tipBall, track, threshold, bar, background, controlledInfoBackground);
}

void PendulumRenderer::draw(RenderWindow &window, Font &font, bool isControlled) {
    window.draw(background);
    if (isControlled) {
        window.draw(controlledInfoBackground);
        drawControlledInfo(window, font);
    }
    window.draw(track);
    window.draw(threshold);
    drawPendulum(window);
    drawScore(window, font);
}

void PendulumRenderer::drawPendulum(RenderWindow &window) {
    bar.setPosition(barPosition);
    bar.setRotation(-(float) angle * 180 / M_PI);
    window.draw(bar);

    baseBall.setPosition(barPosition);
    window.draw(baseBall);

    tipBall.setPosition(tipBallPosition);
    window.draw(tipBall);
}

void PendulumRenderer::drawScore(RenderWindow &window, Font &font) const {
    sf::Text score_text;
    score_text.setFont(font);
    score_text.setString("Score: " + std::to_string(fitness));
    score_text.setCharacterSize(30);
    score_text.setFillColor(Color::White);
    const float xPadding = 10;
    const float yPadding = 5;
    Vector2f position = Vector2f(config::layout::pendulum::originX - config::layout::pendulum::backgroundWidth / 2 + xPadding,
                                 config::layout::pendulum::originY - config::layout::pendulum::backgroundHeight / 2 + yPadding);
    score_text.setPosition(position);
    window.draw(score_text);
}

void PendulumRenderer::drawInputs(RenderWindow &window, Font &font) {
    RectangleShape rectangleInput;
    rectangleInput.setSize(Vector2f(150, 100));
    rectangleInput.setFillColor(Color::Transparent);
    rectangleInput.setPosition(10, 10);
    window.draw(rectangleInput);

    string input;
    if (mode == Mode::Manual) {
        input = static_cast<char>(keyPressed);
    } else {
        input = std::to_string(keyPressed);
    }
    sf::Text input_text;
    input_text.setFont(font);
    input_text.setString(input);
    input_text.setCharacterSize(80);
    input_text.setFillColor(Color::Black);
    input_text.setPosition(20, 20);
    window.draw(input_text);
}

void PendulumRenderer::setPendulumInfo(Vector2f barPos, float ang, Vector2f tipBallPos, int fit,
                                       int key, Mode m) {
    this->barPosition = barPos;
    this->angle = ang;
    this->tipBallPosition = tipBallPos;
    this->fitness = fit;
    this->keyPressed = key;
    this->mode = m;
}

Vector2f PendulumRenderer::getBarPosition() {
    return barPosition;
}

void PendulumRenderer::drawControlledInfo(RenderWindow &window, Font &font) {
    sf::Text cText;
    cText.setFont(font);
    cText.setString("Controlled");
    cText.setCharacterSize(20);
    cText.setStyle(Text::Bold);
    cText.setFillColor(config::colors::textColor);
    cText.setOrigin(cText.getLocalBounds().width / 2, cText.getLocalBounds().height / 2);
    cText.setPosition(config::layout::pendulum::originX + config::layout::pendulum::backgroundWidth / 2 -
                                   config::layout::pendulum::controlledInfoBgWidth / 2 - 5,
                                   config::layout::pendulum::originY - config::layout::pendulum::backgroundHeight / 2 +
                                   config::layout::pendulum::controlledInfoBgHeight / 2);
    window.draw(cText);
}
