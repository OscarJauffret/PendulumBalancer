//
// Created by oscar on 11/07/2024.
//
#ifndef PENDULUMBALANCERAI_CARD_HPP
#define PENDULUMBALANCERAI_CARD_HPP
#include <SFML/Graphics.hpp>
using namespace sf;

class Card {
public:
    static RectangleShape make(Vector2f position, Vector2f size, Color color, float outlineThickness, Color outlineColor) {
        RectangleShape card(size);
        card.setPosition(position);
        card.setFillColor(color);
        card.setOutlineThickness(outlineThickness);
        card.setOutlineColor(outlineColor);
        return card;
    }
};

#endif //PENDULUMBALANCERAI_CARD_HPP