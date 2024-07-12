//
// Created by oscar on 05/07/2024.
//

#include "headers/genetic.h"

Genetic::Genetic(class Renderer &renderer, const string& startingGenomePath)
        : window(renderer.getWindow()), timePerFrame(renderer.getTimePerFrame()), renderer(renderer), duration(0), pool(config::genetic::numThreads) {
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
    showBest = false;
    cout << "Initialized " << config::genetic::numThreads << " threads" << endl;
}

void Genetic::train() {
    auto start = high_resolution_clock::now();
    render(false);
    while (window.isOpen() && !stop) {
        cout << "Generation: " << generation;
        population = selection();
        cout << " Best fitness: " << format("{:.2f}", population[0].getFitness()) << endl;
        scores.push_back(population[0].getFitness());
        renderer.setNetworkGenome(population[0]);

        if ((scores.size() >= 2) && (scores.back() > scores[scores.size() - 2])) {
            generationsSinceLastImprovement = 0;
        } else {
            generationsSinceLastImprovement++;
        }

        auto now = chrono::high_resolution_clock::now();
        duration = duration_cast<chrono::seconds>(now - start).count();
        generation++;

        render(false);
        if (showBest) {
            replayBestGenome();
            render(false);
        }

        vector<Genome> newPopulation = initializeNewPopulationWithElites();
        while (newPopulation.size() < config::genetic::populationSize) {
            newPopulation.push_back(population[tournamentSelection()]);
            Mutator::mutate(newPopulation.back(), generationsSinceLastImprovement);
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
                  isControlled, showBest);
}

vector<Genome> Genetic::initializeNewPopulationWithElites() {
     vector<Genome> newPopulation;

    int eliteCount = config::genetic::populationSize * config::genetic::elitismRate;
    newPopulation.reserve(eliteCount);
    std::copy(population.begin(), population.begin() + eliteCount, std::back_inserter(newPopulation));

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

    while (fut.wait_for(chrono::seconds(0)) != future_status::ready){
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    showBest = !showBest;
                } else if (event.key.code == sf::Keyboard::Backspace) {
                    stop = true;
                }
            }
        }
        render(true);
    }
}

float Genetic::calculateTotalFitness() {
    float totalFitness = 0;
    for (const Genome& genome: population) {
        totalFitness += genome.getFitness();
    }
    return totalFitness;
}

int Genetic::tournamentSelection() {
    const int tournamentSize = 3;
    vector<int> tournamentParticipants;

    for (int i = 0; i < tournamentSize; ++i) {
        int randomIndex = selectRandomGenomeBasedOnFitness();
        tournamentParticipants.push_back(randomIndex);
    }

    int bestParticipant = tournamentParticipants[0];
    float bestFitness = population[tournamentParticipants[0]].getFitness();
    for (int i = 1; i < tournamentParticipants.size(); ++i) {
        int participantIndex = tournamentParticipants[i];
        float participantFitness = population[participantIndex].getFitness();
        if (participantFitness > bestFitness) {
            bestParticipant = participantIndex;
            bestFitness = participantFitness;
        }
    }
    return bestParticipant;
}

int Genetic::selectRandomGenomeBasedOnFitness() {
    float totalFitness = calculateTotalFitness();
    if (totalFitness == 0) {
        return 0;
    }
    float randomFitness = RNG::randomFloatBetween(0, totalFitness - 1);
    float currentFitness = 0;
    int i = 0;
    for (const Genome& genome: population) {
        currentFitness += genome.getFitness();
        if (randomFitness <= currentFitness) {
            return i;
        }
        i++;
    }
    return 0;
}


vector<Genome> Genetic::trainAgents(vector<Genome> pop) {
    vector<std::future<void>> futures;

    for (Genome &genome: pop) {
        futures.push_back(pool.enqueue([&genome, this]() mutable {
            float fitness = 0;
            trainAgent(genome, fitness, false, renderer.getPendulumRenderer(), config::genetic::gameAccelerationFactor);
            genome.setFitness(fitness);
        }));
    }

    while (!futures.empty()) {
        // Traiter les événements de la fenêtre ici
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return {};
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    showBest = !showBest;
                    render(false);
                }
            }
        }
        futures.erase(remove_if(futures.begin(), futures.end(),
                                [](const future<void> &fut) { return fut.wait_for(chrono::seconds(0)) == future_status::ready; }),
                      futures.end());
    }

    return pop;
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
    vector<Genome> newPopulation = trainAgents(population);
    std::sort(newPopulation.begin(), newPopulation.end(), [](Genome& a, Genome& b) -> bool {
        return a.getFitness() > b.getFitness();
    });
    return newPopulation;
}


