//
// Created by oscar on 05/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENETIC_H
#define PENDULUMBALANCERAI_GENETIC_H
#include "../../config/configuration.h"
#include "genome.h"
#include "../../Engine/headers/Engine.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <future>

using std::vector;

class Genetic {
    vector<Genome> population;
    RenderWindow& window;
    Time timePerFrame;
public:
    Genetic(RenderWindow &window, Time timePerFrame);
    vector<Genome> trainAgents(vector<Genome> genomeBatch);
    void trainAgent(Genome genome, bool shouldRender, int &fitness);

    void initializePopulation(int populationSize, int inputSize);
    vector<Genome> selection();
    Genome mutation(Genome genome);
};


#endif //PENDULUMBALANCERAI_GENETIC_H
