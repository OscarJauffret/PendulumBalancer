//
// Created by oscar on 05/07/2024.
//

#include <utility>

#include "headers/genetic.h"

Genetic::Genetic(class Renderer &renderer) : window(renderer.getWindow()), timePerFrame(renderer.getTimePerFrame()), renderer(renderer), duration(0) {
    initializePopulation(config::genetic::populationSize,
                         config::net::inputSize);
    drawer.setGenome(population[0]);
}

void Genetic::train() {
    auto start = high_resolution_clock::now();
    updateRendering(true);
    while (window.isOpen()) {
        cout << "Generation: " << generation << endl;
        population = selection();
        cout << "Best fitness: " << population[0].getFitness() << endl;
        scores.push_back(population[0].getFitness());
        drawer.setGenome(population[0]);

        auto now = chrono::high_resolution_clock::now();
        duration = duration_cast<chrono::seconds>(now - start).count();
        generation++;

        updateRendering(true);
        replayBestGenome();
        updateRendering(true);

        vector<Genome> newPopulation = initializeNewPopulationWithElites();
        while (newPopulation.size() < config::genetic::populationSize) {
            Genome chosenGenome = population[tournamentSelection()];
            chosenGenome = mutation(chosenGenome);
            newPopulation.push_back(chosenGenome);
        }
        population = newPopulation;
    }
}

void Genetic::updateRendering(bool clear) {
    if (clear) {
        window.clear(config::colors::layout::backgroundColor);
    }
    drawer.draw(window);
    renderer.drawGeneration(generation, duration);
    renderer.drawScoresChart(scores);
    if (clear) {
        window.display();
    }
}

vector<Genome> Genetic::initializeNewPopulationWithElites() {
    vector<Genome> newPopulation = {};
    int i = 0;
    while (newPopulation.size() < (unsigned int) (config::genetic::populationSize * config::genetic::elitismRate)) {
        newPopulation.push_back(population[i++]);
    }
    return newPopulation;
}

void Genetic::replayBestGenome() {
    int fitness = 0;
    trainAgent(population[0], true, fitness);
}

int Genetic::calculateTotalFitness() {
    int totalFitness = 0;
    for (Genome genome: population) {
        totalFitness += genome.getFitness();
    }
    return totalFitness;
}

int Genetic::tournamentSelection() {
    int totalFitness = calculateTotalFitness();
    int randomFitness = RNG::randomIntBetween(0, totalFitness - 1);
    int currentFitness = 0;
    int i = 0;
    for (Genome genome: population) {
        currentFitness += genome.getFitness();
        if (randomFitness <= currentFitness) {
            return i;
        }
        i++;
    }
    return 0;
}

vector<Genome> Genetic::trainAgents(vector<Genome> genomeBatch) {
    vector<future<void>> futures;

    for (Genome &genome : genomeBatch) {
        promise<void> prom;
        futures.push_back(prom.get_future());

        thread([&genome, this, prom = move(prom)]() mutable {
            int fitness = 0;
            trainAgent(genome, false, fitness);
            genome.setFitness(fitness);
            prom.set_value();
        }).detach();
    }

    while (!futures.empty()) {
        // Traiter les événements de la fenêtre ici
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return {};
            }
        }
        futures.erase(remove_if(futures.begin(), futures.end(),
                                [](const future<void> &fut) { return fut.wait_for(chrono::seconds(0)) == future_status::ready; }),
                      futures.end());
    }

    return genomeBatch;
}

void Genetic::trainAgent(Genome genome, bool shouldRender, int &fitness) {
    Engine engine(window, timePerFrame, shouldRender, Mode::Ai, std::move(genome), fitness);
    engine.run();
}

void Genetic::initializePopulation(int populationSize, int inputSize) {
    for (int i = 0; i < populationSize; i++) {
        population.emplace_back(inputSize, true, true);
    }
}

vector<Genome> Genetic::selection() {
    int batchSize = config::genetic::batchSize;
    int numBatches = (int) config::genetic::populationSize / batchSize;
    vector<Genome> newPopulation;
    for (int i = 0; i < numBatches; i++) {
        vector<Genome> batch = {};
        for (int j = i * batchSize; j < i * batchSize + batchSize; j++) {
            batch.push_back(population[j]);
        }
        batch = trainAgents(batch);
        for (const Genome &genome: batch) {
            newPopulation.push_back(genome);
        }
    }
    std::sort(newPopulation.begin(), newPopulation.end(), [](Genome& a, Genome& b) -> bool {
        return a.getFitness() > b.getFitness();
    });
    return newPopulation;
}

Genome Genetic::mutation(Genome &genome) {
    int numMutations = config::genetic::numberOfMutations;
    int mutationType = RNG::randomIntBetween(0, numMutations - 1);
    switch (mutationType) {
        case 0:         // Nothing
            return genome;
        case 1:         // Add node
            Mutator::addNodeMutation(genome);
            break;
        case 2:         // Add connection
            Mutator::addConnectionMutation(genome);
            break;
        case 3:         // Change weight
            Mutator::changeWeightMutation(genome);
            break;
        default:
            break;
    }
    return genome;
}


