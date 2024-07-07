//
// Created by oscar on 05/07/2024.
//

#include "headers/genetic.h"

Genetic::Genetic(RenderWindow &window, Time timePerFrame) : window(window), timePerFrame(timePerFrame) {
    initializePopulation(config::genetic::populationSize,
                         config::net::inputSize);
    bool training = true;
    population = selection();
//    while (training) {
//        population = selection();
//        for (Genome genome: population) {
//            genome = mutation(genome);
//        }
//        return;
//    }
}

vector<Genome> Genetic::trainAgents(vector<Genome> genomeBatch) {
    bool shouldRender = true;
    vector<thread> threads;

    for (Genome &genome: genomeBatch) {
        cout << "Training agent with render: " << shouldRender << endl;
        threads.emplace_back([shouldRender, &genome, this]() mutable {
            int fitness = 0;
            trainAgent(genome, shouldRender, fitness);
            genome.setFitness(fitness);
        });
        shouldRender = false;
    }

    for (thread &t: threads) {
        t.join();
    }
    return genomeBatch;
}

void Genetic::trainAgent(Genome genome, bool shouldRender, int &fitness) {
    Engine engine(window, timePerFrame, shouldRender, Mode::Ai, genome, fitness);
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
        for (int j = 0; j < batchSize; j++) {
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

Genome Genetic::mutation(Genome genome) {
    return Genome(0, false, false);
}
