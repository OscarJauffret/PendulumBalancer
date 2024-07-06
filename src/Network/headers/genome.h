//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENOME_H
#define PENDULUMBALANCERAI_GENOME_H
#include "activation.hpp"
#include "../../config/configuration.h"

#include <vector>
using std::vector;

struct Node {
    int id;
    int layer;
    double value;
    float bias;
    ActivationPtr activation;

    Node() : id(-1), layer(-2), value(0.0), bias(0.0), activation(nullptr) {}
};

struct Connection {
    double weight;
    int from;
    int to;
};

class Genome {
    vector<Node> nodes;
    vector<Connection> connections;
    int fitness;

public:
    Genome(int inputSize, bool randomBiases, bool randomlyWeightedConnections);
    int createNode(float bias, Activation activation, int layer);
    void addConnection(float weight, int from, int to);

    int getDepth();
    vector<Node> getNodesInLayer(int layer);
    Node & getNode(int id);
    vector<Connection> getConnections();

    void addWeightedConnections(bool randomWeights);

    double predict(vector<float> inputs);

    float forward();

    void setFitness(int fit);
    int getFitness();

    static float generateBias(bool randomBiases) ;
};

#endif //PENDULUMBALANCERAI_GENOME_H
