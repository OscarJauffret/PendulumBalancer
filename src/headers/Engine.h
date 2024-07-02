//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_ENGINE_H
#define PENDULUMBALANCERAI_ENGINE_H

#include "../headers/Pendulum.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Engine {
private:
    // Window
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time timePerFrame;
    float yThreshold;
    int score;

    Pendulum pendulum;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate;

public:
    Engine();
    void resetGame();
    void input();
    void draw();
    void draw_inputs(string text);
    void run();

    void update_pendulum();
    int getScore();
    float getInputValue(int inputId);
};


#endif //PENDULUMBALANCERAI_ENGINE_H
