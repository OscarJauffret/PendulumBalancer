//
// Created by oscar on 05/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENETIC_H
#define PENDULUMBALANCERAI_GENETIC_H
#include "../../config/configuration.h"
#include "genome.h"
#include <vector>

using std::vector;

class Genetic {
    vector<Genome> population;
public:
    void geneticAlgorithm();
    vector<Genome> trainAgents(vector<Genome> genomeBatch);

    void initializePopulation(int populationSize, int inputSize, int outputSize);
    vector<Genome> selection();
    Genome mutation(Genome genome);
};


#endif //PENDULUMBALANCERAI_GENETIC_H
