//
// Created by oscar on 02/07/2024.
//

#ifndef PENDULUMBALANCERAI_ENGINE_H
#define PENDULUMBALANCERAI_ENGINE_H

#include "Pendulum.h"
#include "../../config/configuration.h"
#include "../../Network/headers/genetic.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Engine {
private:
    RenderWindow& window;
    Time timePerFrame;

    Mode mode;
    Genome controllingAgent;

    float yThreshold;
    const float lengthThreshold = config::score::lengthThreshold;
    float timeAboveThreshold = 0;

    int& fitness;
    int maxPossibleScore = 0;

    Pendulum pendulum;
    bool shouldRenderPendulum;

    Clock clock;
    Time timeSinceLastUpdate;

    Font font;

public:
    Engine(RenderWindow &window, Time timePerFrame, bool shouldRenderPendulum, Mode mode,
           Genome controllingAgent, int &fitness);

    int input();
    int userInput();
    int AiInput();

    void draw(int key);
    void draw_inputs(int key);
    void draw_score();
    void draw_threshold();
    int run();

    void updatePendulum();
    int getScore();
    float getInputValue(int inputId);

    void checkTipPosition();

    void incrementScore();

    void handleWindowClosed(const Event &event);

    int handleMovement();
};


#endif //PENDULUMBALANCERAI_ENGINE_H
