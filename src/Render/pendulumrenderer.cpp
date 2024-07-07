//
// Created by oscar on 07/07/2024.
//

#include "headers/pendulumrenderer.hpp"

PendulumRenderer::PendulumRenderer(RenderWindow &window, float yThreshold, Vector2f startPosition)
        : window(window), yThreshold(yThreshold), startPosition(startPosition) {
    if (!font.loadFromFile(config::assets::fontPath)) {
        cerr << "Failed to load font" << endl;
    }
}

void PendulumRenderer::draw(float trackPositionY, float tipY, float angle, float pendulumLength) {
    window.clear(config::colors::pendulum::backgroundColor);
    drawTrack();
    draw_threshold();
    drawPendulum(tipY, trackPositionY, angle, pendulumLength);
    draw_score(0);
    draw_inputs(0, Mode::Manual);
    window.display();
}

void PendulumRenderer::drawTrack() {
    sf::RectangleShape track;
    Vector2f tSize = Vector2f(config::pendulum::dimensions::trackWidth , config::pendulum::dimensions::trackHeight);
    track.setSize(tSize);
    track.setFillColor(config::colors::pendulum::trackOutlineColor);
    track.setOrigin(Vector2f(tSize.x / 2, tSize.y / 2));
    track.setPosition(startPosition);
    window.draw(track);
}

void PendulumRenderer::draw_threshold() {
    sf::RectangleShape threshold;
    Vector2f tSize = Vector2f(config::pendulum::dimensions::trackWidth , config::pendulum::dimensions::trackHeight);
    threshold.setSize(tSize);
    threshold.setFillColor(config::colors::pendulum::thresholdColor);
    threshold.setOrigin(Vector2f(tSize.x / 2, tSize.y / 2));
    threshold.setPosition(config::window::width / 2, yThreshold);
    window.draw(threshold);
}

void PendulumRenderer::draw_score(int fitness) {
    sf::Text score_text;
    score_text.setFont(font);
    score_text.setString("Score: " + std::to_string(fitness));
    score_text.setCharacterSize(30);
    score_text.setFillColor(Color::White);
    score_text.setPosition(config::window::width / 2 - 100, 10);
    window.draw(score_text);
}

void PendulumRenderer::draw_inputs(int key, Mode mode) {
    RectangleShape rectangleInput;
    rectangleInput.setSize(Vector2f(150, 100));
    rectangleInput.setFillColor(config::colors::inputRectColor);
    rectangleInput.setPosition(10, 10);
    window.draw(rectangleInput);

    string input;
    if (mode == Mode::Manual) {
        input = static_cast<char>(key);
    } else {
        input = std::to_string(key);
    }
    sf::Text input_text;
    input_text.setFont(font);
    input_text.setString(input);
    input_text.setCharacterSize(80);
    input_text.setFillColor(Color::Black);
    input_text.setPosition(20, 20);
    window.draw(input_text);
}