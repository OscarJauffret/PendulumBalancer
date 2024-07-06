//
// Created by oscar on 06/07/2024.
//

#include "headers/renderer.hpp"

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
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (manualButton.isMouseOver(window)) {
                        mode = Mode::Manual;
                        window.close();
                    } else if (aiButton.isMouseOver(window)) {
                        mode = Mode::Ai;
                        window.close();
                    }
                }
            }
        }

        window.clear();
        manualButton.draw(window);
        aiButton.draw(window);
        window.display();
    }
    return mode;
}

Button renderer::createModeButton(bool isManualButton) {
    float buttonHeight = 300;
    float buttonWidth = buttonHeight * M_PHI;
    float buttonX = resolution.x / 2 - 5;
    if (isManualButton) {
        buttonX -= buttonWidth + 10;
    }
    float buttonY = resolution.y / 2 - buttonHeight / 2;
    string text = isManualButton ? "Manual" : "AI";

    return Button(buttonX, buttonY, buttonWidth, buttonHeight, text, font);
}
