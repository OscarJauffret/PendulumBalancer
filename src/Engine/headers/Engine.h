//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_ENGINE_H
#define PENDULUMBALANCERAI_ENGINE_H

#include "Pendulum.h"
#include "../../config/configuration.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Engine {
private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = config::window::fps;
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

    int input(Mode mode);
    int userInput();
    int AiInput();

    void draw(int key);
    void draw_inputs(int key);
    void draw_score();
    void draw_threshold();
    void run(Mode mode);

    void updatePendulum();
    int getScore();
    float getInputValue(int inputId);

    void checkTipPosition();

    void incrementScore();

    void handleWindowClosed(const Event &event);

    int handleMovement();
};


#endif //PENDULUMBALANCERAI_ENGINE_H
