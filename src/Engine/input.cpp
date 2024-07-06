//
// Created by oscar on 02/07/2024.
//
#include "./headers/Engine.h"


int Engine::input() {
    return mode == Mode::Manual ? userInput() : AiInput();
}

int Engine::userInput() {
    Event event{};
    while (window.pollEvent(event)) {
        handleWindowClosed(event);
    }

    int key = handleMovement();
    if (!key) {
        pendulum.stop();
    }

    return key;
}

int Engine::handleMovement() {
    int key = 0;
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        pendulum.moveLeft();
        key = 76;   // ASCII code for 'L'
    } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        pendulum.moveRight();
        key = 82;   // ASCII code for 'R'
    }
    return key;
}

void Engine::handleWindowClosed(const Event &event) {
    if (event.type == Event::Closed) {
        window.close();
    }
    // Keyboard input
    if (event.type == Event::KeyPressed) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
    }
}

int Engine::AiInput() {
    vector<float> inputs = {};
    for (int i = 0; i < 6; i++) {
        inputs.push_back(getInputValue(i));
    }
    double accelerationPercentage = controllingAgent.predict(inputs);
    float acceleration = accelerationPercentage * (int) config::pendulum::acceleration;

    pendulum.setAcceleration(acceleration);
    return (int) acceleration;
}