//
// Created by oscar on 02/07/2024.
//
#include "../headers/Engine.h"


void Engine::input() {
    Event event{};
    bool keyWasPressed = false;
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
        // draw_inputs("L");
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pendulum.moveRight();
        keyWasPressed = true;
        // draw_inputs("R");
    }

    if (!keyWasPressed) {
        pendulum.stop();
    }
}

void Engine::draw_inputs(string text) {
    RectangleShape input;
    input.setSize(Vector2f(100, 100));
    input.setFillColor(Color(80, 80, 80));
    input.setPosition(10, 10);
    window.draw(input);

    sf::Font font;
    if (!font.loadFromFile("src/assets/Roboto-regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    sf::Text input_text;
    input_text.setFont(font);
    input_text.setString(text);
    input_text.setCharacterSize(24);
    input_text.setFillColor(Color::Black);
    input_text.setPosition(20, 20);
    window.draw(input_text);
}