//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENOME_H
#define PENDULUMBALANCERAI_GENOME_H
#include "activation.hpp"
#include "../../config/configuration.h"
#include "genome.h"
#include "randomnumbergenerator.hpp"

#include <vector>
#include <random>
using namespace std;

struct Node {
    int id;
    int layer;
    double value;
    float bias;
    ActivationPtr activation;

    Node() : id(-1), layer(-2), value(0.0), bias(0.0), activation(nullptr) {}
    Node(int id, int layer, float bias, ActivationPtr activation) : id(id), layer(layer), value(0.0), bias(bias), activation(activation) {}
};

struct Connection {
    double weight;
    int from;
    int to;

    Connection(double weight, int from, int to) : weight(weight), from(from), to(to) {}
};

class Genome {
    vector<Node> nodes;
    vector<Connection> connections;
    float fitness;
    unsigned long long int trainingTime = 0;

public:
    Genome();
    Genome(int inputSize, bool randomBiases, bool randomlyWeightedConnections);

    int createNode(float bias, Activation activation, int layer, int id);
    void addConnection(float weight, int from, int to);
    int checkIfLayerIsLast(int layer);
    static bool checkIfRoomForNode(int fromLayer, int toLayer);
    void updateLayersAfter(int layer);
    void removeConnection(int from, int to);

    int getDepth();
    vector<Node> & getNodes();
    vector<Connection> & getConnections();

    vector<Node> getNodesInLayer(int layer);
    Node & getNode(int id);

    vector<Node> getNodesExceptLayer(int layer);

    void addWeightedConnections(bool randomWeights);
    double predict(vector<float> inputs);

    float forward();
    void setFitness(float fit);
    [[nodiscard]] float getFitness() const;

    void setTrainingTime(unsigned long long int time);
    [[nodiscard]] unsigned long long int getTrainingTime() const;

    friend ostream & operator<<(ostream &os, const Genome &genome);
};

#endif //PENDULUMBALANCERAI_GENOME_H
