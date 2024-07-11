//
// Created by oscar on 05/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENETIC_H
#define PENDULUMBALANCERAI_GENETIC_H
#include "../../config/configuration.h"
#include "genome.h"
#include "mutator.hpp"
#include "../../Engine/headers/Engine.h"
#include "../../Render/headers/networkrenderer.h"
#include "../../Render/headers/renderer.hpp"
#include "genomejsonrepository.hpp"
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
    vector<float> scores = {};
    long long int duration;
    long long int lastDuration;

    vector<Genome> population;
    RenderWindow& window;
    Time timePerFrame;
    Renderer& renderer;

public:
    Genetic(class Renderer &renderer, const string& startingGenomePath);
    void train();
    vector<Genome> trainAgents(vector<Genome> genomeBatch);
    void trainAgent(Genome genome, float &fitness, bool shouldRender, PendulumRenderer &pendulumRenderer,
                    float accelerationFactor);
    void replayBestGenome();

    void initializePopulation(int populationSize, int inputSize);
    vector<Genome> selection();

    vector<Genome> initializeNewPopulationWithElites();
    float calculateTotalFitness();
    int tournamentSelection();

    void render(bool isControlled);
};


#endif //PENDULUMBALANCERAI_GENETIC_H
