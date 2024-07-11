//
// Created by oscar on 02/07/2024.
//

#include "./headers/Engine.h"
#include <filesystem>
#include <utility>



Engine::Engine(RenderWindow &window, Time timePerFrame, Mode mode, Genome controllingAgent, float &fitness,
               bool shouldRenderPendulum, PendulumRenderer &pendRenderer)
        : window(window),
          yThreshold(config::score::yThreshold),
          pendulum(window, Vector2f(config::layout::pendulum::originX, config::layout::pendulum::originY), shouldRenderPendulum,
                   pendRenderer),
          fitness(fitness), timePerFrame(timePerFrame), mode(mode),
          controllingAgent(std::move(controllingAgent)) {
    if (!font.loadFromFile(config::assets::fontPath)) {
        cerr << "Failed to load font" << endl;
    }
}

void Engine::updatePendulum() {
    pendulum.update(timePerFrame);
}

float Engine::run(float accelerationFactor) {
    clock.restart();
    timeSinceLastUpdate = Time::Zero;
    int key = 0;
    framesElapsed = 0;

    while (window.isOpen() && framesElapsed < config::score::timeLimit * config::window::fps) {
        Time dt = clock.restart();  // Restart the clock and return the time elapsed since the last restart
        dt *= accelerationFactor;
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > timePerFrame) {
            if (framesElapsed >= config::score::timeLimit * config::window::fps) {
                break;
            }
            timeSinceLastUpdate -= timePerFrame;

            key = input();
            updatePendulum();

            checkTipPosition();
            incrementFitness();
            framesElapsed++;
        }

        pendulum.draw(fitness, key, mode);
    }
    if (framesElapsed != 1800) {
        cout << "Agent played for " << framesElapsed << " frames" << endl;
    }
    return fitness;
}

void Engine::checkTipPosition() {
    const float adjustedTimePerFrame = timePerFrame.asSeconds();
    if (pendulum.getTipY() < yThreshold) {
        timeAboveThreshold += adjustedTimePerFrame;
    } else {
        timeAboveThreshold = 0;
    }
}

void Engine::incrementFitness() {
    if (timeAboveThreshold > config::score::timeAboveThresholdToScore) {
        float distanceFromCenter = abs(pendulum.getPosition()) / (config::pendulum::dimensions::trackWidth / 2);
        float positionFactor = 1.0f/(distanceFromCenter + 1);
        float velocityFactor = 1.0f/(abs(pendulum.getAngularVelocity()) + 1);
        fitness += positionFactor * velocityFactor;
        timeAboveThreshold = 0;
    }
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
