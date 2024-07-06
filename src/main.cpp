#include "Engine/headers/Engine.h"
#include "Network/headers/networkdrawer.h"
#include "Render/headers/renderer.hpp"

void launchGame(Mode mode);
void launchNetwork();

int main() {
//    config::mode == Mode::Manual ? launchGame() : launchNetwork();
    renderer r = renderer();
//    r.askMode() == Mode::Manual ? launchGame(Mode::Manual) : launchNetwork();
    launchGame(r.askMode());
    return 0;
}

void launchGame(Mode mode) {
    Engine engine;
    engine.run(mode);
}

void launchNetwork() {
    Genome genome(7, 1, false, true);
//    genome.createNode(0, Activation::Relu, 1, true);
//    genome.createNode(0, Activation::Relu, 1, true);
//    genome.createNode(0, Activation::Relu, 2, true);
    NetworkDrawer drawer(genome);
    RenderWindow window(VideoMode(config::window::width, config::window::height), config::window::title,
                        config::window::style, ContextSettings(0, 0, 8));
    window.setFramerateLimit(config::window::fps);
    drawer.draw(window);
    window.display();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }
}