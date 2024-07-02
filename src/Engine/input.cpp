//
// Created by oscar on 02/07/2024.
//
#include "../headers/Engine.h"


char Engine::input() {
    Event event{};
    bool keyWasPressed = false;
    char key = ' ';
    while (window.pollEvent(event)) {
        // Window closed
        if (event.type == Event::Closed) {
            window.close();
        }

        // Keyboard input
        if (event.type == Event::KeyPressed) {
            keyWasPressed = true;
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pendulum.moveLeft();
        keyWasPressed = true;
        key = 'L';
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pendulum.moveRight();
        keyWasPressed = true;
        key = 'R';
    }

    if (!keyWasPressed) {
        pendulum.stop();
    }
    return key;
}