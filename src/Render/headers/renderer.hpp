//
// Created by oscar on 06/07/2024.
//

#ifndef PENDULUMBALANCERAI_RENDERER_HPP
#define PENDULUMBALANCERAI_RENDERER_HPP

#include "../../config/configuration.h"
#include "button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>

using namespace sf;
using namespace std;

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

    void drawScoresChart(const deque<int> &scores);

    RenderWindow& getWindow();
    Time getTimePerFrame();

    void drawScoresBackground();
    void drawScoresLines(const deque<int> &scores);
};


#endif //PENDULUMBALANCERAI_RENDERER_HPP
