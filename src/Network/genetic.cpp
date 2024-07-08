//
// Created by oscar on 05/07/2024.
//

#include <utility>

#include "headers/genetic.h"

Genetic::Genetic(RenderWindow &window, Time timePerFrame) : window(window), timePerFrame(timePerFrame) {
    initializePopulation(config::genetic::populationSize,
                         config::net::inputSize);
    bool training = true;
    int generation = 0;
    while (generation < 10) {
        cout << "Generation: " << generation << endl;
        population = selection();
        for (Genome genome: population) {
            cout << "Fitness: " << genome.getFitness() << endl;
        }
        NetworkDrawer drawer(population[0]);
        drawer.draw(window);
        window.display();

        vector<Genome> newPopulation = initializeNewPopulationWithElites();
        generation++;
        while (newPopulation.size() < config::genetic::populationSize) {
            Genome chosenGenome = population[tournamentSelection()];
            chosenGenome = mutation(chosenGenome);
            newPopulation.push_back(chosenGenome);
        }
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
    vector<thread> threads;

    for (Genome &genome: genomeBatch) {
        threads.emplace_back([&genome, this]() mutable {
            int fitness = 0;
            trainAgent(genome, false, fitness);
            genome.setFitness(fitness);
        });
    }

    for (thread &t: threads) {
        t.join();
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
    int mutationType = RNG::randomIntBetween(0, numMutations);
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


