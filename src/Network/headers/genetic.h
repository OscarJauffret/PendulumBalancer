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
#include <chrono>

using std::vector;
using namespace std::chrono;

class Genetic {
    int generation = 0;
    NetworkDrawer drawer;
    vector<int> scores = {};
    long long int duration;

    vector<Genome> population;
    RenderWindow& window;
    Time timePerFrame;
    Renderer& renderer;
public:
    Genetic(class Renderer &renderer);
    void train();
    vector<Genome> trainAgents(vector<Genome> genomeBatch);
    void trainAgent(Genome genome, bool shouldRender, int &fitness);
    void replayBestGenome();

    void initializePopulation(int populationSize, int inputSize);
    vector<Genome> selection();
    static Genome mutation(Genome &genome);

    vector<Genome> initializeNewPopulationWithElites();
    int calculateTotalFitness();
    int tournamentSelection();

    void updateRendering(bool clear);
};


#endif //PENDULUMBALANCERAI_GENETIC_H
