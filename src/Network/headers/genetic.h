//
// Created by oscar on 05/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENETIC_H
#define PENDULUMBALANCERAI_GENETIC_H
#include "../../config/configuration.h"
#include "genome.h"
#include "mutator.hpp"
#include "../../Engine/headers/Engine.h"
#include "networkdrawer.h"
#include "../../Render/headers/renderer.hpp"
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <deque>

using std::vector;

class Genetic {
    vector<Genome> population;
    RenderWindow& window;
    Time timePerFrame;
public:
    Genetic(renderer &renderer);
    vector<Genome> trainAgents(vector<Genome> genomeBatch);
    void trainAgent(Genome genome, bool shouldRender, int &fitness);

    void initializePopulation(int populationSize, int inputSize);
    vector<Genome> selection();
    static Genome mutation(Genome &genome);

    vector<Genome> initializeNewPopulationWithElites();
    int calculateTotalFitness();
    int tournamentSelection();

};


#endif //PENDULUMBALANCERAI_GENETIC_H
