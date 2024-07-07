//
// Created by oscar on 07/07/2024.
//

#ifndef PENDULUMBALANCERAI_SHAPEINITIALIZER_HPP
#define PENDULUMBALANCERAI_SHAPEINITIALIZER_HPP

#include "../../config/configuration.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ShapeInitializer {
private:
    float yThreshold;
    Vector2f startPosition;

public:
    ShapeInitializer() = default;
    ShapeInitializer(float yThreshold, Vector2f startPosition);

    void initializeShapes(CircleShape &baseBall, CircleShape &tipBall, RectangleShape &track,
                          RectangleShape &threshold, RectangleShape &bar);

    static void initializeBall(CircleShape& ball, float radius, Color color, float outlineThickness, Color outlineColor, float positionX, float positionY);
    static void initializeRectangle(RectangleShape &rectangleShape, Vector2f size, Color fillColor, float outlineThickness, Color outlineColor, Vector2f position);
    void initializeBar(RectangleShape& bar);
};


#endif //PENDULUMBALANCERAI_SHAPEINITIALIZER_HPP
