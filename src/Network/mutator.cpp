//
// Created by oscar on 08/07/2024.
//

#include "headers/mutator.hpp"

Genome Mutator::mutate(Genome &genome) {
    int numMutations = config::genetic::numberOfMutations;
    for (int i = 0; i < numMutations; i++) {
        if (RNG::proba(config::genetic::mut::weightAndBiasMutRate)) {
            if (RNG::proba(config::genetic::mut::weightMutProportion)) {
                mutateWeights(genome);
            } else {
                mutateBiases(genome);
            }
        }
    }
    if (RNG::proba(config::genetic::mut::newNodeProba)) {
        newNode(genome);
    }

    if (RNG::proba(config::genetic::mut::newConnectionProba)) {
        newConnection(genome);
    }

    return genome;
}

void Mutator::mutateWeights(Genome &genome) {
    if (genome.getConnections().empty()) {
        return;
    }
    Connection& connection = pickRandom(genome.getConnections());
    if (RNG::proba(config::genetic::mut::newValueProba)) {
        connection.weight = RNG::randomFloatBetweenMinus1And1(true);
    } else {
        if (RNG::proba(config::genetic::mut::addValueProba)) {
            connection.weight += RNG::randomFloatBetweenMinus1And1(true);
        } else {
            connection.weight += config::genetic::mut::smallWeightRate * RNG::randomFloatBetweenMinus1And1(true);
        }
    }
}

void Mutator::mutateBiases(Genome &genome) {
    Node& node = pickRandom(genome.getNodes());
    if (RNG::proba(config::genetic::mut::newValueProba)) {
        node.bias = RNG::randomFloatBetweenMinus1And1(true);
    } else {
        if (RNG::proba(config::genetic::mut::addValueProba)) {
            node.bias += RNG::randomFloatBetweenMinus1And1(true);
        } else {
            node.bias += config::genetic::mut::smallWeightRate * RNG::randomFloatBetweenMinus1And1(true);
        }
    }
}

void Mutator::newNode(Genome &genome) {
    Connection &connection = pickRandom(genome.getConnections());
    int from = connection.from;
    int to = connection.to;
    to = genome.checkIfLayerIsLast(to);
    int newNodeLayer = calculateNewNodeLayer(genome, from, to);
    double weight = connection.weight;
    initializeNewNodeAndConnections(genome, from, to, newNodeLayer, weight);
}

int Mutator::calculateNewNodeLayer(Genome &genome, const int from, const int to) {
    bool roomForNode = Genome::checkIfRoomForNode(from, to);
    int newNodeLayer;
    if (roomForNode) {
        newNodeLayer = RNG::randomIntBetween(from + 1, to - 1);
    } else {
        newNodeLayer = to;
        genome.updateLayersAfter(to);
    }
    return newNodeLayer;
}

void Mutator::initializeNewNodeAndConnections(Genome &genome, int from, int to, int newNodeLayer, double previousWeight) {
    genome.removeConnection(from, to);
    int nodeId = genome.createNode(RNG::randomFloatBetweenMinus1And1(true), Activation::Relu, newNodeLayer, -1);
    genome.addConnection(previousWeight, from, nodeId);
    genome.addConnection(1.0f, nodeId, to);
}

void Mutator::newConnection(Genome &genome) {
    vector<Connection> connections = genome.getConnections();
    vector<Node> fromNodes = genome.getNodesExceptLayer(-1);
    vector<Node> toNodes = genome.getNodesExceptLayer(0);
    Connection connection = getNewConnectionNodes(genome, fromNodes, toNodes);

    int from = connection.from;
    int to = connection.to;
    if (connectionsExists(connections, from, to)) {
        return;
    }
    genome.addConnection(RNG::randomFloatBetweenMinus1And1(true), from, to);
}

Connection Mutator::getNewConnectionNodes(Genome &genome, vector<Node> &fromNodes, vector<Node> &toNodes) {
    while (true) {
        Node fromNode = pickRandom(fromNodes);
        Node toNode = pickRandom(toNodes);
        int toLayer = genome.checkIfLayerIsLast(toNode.layer);
        if (fromNode.layer < toLayer) {
            return {0.0, fromNode.id, toNode.id}; }
    }
}

bool Mutator::connectionsExists(vector<Connection> &connections, int from, int to) {
    bool exists = false;
    for (Connection connection: connections) {
        if (connection.from == from && connection.to == to) {
            exists = true;
        }
    }
    return exists;
}

template<typename TDataType>
TDataType& Mutator::pickRandom(vector<TDataType> &vector) {
    int const index = RNG::randomIntBetween(0, (int) vector.size() - 1);
    return vector[index];
}