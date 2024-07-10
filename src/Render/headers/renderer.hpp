//
// Created by oscar on 06/07/2024.
//

#ifndef PENDULUMBALANCERAI_RENDERER_HPP
#define PENDULUMBALANCERAI_RENDERER_HPP

#include "../../config/configuration.h"
#include "../../Network/headers/genomejsonrepository.hpp"
#include "button.hpp"
#include "pendulumrenderer.hpp"
#include "networkrenderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;
using duration = unsigned long long int;

class Renderer {
    Vector2i resolution;
    const unsigned int FPS = config::window::fps;
    static const Time timePerFrame;

    PendulumRenderer& pendulumRenderer;
    NetworkRenderer& networkRenderer;

    Font font;
public:
    RenderWindow window;

    Renderer(PendulumRenderer &pendRenderer, NetworkRenderer &netRenderer);
    Mode askMode();
    Button createModeButton(bool isManualButton);
    string askGenomePath();
    string &getGenomeButtonText(int g, const string &path, string &text) const;

    RenderWindow& getWindow();
    Time getTimePerFrame();
    PendulumRenderer& getPendulumRenderer();

    void drawGeneration(int generation, duration elapsedTime, duration virtualTime);
    void drawGenerationText(int generation);
    void drawRealTime(duration timeElapsed);
    void drawVirtualTime(duration virtualTime);
    void drawGenerationBackground();
    static string formatTime(duration seconds);

    void drawScoresChart(const vector<int> &scores);
    void drawScoresBackground();
    void drawScoresText();
    void drawScaleLines();
    void drawScoresLines(vector<int> scores);

    Text getText(const string& text, int charSize, Color color, Vector2f position) const;

    void setNetworkGenome(Genome &genome);
    void draw(int generation, duration realTime, duration virtualTime, const vector<int> &scores, bool isControlled);

    vector<int> getLastScores(vector<int> &scores) const;

    int getMaxScore(vector<int> &lastScores) const;

    RectangleShape initScoreBar(float x, int score) const;
};


#endif //PENDULUMBALANCERAI_RENDERER_HPP
