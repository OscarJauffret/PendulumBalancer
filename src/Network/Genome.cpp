#include "headers/genome.h"

Genome::Genome(int inputSize, int outputSize, bool randomBiases, bool randomlyWeightedConnections) {
    srand(time(nullptr));
    float bias;

    for (int i = 0; i < inputSize; i++) {
        bias = randomBiases ? (float) rand() / RAND_MAX : 0;
        createNode(bias, Activation::Relu, 0);
    }

    for (int i = 0; i < outputSize; i++) {
        bias = randomBiases ? (float) rand() / RAND_MAX : 0;
        createNode(bias, Activation::Tanh, -1);
    }

    addWeightedConnections(randomlyWeightedConnections);
    fitness = 0;
}

void Genome::addWeightedConnections(bool randomWeights) {
    cout << "Nodes in layer 0: " << getNodesInLayer(0).size() << endl;
    for (Node from : getNodesInLayer(0)) {
        for (Node to : getNodesInLayer(-1)) {
            float weight = randomWeights ? (float) rand() / RAND_MAX : 0;
            cout << "Adding connection from " << from.id << " to " << to.id << " with weight " << weight << endl;
            addConnection(weight, from.id, to.id);
        }
    }
}

int Genome::createNode(float bias, Activation activation, int layer) {
    Node node{};
    node.id = (int) nodes.size();
    node.bias = bias;
    node.activation = activation;
    node.layer = layer;
    nodes.push_back(node);
    return node.id;
}

void Genome::addConnection(float weight, int from, int to) {
    Connection connection{};
    connection.weight = weight;
    connection.from = from;
    connection.to = to;
    connections.push_back(connection);
}

int Genome::getDepth() {
    int maxDepth = 0;
    for (Node node : nodes) {
        if (node.layer > maxDepth) {
            maxDepth = node.layer;
        }
    }
    return maxDepth + 2;    // +1 for output layer, +1 for input layer, because output layer has a layer of -1
}

std::vector<Node> Genome::getNodesInLayer(int layer) {
    if (layer == getDepth() - 1) {
        layer = -1;
    }

    std::vector<Node> layerNodes;
    for (Node node : nodes) {
        if (node.layer == layer) {
            layerNodes.push_back(node);
        }
    }
    return layerNodes;
}

std::vector<Connection> Genome::getConnections() {
    return connections;
}