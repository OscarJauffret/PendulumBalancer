//
// Created by oscar on 07/07/2024.
//

#include <format>
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
    drawScale(window, font);
    drawPendulum(window);
    drawScore(window, font);
    drawAccelerationChart(window, font);
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
    score_text.setString("Score: " + std::format("{:.2f}", fitness));
    score_text.setCharacterSize(30);
    score_text.setFillColor(Color::White);
    const float xPadding = 10;
    const float yPadding = 5;
    Vector2f position = Vector2f(config::layout::pendulum::originX - config::layout::pendulum::backgroundWidth / 2 + xPadding,
                                 config::layout::pendulum::originY - config::layout::pendulum::backgroundHeight / 2 + yPadding);
    score_text.setPosition(position);
    window.draw(score_text);
}

void PendulumRenderer::drawScale(RenderWindow &window, Font &font) {
    float baseX = track.getPosition().x;
    int distance = -config::pendulum::dimensions::trackWidth / 2;
    while (static_cast<float>(distance) <= config::pendulum::dimensions::trackWidth / 2) {
        Color color = config::colors::layout::backgroundColor;
        if (distance % 100 == 0) {
            color = config::colors::layout::scoreOutlineColor;
            sf::Text scale;
            scale.setFont(font);
            scale.setString(std::to_string(distance));
            scale.setCharacterSize(distance == 0 ? 30 : 20);
            scale.setFillColor(Color::White);
            scale.setOrigin(scale.getLocalBounds().width / 2 + (distance == 0 ? 2 : 0), scale.getLocalBounds().height / 2);
            scale.setPosition(baseX + static_cast<float>(distance), config::layout::pendulum::originY + 70);
            window.draw(scale);
        }
        RectangleShape r(distance % 100 == 0 ? Vector2f(1, 20) : Vector2f(1, 10));
        r.setOrigin(0, r.getSize().y / 2);
        r.setFillColor(color);
        r.setPosition(baseX + static_cast<float>(distance), config::layout::pendulum::originY + 50);
        window.draw(r);
        distance += 10;
    }

}

void PendulumRenderer::resetAccelerations() {
    accelerations.clear();
}

void PendulumRenderer::setPendulumInfo(Vector2f barPos, float ang, float accel, Vector2f tipBallPos, float fit, int key,
                                       Mode m) {
    this->barPosition = barPos;
    this->angle = ang;
    this->accelerations.emplace_back(accel);
    if (this->accelerations.size() > 100) {
        this->accelerations.pop_front();
    }
    this->tipBallPosition = tipBallPos;
    this->fitness = fit;
    this->keyPressed = key;
    this->mode = m;
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

void PendulumRenderer::drawAccelerationChart(RenderWindow &window, Font &font) {
    drawAccelerationChartBackground(window);
    drawAccelerationScaleLines(window);
    updateAccelerationLine();
    window.draw(accelerationLine);
    drawAccelerationText(window, font);
}

void PendulumRenderer::drawAccelerationChartBackground(RenderWindow &window) {
    RectangleShape bg = Card::make(Vector2f(config::layout::pendulum::accel::originX, config::layout::pendulum::accel::originY),
                                   Vector2f(config::layout::pendulum::accel::width, config::layout::pendulum::accel::height),
                                   config::colors::layout::darkerBackgroundColor, config::layout::pendulum::accel::bgOutlineThickness,
                                   config::colors::layout::accelChartOutlineColor);
    window.draw(bg);
}

void PendulumRenderer::drawAccelerationScaleLines(RenderWindow& window) {
    float x = config::layout::pendulum::accel::originX;
    float y = config::layout::pendulum::accel::originY;
    float width = config::layout::pendulum::accel::width - config::layout::pendulum::accel::rightPadding;
    float height = config::layout::pendulum::accel::height;
    for (int i = 0; i < 10; i++) {
        RectangleShape line(Vector2<float>(width, 1));
        line.setPosition(x, y + i * height / 10);
        line.setFillColor(config::colors::layout::backgroundColor);
        window.draw(line);
    }
    for (int i = 0; i < 10; i++) {
        RectangleShape line(Vector2<float>(1, height));
        line.setPosition(x + i * width / 10, y);
        line.setFillColor(config::colors::layout::backgroundColor);
        window.draw(line);
    }
}

void PendulumRenderer::updateAccelerationLine() {
    constexpr float x = config::layout::pendulum::accel::originX;
    constexpr float y = config::layout::pendulum::accel::originY;
    constexpr float width = config::layout::pendulum::accel::width - config::layout::pendulum::accel::rightPadding;
    constexpr float height = config::layout::pendulum::accel::height;
    constexpr float maxAccel = config::pendulum::acceleration;
    constexpr float minAccel = -maxAccel;

    accelerationLine.clear();
    accelerationLine.setPrimitiveType(LineStrip);

    for (size_t i = 0; i < accelerations.size(); ++i) {
        float accel = accelerations[i];
        float yPos = height - ((accel + maxAccel) / (maxAccel - minAccel)) * height;
        float xPos = x + (i * width / accelerations.size());
        accelerationLine.append(Vertex(Vector2f(xPos, y + yPos), config::colors::layout::accelChartOutlineColor));
    }
}

void PendulumRenderer::drawAccelerationText(sf::RenderWindow &window, sf::Font &font) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(config::colors::textColor);
    text.setPosition(config::layout::pendulum::accel::originX + 5, config::layout::pendulum::accel::originY + 5);
    text.setString("Acceleration over time");
    window.draw(text);
    text.setOrigin(0, text.getLocalBounds().height / 2);
    text.setPosition(config::layout::pendulum::accel::originX + config::layout::pendulum::accel::width - config::layout::pendulum::accel::rightPadding + 10.0f,
                     config::layout::pendulum::accel::originY + config::layout::pendulum::accel::height / 2 - 2);
    text.setString("0");
    window.draw(text);
    text.setPosition(config::layout::pendulum::accel::originX + config::layout::pendulum::accel::width - config::layout::pendulum::accel::rightPadding + 10.0f,
                     config::layout::pendulum::accel::originY + 5);
    text.setString(std::format("{:.0f}", config::pendulum::acceleration));
    window.draw(text);
    text.setPosition(config::layout::pendulum::accel::originX + config::layout::pendulum::accel::width - config::layout::pendulum::accel::rightPadding + 10.0f,
                     config::layout::pendulum::accel::originY + config::layout::pendulum::accel::height - 5);
    text.setString(std::format("{:.0f}", -config::pendulum::acceleration));
    window.draw(text);
}

void PendulumRenderer::drawManualMode(RenderWindow &window) {
    window.clear(config::colors::layout::backgroundColor);
    window.draw(background);
    window.draw(track);
    window.draw(threshold);
    drawPendulum(window);
    window.display();
}
