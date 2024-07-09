//
// Created by oscar on 07/07/2024.
//

#ifndef PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
#define PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
#include "../../config/configuration.h"
#include "shapeinitializer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using std::cerr; using std::endl;

class PendulumRenderer {
private:
    RenderWindow& window;
    Font font;
    RectangleShape bar;
    CircleShape baseBall;
    CircleShape tipBall;
    RectangleShape track;
    RectangleShape threshold;
    ShapeInitializer shapeInitializer;

    bool render;

public:
    explicit PendulumRenderer(RenderWindow &window, float yThreshold, Vector2f startPosition,
                              bool render);

    void draw(Vector2f barPosition, float angle, Vector2f tipBallPosition, int fitness, int keyPressed,
              Mode mode);
    void drawPendulum(Vector2f barPosition, float angle, Vector2f tipBallPosition);

    void draw_score(int fitness);
    void draw_inputs(int key, Mode mode);
};


#endif //PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
