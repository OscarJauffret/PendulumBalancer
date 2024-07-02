//
// Created by oscar on 02/07/2024.
//
#include "../headers/Engine.h"

void Engine::draw(char key, int score) {
    window.clear(Color::Black);
    pendulum.draw(window);
    draw_inputs(key);
    draw_score(score);
    draw_threshold();
    window.display();
}

void Engine::draw_inputs(char key) {
    RectangleShape rectangleInput;
    rectangleInput.setSize(Vector2f(100, 100));
    rectangleInput.setFillColor(Color(80, 80, 80));
    rectangleInput.setPosition(10, 10);
    window.draw(rectangleInput);

    sf::Text input_text;
    input_text.setFont(font);
    input_text.setString(key);
    input_text.setCharacterSize(80);
    input_text.setFillColor(Color::Black);
    input_text.setPosition(20, 20);
    window.draw(input_text);
}

void Engine::draw_score(int score) {

    sf::Text score_text;
    score_text.setFont(font);
    score_text.setString("Score: " + std::to_string(score));
    score_text.setCharacterSize(30);
    score_text.setFillColor(Color::White);
    score_text.setPosition(window.getSize().x / 2 - 100, 10);
    window.draw(score_text);
}

void Engine::draw_threshold() {
    sf::RectangleShape threshold;
    threshold.setSize(Vector2f(window.getSize().x, 5));
    threshold.setFillColor(Color::Red);
    threshold.setPosition(0, yThreshold);
    window.draw(threshold);
}