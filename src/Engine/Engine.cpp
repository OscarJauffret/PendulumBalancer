//
// Created by oscar on 02/07/2024.
//

#include "./headers/Engine.h"
#include <filesystem>


const sf::Time Engine::timePerFrame = sf::seconds(1.f/60.f);

Engine::Engine(): resolution(config::window::width, config::window::height), window(VideoMode(resolution.x, resolution.y), "Pendulum Balancer", Style::Default, sf::ContextSettings(0, 0, 8)),
          pendulum(Vector2f(window.getSize().x / 2, window.getSize().y / 2)), score(0) {
    window.setFramerateLimit(FPS);
    yThreshold = pendulum.getTrackPositionY() - pendulum.getPendulumLength() * lengthThreshold;
    if (!font.loadFromFile(config::assets::fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

void Engine::updatePendulum() {
    pendulum.update(timePerFrame);
}

void Engine::resetGame() {
    Engine();
}

int Engine::getScore() {
    return score;
}

void Engine::run(Mode mode) {
    clock.restart();
    timeSinceLastUpdate = sf::Time::Zero;
    int key = 0;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            key = input(mode);
            updatePendulum();

            checkTipPosition();
            incrementScore();
        }

        draw(key);
    }
}

void Engine::checkTipPosition() {
    if (pendulum.getTipY() < yThreshold) {
        timeAboveThreshold += timePerFrame.asSeconds();
    } else {
        timeAboveThreshold = 0;
    }
}

void Engine::incrementScore() {
    if (timeAboveThreshold > 1) {
        score++;
        timeAboveThreshold = 0;
    }
}

float Engine::getInputValue(int inputId) {
    switch (inputId) {
        case 1:
            return pendulum.getPosition();
        case 2:
            return pendulum.getAngleCos();
        case 3:
            return pendulum.getAngleSin();
        case 4:
            return pendulum.getAngularVelocity();
        case 5:
            return pendulum.getAcceleration();
        case 6:
            return pendulum.getVelocity();
        default:
            return 0.0f;
    }
}