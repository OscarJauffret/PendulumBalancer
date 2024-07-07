//
// Created by oscar on 02/07/2024.
//

#include "./headers/Engine.h"
#include <filesystem>
#include <utility>



Engine::Engine(RenderWindow &window, Time timePerFrame, bool shouldRenderPendulum, Mode mode,
               Genome controllingAgent, int &fitness)
        : window(window),
          pendulum(Vector2f(config::window::width / 2, config::window::height / 2)),
          fitness(fitness), timePerFrame(timePerFrame), shouldRenderPendulum(shouldRenderPendulum), mode(mode),
          controllingAgent(std::move(controllingAgent)) {
    yThreshold = pendulum.getTrackPositionY() - pendulum.getPendulumLength() * lengthThreshold;

    if (!font.loadFromFile(config::assets::fontPath)) {
        cerr << "Failed to load font" << endl;
    }
}

void Engine::updatePendulum() {
    pendulum.update(timePerFrame);
}

int Engine::getScore() {
    return fitness;
}

int Engine::run() {
    clock.restart();
    timeSinceLastUpdate = Time::Zero;
    int key = 0;

    while (window.isOpen() && maxPossibleScore < config::score::timeLimit * config::window::fps) {
        Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            key = input();
            updatePendulum();

            checkTipPosition();
            incrementScore();
        }

        if (shouldRenderPendulum) {
            draw(key);
        }
    }
    return fitness;
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
        fitness++;
        timeAboveThreshold = 0;
    }
    maxPossibleScore++;
}

float Engine::getInputValue(int inputId) {
    switch (inputId) {
        case 0:
            return pendulum.getPosition() / (config::pendulum::dimensions::trackWidth / 2);    // Normalized position
        case 1:
            return pendulum.getAngleCos();          // Cosine of angle
        case 2:
            return pendulum.getAngleSin();          // Sine of angle
        case 3:
            return pendulum.getAngularVelocity() / 16;   // Angular velocity
        case 4:
            return pendulum.getAcceleration() / config::pendulum::acceleration;   // Normalized acceleration
        case 5:
            return pendulum.getVelocity() / 250;
        default:
            return 0.0f;
    }
}