//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENOME_H
#define PENDULUMBALANCERAI_GENOME_H
#include "activation.hpp"
#include "../../config/configuration.h"

#include <vector>

struct Node {
    int id;
    int layer;
    float value;
    float bias;
    Activation activation;
};

struct Connection {
    float weight;
    int from;
    int to;
};

class Genome {
    std::vector<Node> nodes;
    std::vector<Connection> connections;
    int fitness;

public:
    Genome(int inputSize, int outputSize, bool randomBiases, bool randomlyWeightedConnections);
    int createNode(float bias, Activation activation, int layer);
    void addConnection(float weight, int from, int to);
    int getDepth();
    std::vector<Node> getNodesInLayer(int layer);
    Node getNode(int id);
    std::vector<Connection> getConnections();

    void addWeightedConnections(bool randomWeights);
};

#endif //PENDULUMBALANCERAI_GENOME_H
