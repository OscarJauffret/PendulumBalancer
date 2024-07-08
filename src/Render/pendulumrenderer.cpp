//
// Created by oscar on 07/07/2024.
//

#include "headers/pendulumrenderer.hpp"
#include "headers/shapeinitializer.hpp"

PendulumRenderer::PendulumRenderer(RenderWindow &window, float yThreshold, Vector2f startPosition,
                                   bool render)
        : window(window), yThreshold(yThreshold), startPosition(startPosition), render(render) {
    if (!font.loadFromFile(config::assets::fontPath)) {
        cerr << "Failed to load font" << endl;
    }
    shapeInitializer = ShapeInitializer(yThreshold, startPosition);
    shapeInitializer.initializeShapes(baseBall, tipBall, track, threshold, bar);

}

void PendulumRenderer::draw(Vector2f barPosition, float angle, Vector2f tipBallPosition, int fitness, int keyPressed,
                            Mode mode) {
    if (!render) {
        return;
    }
    window.clear(config::colors::layout::backgroundColor);
    window.draw(track);
    window.draw(threshold);
    drawPendulum(barPosition, angle, tipBallPosition);
    draw_score(fitness);
    draw_inputs(keyPressed, mode);
    window.display();
}

void PendulumRenderer::drawPendulum(Vector2f barPosition, float angle, Vector2f tipBallPosition) {
    bar.setPosition(barPosition);
    bar.setRotation(-(float) angle * 180 / M_PI);
    window.draw(bar);

    baseBall.setPosition(barPosition);
    window.draw(baseBall);

    tipBall.setPosition(tipBallPosition);
    window.draw(tipBall);
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
    rectangleInput.setFillColor(config::colors::layout::inputRectColor);
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

