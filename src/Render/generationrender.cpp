//
// Created by oscar on 09/07/2024.
//
#include "headers/renderer.hpp"

void Renderer::drawGeneration(int generation, duration elapsedTime, duration virtualTime) {
    drawGenerationBackground();
    drawRealTime(elapsedTime);
    drawVirtualTime(virtualTime);
    drawGenerationText(generation);
}

void Renderer::drawGenerationBackground() {
    RectangleShape background = Card::make(Vector2f(config::layout::generation::originX, config::layout::generation::originY),
                                          Vector2f(config::layout::generation::width, config::layout::generation::height),
                                          config::colors::layout::darkerBackgroundColor,
                                          config::layout::generation::bgOutlineThickness,
                                          config::colors::layout::generationOutlineColor);
    window.draw(background);
}

void Renderer::drawRealTime(duration timeElapsed) {
    string timeText = "Real training time: \n" + formatTime(timeElapsed);
    Text text = getText(timeText, 10, config::colors::textColor,
                        Vector2f(config::layout::generation::originX + 5,
                                 config::layout::generation::originY + 2 + 25));
    window.draw(text);
}

void Renderer::drawVirtualTime(duration virtualTime) {
    string virtualTimeText = "Simulated training time: \n" + formatTime(virtualTime);
    Text text = getText(virtualTimeText, 10, config::colors::textColor,
                        Vector2f(config::layout::generation::originX + 5,
                                 config::layout::generation::originY + 2 + 60));
    window.draw(text);
}

string Renderer::formatTime(duration seconds) {
    const long long secondsPerMinute = 60;
    const long long secondsPerHour = 60 * secondsPerMinute;
    const long long secondsPerDay = 24 * secondsPerHour;

    long long days = seconds / secondsPerDay;
    seconds %= secondsPerDay;
    long long hours = seconds / secondsPerHour;
    seconds %= secondsPerHour;
    long long minutes = seconds / secondsPerMinute;
    seconds %= secondsPerMinute;

    string result;
    if (days > 0) result += to_string(days) + " day" + (days > 1 ? "s" : "") + ", ";
    if (hours > 0) result += to_string(hours) + " h, ";
    if (minutes > 0) result += to_string(minutes) + " m, ";
    result += to_string(seconds) + " s";

    return result;
}

void Renderer::drawGenerationText(int generation) {
    string generationText = "Generation: " + to_string(generation);
    Text text = getText(generationText, 20, config::colors::textColor,
                        Vector2f(config::layout::generation::originX + 5, config::layout::generation::originY + 2));
    window.draw(text);
}