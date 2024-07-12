//
// Created by oscar on 08/07/2024.
//

#include "headers/mutator.hpp"

void Mutator::mutate(Genome &genome, int generationsSinceLastImprovement) {
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
    float multiplier = 1.0f;
    if (generationsSinceLastImprovement > 100) {
        multiplier = 3.0f;
    } else if (generationsSinceLastImprovement > 50) {
        multiplier = 2.0f;
    }
    if (RNG::proba(config::genetic::mut::newNodeProba * multiplier)) {
        newNode(genome);
    }

    if (RNG::proba(config::genetic::mut::newConnectionProba)) {
        newConnection(genome);
    }
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
    int fromLayer = genome.getNode(from).layer;
    int toLayer = genome.getNode(to).layer;
    toLayer = genome.checkIfLayerIsLast(toLayer);
    int newNodeLayer = calculateNewNodeLayer(genome, fromLayer, toLayer);
    double weight = connection.weight;
    initializeNewNodeAndConnections(genome, from, to, newNodeLayer, weight);
}

int Mutator::calculateNewNodeLayer(Genome &genome, const int fromLayer, const int toLayer) {
    bool roomForNode = Genome::checkIfRoomForNode(fromLayer, toLayer);
    int newNodeLayer;
    if (roomForNode) {
        newNodeLayer = RNG::randomIntBetween(fromLayer + 1, toLayer - 1);
    } else {
        newNodeLayer = toLayer;
        genome.updateLayersAfter(toLayer);
    }
    return newNodeLayer;
}

void Mutator::initializeNewNodeAndConnections(Genome &genome, int from, int to, int newNodeLayer, double previousWeight) {
    genome.removeConnection(from, to);
    int nodeId = genome.createNode(RNG::randomFloatBetweenMinus1And1(false), Activation::Relu, newNodeLayer, -1);
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