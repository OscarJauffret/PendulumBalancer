//
// Created by oscar on 09/07/2024.
//
#include "headers/renderer.hpp"

void Renderer::drawScoresChart(const vector<int> &scores) {
    drawScoresBackground();
    drawScaleLines();
    drawScoresText();
    drawScoresLines(scores);
}

void Renderer::drawScoresBackground() {
    RectangleShape background(Vector2<float>(config::layout::score::width, config::layout::score::height));
    background.setPosition(config::layout::score::originX, config::layout::score::originY);
    background.setOutlineThickness(config::layout::score::bgOutlineThickness);
    background.setOutlineColor(config::colors::layout::scoreOutlineColor);
    background.setFillColor(config::colors::layout::darkerBackgroundColor);
    window.draw(background);
}

void Renderer::drawScaleLines() {
    float x = config::layout::score::originX;
    float y = config::layout::score::originY;
    float width = config::layout::score::width;
    float height = config::layout::score::height;
    for (int i = 0; i < 10; i++) {
        RectangleShape line(Vector2<float>(width, 1));
        line.setPosition(x, y + i * height / 10);
        line.setFillColor(config::colors::layout::backgroundColor);
        window.draw(line);
    }
    for (int i = 0; i < 10; i++) {
        RectangleShape line(Vector2<float>(1, height));
        line.setPosition(x + i * width / 10, y);
        line.setFillColor(config::colors::layout::backgroundColor);
        window.draw(line);
    }

}

void Renderer::drawScoresText() {
    Text text = getText("Scores", 10, config::colors::textColor,
                        Vector2<float>(config::layout::score::originX + 5, config::layout::score::originY + 5));
    window.draw(text);

}

void Renderer::drawScoresLines(vector<int> scores) {
    if (scores.empty()) {
        return;
    }
    vector<int> lastScores = getLastScores(scores);
    float x = config::layout::score::originX + config::layout::score::spaceBetweenBars;
    int maxScore = getMaxScore(lastScores);
    int i = lastScores.size();
    for (int score: lastScores) {
        float normalizedScore = static_cast<float>(score) / maxScore;
        int height = normalizedScore * config::layout::score::height * 0.8f;
        RectangleShape line = initScoreBar(x, height);
        Text generationText = getText(to_string(scores.size() - i), 10, config::colors::textColor,
                                      Vector2<float>(x, config::layout::score::originY + config::layout::score::height - 5));
        generationText.setRotation(-90);
        Text scoreText = getText(to_string(score), 10, config::colors::textColor,
                                 Vector2<float>(x, config::layout::score::originY + config::layout::score::height - height - 15));
        x += config::layout::score::barWidth + config::layout::score::spaceBetweenBars;
        i--;
        window.draw(line);
        window.draw(generationText);
        window.draw(scoreText);
    }
}

RectangleShape Renderer::initScoreBar(float x, int score) const {
    RectangleShape line(Vector2<float>(config::layout::score::barWidth, score));
    line.setPosition(x, config::layout::score::originY + config::layout::score::height - score);
    line.setFillColor(config::colors::layout::scoreLineColor);
    return line;
}

int Renderer::getMaxScore(vector<int> &lastScores) const {
    int maxScore = *max_element(lastScores.begin(), lastScores.end());
    if (maxScore == 0) {
        maxScore = 1;
    }
    return maxScore;
}

vector<int> Renderer::getLastScores(vector<int> &scores) const {
    vector<int> lastScores;
    if (scores.size() > 10) {
        lastScores = vector<int>(scores.end() - 10, scores.end());
    } else {
        lastScores = scores;
    }
    return lastScores;
}