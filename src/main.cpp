#include "Engine/headers/Engine.h"
#include "Network/headers/networkdrawer.h"
#include "Render/headers/renderer.hpp"
#include "Network/headers/genetic.h"

void launchGame(Renderer &renderer);
void launchNetwork(RenderWindow &window);

int main() {
    Renderer r;
    launchGame(r);
//    launchNetwork(r.getWindow());
    return 0;
}

void launchGame(Renderer &renderer) {
    Mode mode = renderer.askMode();
    if (mode == Mode::Manual) {
        int fitness = 0;
        Engine engine(renderer.getWindow(), renderer.getTimePerFrame(), true, mode, Genome(0, false, false), fitness);
        engine.run();
    } else {
        Genetic genetic(renderer);
        genetic.train();
    }
}

void launchNetwork(RenderWindow &window) {
    Genome genome(6, true, true);
//    genome.createNode(0, Activation::Relu, 1, true);
//    genome.createNode(0, Activation::Relu, 1, true);
//    genome.createNode(0, Activation::Relu, 2, true);
    NetworkDrawer drawer(genome);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    genome = Genetic::mutation(genome);
                    drawer.setGenome(genome);
                }
            }
        }
        drawer.draw(window);
        window.display();
    }
}