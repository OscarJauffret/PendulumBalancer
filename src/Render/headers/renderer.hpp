//
// Created by oscar on 06/07/2024.
//

#ifndef PENDULUMBALANCERAI_RENDERER_HPP
#define PENDULUMBALANCERAI_RENDERER_HPP

#include "../../config/configuration.h"
#include "button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class renderer {
    Vector2i resolution;
    RenderWindow window;
    const unsigned int FPS = config::window::fps;
    static const Time timePerFrame;

    Font font;
public:
    renderer();
    Mode askMode();
    Button createModeButton(bool isManualButton);

    RenderWindow& getWindow();
    Time getTimePerFrame();

};


#endif //PENDULUMBALANCERAI_RENDERER_HPP
