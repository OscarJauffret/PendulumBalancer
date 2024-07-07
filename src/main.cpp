#include "Engine/headers/Engine.h"
#include "Network/headers/networkdrawer.h"
#include "Render/headers/renderer.hpp"
#include "Network/headers/genetic.h"

void launchGame(Mode mode, RenderWindow &window, Time timePerFrame);
void launchNetwork();

int main() {
    renderer r;
    launchGame(r.askMode(), r.getWindow(), r.getTimePerFrame());
    return 0;
}

void launchGame(Mode mode, RenderWindow &window, Time timePerFrame) {
    if (mode == Mode::Manual) {
        int fitness = 0;
        Engine engine(window, timePerFrame, true, mode, Genome(0, false, false), fitness);
        engine.run();
    } else {
        Genetic genetic(window, timePerFrame);
    }
}

void launchNetwork() {
    Genome genome(7, false, true);
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