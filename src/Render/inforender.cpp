//
// Created by oscar on 11/07/2024.
//

#include "headers/renderer.hpp"

void Renderer::drawInfoPanel(bool showBest) {
    drawInfoBackground();
    drawInfoText();
    drawInfoWidget(showBest);
}

void Renderer::drawInfoBackground() {
    RectangleShape background = Card::make(Vector2f(config::layout::info::originX, config::layout::info::originY),
                                          Vector2f(config::layout::info::width, config::layout::info::height),
                                          config::colors::layout::darkerBackgroundColor,
                                          config::layout::info::bgOutlineThickness,
                                          config::colors::layout::infoOutlineColor);
    window.draw(background);
}

void Renderer::drawInfoText() {
    Text text = getText("Show best agent", 15, config::colors::textColor,
                        Vector2<float>(config::layout::info::originX + 30, config::layout::info::originY + 22));
    text.setOrigin(0, text.getGlobalBounds().height / 2);
    window.draw(text);
}

void Renderer::drawInfoWidget(bool showBest) {
    CircleShape circle(config::layout::info::widgetRadius);
    circle.setFillColor(showBest ? config::colors::layout::activatedWidgetColor : config::colors::layout::deactivatedWidgetColor);
    circle.setPosition(config::layout::info::originX + 10, config::layout::info::originY + 20);
    window.draw(circle);
}