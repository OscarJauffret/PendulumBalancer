//
// Created by oscar on 05/07/2024.
//

#include "headers/genetic.h"

Genetic::Genetic(class Renderer &renderer, const string& startingGenomePath)
        : window(renderer.getWindow()), timePerFrame(renderer.getTimePerFrame()), renderer(renderer), duration(0) {
    if (startingGenomePath.empty()) {
        initializePopulation(config::genetic::populationSize,
                             config::net::inputSize);
        lastDuration = 0;
    } else {
        population = {GenomeJSonRepository::loadGenomeFromFile(startingGenomePath)};
        for (int i = 1; i < config::genetic::populationSize; i++) {
            population.emplace_back(config::net::inputSize, true, true);
        }
        lastDuration = population[0].getTrainingTime();
    }
    renderer.setNetworkGenome(population[0]);
}

void Genetic::train() {
    auto start = high_resolution_clock::now();
    render(false);
    while (window.isOpen()) {
        cout << "Generation: " << generation;
        population = selection();
        cout << " Best fitness: " << round(population[0].getFitness()) << endl;
        scores.push_back(population[0].getFitness());
        renderer.setNetworkGenome(population[0]);

        auto now = chrono::high_resolution_clock::now();
        duration = duration_cast<chrono::seconds>(now - start).count();
        generation++;

        render(false);
        replayBestGenome();
        render(false);

        vector<Genome> newPopulation = initializeNewPopulationWithElites();
        while (newPopulation.size() < config::genetic::populationSize) {
            Genome chosenGenome = population[tournamentSelection()];
            chosenGenome = Mutator::mutate(chosenGenome);
            newPopulation.push_back(chosenGenome);
        }
        population = newPopulation;
    }
    Genome toSave = population[0];
    toSave.setTrainingTime(generation * config::genetic::populationSize * config::score::timeLimit + lastDuration);
    toSave.setFitness(population[0].getFitness());
    GenomeJSonRepository::saveGenomeToFile(toSave);
}

void Genetic::render(bool isControlled) {
    renderer.draw(generation, duration,
                  lastDuration + generation * config::genetic::populationSize * config::score::timeLimit, scores,
                  isControlled);
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
    // Launch the best genome in a separate thread
    promise<void> prom;
    future<void> fut = prom.get_future();
    thread([prom = std::move(prom), this]() mutable {
        float fitness = 0;
        trainAgent(population[0], fitness, true, renderer.getPendulumRenderer(), 1.0);
        prom.set_value();
    }).detach();

    // Wait for the thread to finish and update rendering while waiting
    while (fut.wait_for(chrono::seconds(0)) != future_status::ready){
        // Traiter les événements de la fenêtre ici
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
        render(true);
    }
}

float Genetic::calculateTotalFitness() {
    float totalFitness = 0;
    for (Genome genome: population) {
        totalFitness += genome.getFitness();
    }
    return totalFitness;
}

int Genetic::tournamentSelection() {
    float totalFitness = calculateTotalFitness();
    if (totalFitness == 0) {
        return 0;
    }
    float randomFitness = RNG::randomFloatBetween(0, totalFitness - 1);
    float currentFitness = 0;
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
            float fitness = 0;
            trainAgent(genome, fitness, false, renderer.getPendulumRenderer(), 5.0);
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

void Genetic::trainAgent(Genome genome, float &fitness, bool shouldRender, PendulumRenderer &pendulumRenderer,
                         float accelerationFactor) {
    Engine engine(window, timePerFrame, Mode::Ai, std::move(genome), fitness, shouldRender, pendulumRenderer);
    engine.run(accelerationFactor);
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


