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
    float timeAboveThreshold = 0;

    float& fitness;
    int framesElapsed = 0;

    Pendulum pendulum;

    Clock clock;
    Time timeSinceLastUpdate;

    Font font;

public:
    Engine(RenderWindow &window, Time timePerFrame, Mode mode, Genome controllingAgent, float &fitness,
           bool shouldRenderPendulum, PendulumRenderer &pendRenderer);

    int input();
    int userInput();
    int AiInput();

    float run(float accelerationFactor);
    void updatePendulum();
    float getInputValue(int inputId);
    void checkTipPosition(float accelerationFactor);
    void incrementFitness();

    void handleWindowClosed(const Event &event);
    int handleMovement();
};


#endif //PENDULUMBALANCERAI_ENGINE_H
