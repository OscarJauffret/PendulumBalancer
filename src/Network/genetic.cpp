//
// Created by oscar on 05/07/2024.
//

#include "headers/genetic.h"

void Genetic::geneticAlgorithm() {
    initializePopulation(config::genetic::populationSize,
                                      config::net::inputSize, config::net::outputSize);
    bool training = true;
    while (training) {
        population = selection();
        for (Genome genome : population) {
            genome = mutation(genome);
        }
    }
}

vector<Genome> Genetic::trainAgents(vector<Genome> genomeBatch) {

}

void Genetic::initializePopulation(int populationSize, int inputSize, int outputSize) {
    for (int i = 0; i < populationSize; i++) {
        population.emplace_back(inputSize, outputSize, true, true);
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
        for (const Genome& genome : batch) {
            newPopulation.push_back(genome);
        }
    }
    return newPopulation;
}

Genome Genetic::mutation(Genome genome) {
    return Genome(0, 0, false, false);
}
