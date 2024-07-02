//
// Created by oscar on 02/07/2024.
//
#include "../headers/Engine.h"

void Engine::draw() {
    window.clear(Color::Black);
    pendulum.draw(window);
    window.display();
}