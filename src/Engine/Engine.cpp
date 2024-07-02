//
// Created by oscar on 02/07/2024.
//

#include "../headers/Engine.h"


const sf::Time Engine::timePerFrame = sf::seconds(1.f/60.f);

Engine::Engine(): resolution(800, 600), window(VideoMode(resolution.x, resolution.y), "Pendulum Balancer", Style::Default),
          pendulum(Vector2f(window.getSize().x / 2, window.getSize().y / 2)), score(0) {
    window.setFramerateLimit(FPS);
    yThreshold = window.getSize().y / 2 - pendulum.getPendulumLength() / 2;
}

void Engine::update_pendulum() {
    pendulum.update(timePerFrame);
}

void Engine::resetGame() {
    Engine();
}

int Engine::getScore() {
    return score;
}

void Engine::run() {
    clock.restart();
    timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            input();
            update_pendulum();

            // Vérifier la position du pendule
            if (pendulum.getTipY() < yThreshold) {
                score++;
                cout << "Score: " << score << endl;
            }
        }

        draw();
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