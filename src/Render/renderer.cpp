//
// Created by oscar on 06/07/2024.
//

#include "headers/renderer.hpp"

const Time renderer::timePerFrame = seconds(1.f / config::window::fps);

renderer::renderer() : resolution(config::window::width, config::window::height),
                        window(VideoMode(resolution.x, resolution.y),
                               config::window::title, config::window::style,
                               sf::ContextSettings(0, 0, 8)) {
    window.setFramerateLimit(FPS);
    if (!font.loadFromFile(config::assets::fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

Mode renderer::askMode() {
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
    window.clear(Color::Black);
    window.display();
    return mode;
}

Button renderer::createModeButton(bool isManualButton) {
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

void renderer::drawScoresChart(const deque<int> &scores) {
    drawScoresBackground();
    drawScoresLines(scores);
}

void renderer::drawScoresBackground() {
    RectangleShape background(Vector2f(config::layout::score::width, config::layout::score::height));
    background.setPosition(config::layout::score::originX, config::layout::score::originY);
    background.setOutlineThickness(config::layout::score::bgOutlineThickness);
    background.setOutlineColor(config::colors::layout::scoreOutlineColor);
    background.setFillColor(config::colors::layout::scoreBackgroundColor);
    window.draw(background);
}

void renderer::drawScoresLines(const deque<int> &scores) {
    float x = config::layout::score::originX + config::layout::score::spaceBetweenBars / 2;
    int maxScore = *max_element(scores.begin(), scores.end());
    for (int score : scores) {
        float normalizedScore = static_cast<float>(score) / maxScore;
        score = normalizedScore * config::layout::score::height * 0.9f;
        RectangleShape line(Vector2f(config::layout::score::barWidth, score));
        line.setPosition(x, config::layout::score::originY + config::layout::score::height - score);
        line.setFillColor(config::colors::layout::scoreLineColor);
        window.draw(line);
        x += config::layout::score::barWidth + config::layout::score::spaceBetweenBars;
    }
}

RenderWindow& renderer::getWindow() {
    return window;
}

Time renderer::getTimePerFrame() {
    return timePerFrame;
}
