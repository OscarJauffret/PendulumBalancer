//
// Created by oscar on 07/07/2024.
//

#ifndef PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
#define PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
#include "../../config/configuration.h"
#include "shapeinitializer.hpp"
#include "card.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>
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

    deque<float> accelerations;
    VertexArray accelerationLine;

public:
    PendulumRenderer();
    explicit PendulumRenderer(float yThreshold, Vector2f startPosition);
    void initializeShapes(float yThreshold, Vector2f startPosition);

    void resetAccelerations();
    void setPendulumInfo(Vector2f barPos, float ang, float accel, Vector2f tipBallPos, float fit, int key, Mode m);

    void draw(RenderWindow &window, Font &font, bool isControlled);
    void drawPendulum(RenderWindow &window);
    void drawScale(RenderWindow &window, Font &font);
    void drawScore(RenderWindow &window, Font &font) const;

    static void drawControlledInfo(RenderWindow &window, Font &font);

    void drawAccelerationChart(RenderWindow& window, Font& font);
    void drawAccelerationChartBackground(RenderWindow &window);
    void drawAccelerationScaleLines(RenderWindow &window);
    void updateAccelerationLine();
    void drawAccelerationText(RenderWindow &window, Font &font);

    void drawManualMode(RenderWindow &window);
};


#endif //PENDULUMBALANCERAI_PENDULUMRENDERER_HPP
