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
    RectangleShape background;
    RectangleShape controlledInfoBackground;
    RectangleShape bar;
    CircleShape baseBall;
    CircleShape tipBall;
    RectangleShape track;
    RectangleShape threshold;
    ShapeInitializer shapeInitializer;

    Vector2f barPosition;
    float angle;
    Vector2f tipBallPosition;
    float fitness;
    int keyPressed;
    Mode mode;

public:
    PendulumRenderer();
    explicit PendulumRenderer(float yThreshold, Vector2f startPosition);
    void initializeShapes(float yThreshold, Vector2f startPosition);

    void setPendulumInfo(Vector2f barPos, float ang, Vector2f tipBallPos, float fit, int key, Mode m);

    Vector2f getBarPosition();

    void draw(RenderWindow &window, Font &font, bool isControlled);
    void drawPendulum(RenderWindow &window);

    void drawScore(RenderWindow &window, Font &font) const;
    void drawInputs(RenderWindow &window, Font &font);

    static void drawControlledInfo(RenderWindow &window, Font &font);
};


#endif //PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
