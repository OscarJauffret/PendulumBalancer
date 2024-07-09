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
using namespace std;

class Renderer {
    Vector2i resolution;
    RenderWindow window;
    const unsigned int FPS = config::window::fps;
    static const Time timePerFrame;

    Font font;
public:
    Renderer();
    Mode askMode();
    Button createModeButton(bool isManualButton);

    RenderWindow& getWindow();

    Time getTimePerFrame();

    void drawGeneration(int generation, long long elapsedTime);
    void drawGenerationText(int generation);
    void drawRealTime(long long int timeElapsed);
    void drawVirtualTime(int generation);
    string formatTime(long long int seconds);

    void drawScoresChart(const vector<int> &scores);
    void drawScoresBackground();
    void drawScoresText();
    void drawScaleLines();
    void drawScoresLines(vector<int> scores);

    Text getText(const string& text, int charSize, Color color, Vector2f position) const;

    void drawGenerationBackground();
};


#endif //PENDULUMBALANCERAI_RENDERER_HPP
