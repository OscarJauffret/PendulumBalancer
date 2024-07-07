//
// Created by oscar on 07/07/2024.
//

#ifndef PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
#define PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
#include "../../config/configuration.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using std::cerr; using std::endl;

class PendulumRenderer {
    RenderWindow& window;

    float yThreshold;
    Vector2f startPosition;

    Font font;

public:
    explicit PendulumRenderer(RenderWindow &window, float yThreshold, Vector2f startPosition);
    void draw(float trackPositionY, float tipY, float angle, float pendulumLength);
    void drawTrack();
    void drawPendulum(float tipY, float trackPositionY, float angle, float pendulumLength);
    void draw_threshold();
    void draw_score(int fitness);
    void draw_inputs(int key, Mode mode);
};


#endif //PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
