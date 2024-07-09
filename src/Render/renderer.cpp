//
// Created by oscar on 06/07/2024.
//

#include "headers/renderer.hpp"

const Time Renderer::timePerFrame = seconds(1.f / config::window::fps);

Renderer::Renderer() : resolution(config::window::width, config::window::height),
                       window(VideoMode(resolution.x, resolution.y),
                               config::window::title, config::window::style,
                               sf::ContextSettings(0, 0, 8)) {
    window.setFramerateLimit(FPS);
    if (!font.loadFromFile(config::assets::fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
    }
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
    window.clear(Color::Black);
    window.display();
    return mode;
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

void Renderer::drawGeneration(int generation, long long elapsedTime) {
    drawGenerationBackground();
    drawRealTime(elapsedTime);
    drawVirtualTime(generation);
    drawGenerationText(generation);
}

void Renderer::drawGenerationBackground() {
    RectangleShape background(Vector2f(config::layout::generation::width, config::layout::generation::height));
    background.setPosition(config::layout::generation::originX, config::layout::generation::originY);
    background.setFillColor(config::colors::layout::generationBackgroundColor);
    background.setOutlineThickness(config::layout::generation::bgOutlineThickness);
    background.setOutlineColor(config::colors::layout::generationOutlineColor);
    window.draw(background);
}

void Renderer::drawRealTime(long long int timeElapsed) {
    string timeText = "Real training time: \n" + formatTime(timeElapsed);
    Text text = getText(timeText, 10, config::colors::textColor,
                        Vector2f(config::layout::generation::originX + 5, config::layout::generation::originY + 2 + 25));
    window.draw(text);
}

void Renderer::drawVirtualTime(int generation) {
    long long int simulatedTime = generation * config::score::timeLimit * config::genetic::populationSize;
    string virtualTimeText = "Simulated training time: \n" + formatTime(simulatedTime);
    Text text = getText(virtualTimeText, 10, config::colors::textColor,
                        Vector2f(config::layout::generation::originX + 5, config::layout::generation::originY + 2 + 60));
    window.draw(text);
}

string Renderer::formatTime(long long int seconds) {
    const long long secondsPerMinute = 60;
    const long long secondsPerHour = 60 * secondsPerMinute;
    const long long secondsPerDay = 24 * secondsPerHour;

    long long days = seconds / secondsPerDay;
    seconds %= secondsPerDay;
    long long hours = seconds / secondsPerHour;
    seconds %= secondsPerHour;
    long long minutes = seconds / secondsPerMinute;
    seconds %= secondsPerMinute;

    std::string result;
    if (days > 0) result += std::to_string(days) + " day" + (days > 1 ? "s" : "") + ", ";
    if (hours > 0) result += std::to_string(hours) + " h, ";
    if (minutes > 0) result += std::to_string(minutes) + " m, ";
    result += std::to_string(seconds) + " s";

    return result;
}


void Renderer::drawGenerationText(int generation) {
    string generationText = "Generation: " + to_string(generation);
    Text text = getText(generationText, 20, config::colors::textColor,
                        Vector2f(config::layout::generation::originX + 5, config::layout::generation::originY + 2));
    window.draw(text);
}

Text Renderer::getText(const string& textToWrite, int charSize, Color color, Vector2f position) const {
    Text text;
    text.setFont(font);
    text.setString(textToWrite);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}

void Renderer::drawScoresChart(const vector<int> &scores) {
    drawScoresBackground();
    drawScaleLines();
    drawScoresText();
    drawScoresLines(scores);
}

void Renderer::drawScoresBackground() {
    RectangleShape background(Vector2f(config::layout::score::width, config::layout::score::height));
    background.setPosition(config::layout::score::originX, config::layout::score::originY);
    background.setOutlineThickness(config::layout::score::bgOutlineThickness);
    background.setOutlineColor(config::colors::layout::scoreOutlineColor);
    background.setFillColor(config::colors::layout::scoreBackgroundColor);
    window.draw(background);
}

void Renderer::drawScaleLines() {
    float x = config::layout::score::originX;
    float y = config::layout::score::originY;
    float width = config::layout::score::width;
    float height = config::layout::score::height;
    for (int i = 0; i < 10; i++) {
        RectangleShape line(Vector2f(width, 1));
        line.setPosition(x, y + i * height / 10);
        line.setFillColor(config::colors::layout::backgroundColor);
        window.draw(line);
    }
    for (int i = 0; i < 10; i++) {
        RectangleShape line(Vector2f(1, height));
        line.setPosition(x + i * width / 10, y);
        line.setFillColor(config::colors::layout::backgroundColor);
        window.draw(line);
    }

}

void Renderer::drawScoresText() {
    Text text = getText("Scores", 10, config::colors::textColor,
                        Vector2f(config::layout::score::originX + 5, config::layout::score::originY + 5));
    window.draw(text);

}

void Renderer::drawScoresLines(vector<int> scores) {
    if (scores.empty()) {
        return;
    }
    vector<int> lastScores;
    if (scores.size() > 10) {
        lastScores = vector<int>(scores.end() - 10, scores.end());
    } else {
        lastScores = scores;
    }
    float x = config::layout::score::originX + config::layout::score::spaceBetweenBars;
    int maxScore = *max_element(lastScores.begin(), lastScores.end());
    if (maxScore == 0) {
        maxScore = 1;
    }
    int i = lastScores.size();
    for (int score : lastScores) {
        float normalizedScore = static_cast<float>(score) / maxScore;
        score = normalizedScore * config::layout::score::height * 0.8f;
        RectangleShape line(Vector2f(config::layout::score::barWidth, score));
        line.setPosition(x, config::layout::score::originY + config::layout::score::height - score);
        line.setFillColor(config::colors::layout::scoreLineColor);
        Text generationText = getText(to_string(scores.size() - i), 10, config::colors::textColor,
                                     Vector2f(x, config::layout::score::originY + config::layout::score::height - 5));
        generationText.setRotation(-90);
        x += config::layout::score::barWidth + config::layout::score::spaceBetweenBars;
        i--;
        window.draw(line);
        window.draw(generationText);
    }
}

RenderWindow& Renderer::getWindow() {
    return window;
}

Time Renderer::getTimePerFrame() {
    return timePerFrame;
}
