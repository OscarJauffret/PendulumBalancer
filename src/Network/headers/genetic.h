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
#include "threadpool.hpp"
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
    int generationsSinceLastImprovement = 0;
    unsigned long long int duration;
    unsigned long long int lastDuration;

    vector<Genome> population;
    RenderWindow& window;
    Time timePerFrame;
    Renderer& renderer;

    ThreadPool pool;
    bool showBest = false;
    bool stop = false;

public:
    Genetic(class Renderer &renderer, const string& startingGenomePath);
    void train();
    vector<Genome> trainAgents(vector<Genome> pop);
    void trainAgent(Genome genome, float &fitness, bool shouldRender, PendulumRenderer &pendulumRenderer,
                    float accelerationFactor);
    void replayBestGenome();

    void initializePopulation(int populationSize, int inputSize);
    vector<Genome> selection();

    vector<Genome> initializeNewPopulationWithElites();
    float calculateTotalFitness();
    int tournamentSelection();

    void render(bool isControlled);

    int selectRandomGenomeBasedOnFitness();
};


#endif //PENDULUMBALANCERAI_GENETIC_H
