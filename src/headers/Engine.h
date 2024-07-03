//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_ENGINE_H
#define PENDULUMBALANCERAI_ENGINE_H

#include "../headers/Pendulum.h"
#include "../config/configuration.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Engine {
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time timePerFrame;

    float yThreshold;
    const float lengthThreshold = 0.8f;
    float timeAboveThreshold = 0;
    int score;

    Pendulum pendulum;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate;

    sf::Font font;

public:
    Engine();
    void resetGame();
    char input();
    void draw(char key);
    void draw_inputs(char key);
    void draw_score();
    void draw_threshold();
    void run();

    void update_pendulum();
    int getScore();
    float getInputValue(int inputId);

    void checkTipPosition();

    void incrementScore();
};


#endif //PENDULUMBALANCERAI_ENGINE_H
