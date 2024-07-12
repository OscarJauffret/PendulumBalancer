//
// Created by oscar on 06/07/2024.
//

#include "headers/renderer.hpp"

const Time Renderer::timePerFrame = seconds(1.0f / config::window::fps);

Renderer::Renderer(PendulumRenderer &pendRenderer, NetworkRenderer &netRenderer)
: resolution(config::window::width,config::window::height),
    window(VideoMode(resolution.x, resolution.y),config::window::title,
           config::window::style,sf::ContextSettings(0, 0, 8)),
    pendulumRenderer(pendRenderer), networkRenderer(netRenderer) {
    window.setFramerateLimit(FPS);
    if (!font.loadFromFile(config::assets::fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

PendulumRenderer &Renderer::getPendulumRenderer() {
    return pendulumRenderer;
}

Mode Renderer::askMode() {
    Button manualButton = createModeButton(true);
    Button aiButton = createModeButton(false);
    Mode mode = Mode::Manual;
    bool chosen = false;
    while (window.isOpen() && !chosen) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (manualButton.isMouseOver(window)) {
                        mode = Mode::Manual;
                        chosen = true;
                    } else if (aiButton.isMouseOver(window)) {
                        mode = Mode::Ai;
                        chosen = true;
                    }
                }
            }
        }

        window.clear(config::colors::layout::backgroundColor);
        manualButton.draw(window);
        aiButton.draw(window);
        window.display();
    }
    return mode;
}

string Renderer::askGenomePath() {
    vector<string> paths = GenomeJSonRepository::getFiles();
    paths.insert(paths.begin(), "");
    if (paths.empty()) {
        return "";
    }
    vector<Button> buttons;
    int g = 0;
    float buttonWidth = config::window::width / 2;
    for (const string &path: paths) {
        string text;
        text = getGenomeButtonText(g, path, text);
        buttons.emplace_back(config::window::width / 2 - buttonWidth / 2, 50.0 + g * 50, buttonWidth, 40.0, text, font);
        g++;
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
                return "Close";
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < buttons.size(); i++) {
                        if (buttons[i].isMouseOver(window)) {
                            return paths[i];
                        }
                    }
                }
            }
        }
        window.clear(config::colors::layout::backgroundColor);
        for (Button &button: buttons) {
            button.draw(window);
        }
        window.display();
    }
    return paths[0];
}

string &Renderer::getGenomeButtonText(int g, const string &path, string &text) const {
    if (path.empty()) {
        text = "New genome";
    } else {
        Genome genome = GenomeJSonRepository::loadGenomeFromFile(path);
        text = format("Genome {} - Fitness: {:.2f} - Training time {}", g, genome.getFitness(), formatTime(genome.getTrainingTime()));
    }
    return text;
}


Button Renderer::createModeButton(bool isManualButton) {
    float buttonHeight = 200;
    float buttonWidth = buttonHeight * M_PHI;
    float buttonX = resolution.x / 2 - 5;
    if (isManualButton) {
        buttonX -= buttonWidth + 10;
    }
    float buttonY = resolution.y / 2 - buttonHeight / 2;
    string text = isManualButton ? "Manual" : "AI";

    return Button(buttonX, buttonY, buttonWidth, buttonHeight, text, font);
}

Text Renderer::getText(const string &textToWrite, int charSize, Color color, Vector2f position) const { //TODO: move to utils
    Text text;
    text.setFont(font);
    text.setString(textToWrite);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}

RenderWindow &Renderer::getWindow() {
    return window;
}

Time Renderer::getTimePerFrame() {
    return timePerFrame;
}


void Renderer::setNetworkGenome(Genome &genome) {
    networkRenderer.setGenome(genome);
}

void
Renderer::draw(int generation, duration realTime, duration virtualTime, const vector<float> &scores, bool isControlled,
               bool showBest) {
    window.clear(config::colors::layout::backgroundColor);
    pendulumRenderer.draw(window, font, isControlled);
    networkRenderer.draw(window);
    drawGeneration(generation, realTime, virtualTime);
    drawScoresChart(scores);
    drawInfoPanel(showBest);
    window.display();
}


