//
// Created by oscar on 08/07/2024.
//

#include "headers/mutator.hpp"

void Mutator::addNodeMutation(Genome &genome) {
    Connection connection = getRandomConnection(genome);
    Node fromNode = genome.getNode(connection.from);
    Node toNode = genome.getNode(connection.to);
    int toLayer = genome.checkIfLayerIsLast(toNode.layer);
    int newNodeLayer = calculateNewNodeLayer(genome, fromNode, toLayer);
    initializeNewNodeAndConnections(genome, fromNode, toNode, newNodeLayer);
}

Connection Mutator::getRandomConnection(Genome &genome) {
    vector<Connection> connections = genome.getConnections();
    int randomIndex = RNG::randomIntBetween(0, (int) connections.size() - 1);
    Connection connection = connections[randomIndex];
    return connection;
}

int Mutator::calculateNewNodeLayer(Genome &genome, const Node &fromNode, int toLayer) {
    bool roomForNode = Genome::checkIfRoomForNode(fromNode.layer, toLayer);
    int newNodeLayer;
    if (roomForNode) {
        newNodeLayer = RNG::randomIntBetween(fromNode.layer + 1, toLayer - 1);
    } else {
        newNodeLayer = toLayer;
        genome.updateLayersAfter(toLayer);
    }
    return newNodeLayer;
}

void Mutator::initializeNewNodeAndConnections(Genome &genome, const Node &fromNode, const Node &toNode, int newNodeLayer) {
    int nodeId = genome.createNode(RNG::randomFloatBetweenMinus1And1(true), Activation::Relu, newNodeLayer);
    genome.addConnection(RNG::randomFloatBetweenMinus1And1(true), fromNode.id, nodeId);
    genome.addConnection(RNG::randomFloatBetweenMinus1And1(true), nodeId, toNode.id);
    genome.removeConnection(fromNode.id, toNode.id);  // Remove old connection (from -> to)
}

void Mutator::addConnectionMutation(Genome &genome) {
    vector<Connection> connections = genome.getConnections();
    vector<Node> fromNodes = genome.getNodesExceptLayer(-1);
    vector<Node> toNodes = genome.getNodesExceptLayer(0);
    int fromIndex = RNG::randomIntBetween(0, (int) fromNodes.size() - 1);
    int toIndex = RNG::randomIntBetween(0, (int) toNodes.size() - 1);
    int from = fromNodes[fromIndex].id;
    int to = toNodes[toIndex].id;
    if (connectionsExists(connections, from, to)) {
        return;
    }
    genome.addConnection(RNG::randomFloatBetweenMinus1And1(true), from, to);
}

bool Mutator::connectionsExists(vector<Connection> &connections, int from, int to) {
    bool exists = false;
    for (Connection connection: connections) {
        if (connection.from == from && connection.to == to) {
            cout << "Connection already exists" << endl;
            exists = true;
        }
    }
    return exists;
}

void Mutator::changeWeightMutation(Genome &genome) {
    vector<Connection> connections = genome.getConnections();
    int index = RNG::randomIntBetween(0, (int) connections.size() - 1);
    genome.setConnectionWeight(index, RNG::randomFloatBetweenMinus1And1(true));
}
