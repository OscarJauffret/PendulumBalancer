#include "Engine/headers/Engine.h"
#include "Render/headers/networkrenderer.h"
#include "Render/headers/renderer.hpp"
#include "Network/headers/genetic.h"

void launchGame(Renderer &renderer);
void launchNetwork(RenderWindow &window);
NetworkRenderer networkRenderer;
PendulumRenderer pendulumRenderer = PendulumRenderer(config::score::yThreshold, Vector2f(config::layout::pendulum::originX,
                                                                      config::layout::pendulum::originY));

int main() {
    Renderer r(pendulumRenderer, networkRenderer);
    launchGame(r);
//    launchNetwork(r.getWindow());
    return 0;
}

void launchGame(Renderer &renderer) {
    Mode mode = renderer.askMode();
    string genomePath = renderer.askGenomePath();
    pendulumRenderer.initializeShapes(config::score::yThreshold, Vector2f(config::layout::pendulum::originX,
                                                                         config::layout::pendulum::originY));
    if (genomePath == "close") {
        return;
    }
    if (mode == Mode::Manual) {
        int fitness = 0;
        Engine engine(renderer.getWindow(), renderer.getTimePerFrame(), mode, Genome(0, false, false), fitness, true,
                      pendulumRenderer);
        engine.run();
    } else {
        Genetic genetic(renderer, genomePath);
        genetic.train();
    }
}

void launchNetwork(RenderWindow &window) {
    Genome genome(6, true, true);
//    genome.createNode(0, Activation::Relu, 1, true);
//    genome.createNode(0, Activation::Relu, 1, true);
//    genome.createNode(0, Activation::Relu, 2, true);
    NetworkRenderer drawer(genome);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    genome = Mutator::mutate(genome);
                    drawer.setGenome(genome);
                }
            }
        }
        window.clear();
        drawer.draw(window);
        window.display();
    }
}