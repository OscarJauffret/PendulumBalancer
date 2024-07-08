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
        int fromIndex = RNG::randomIntBetween(0, (int) fromNodes.size() - 1);
        int toIndex = RNG::randomIntBetween(0, (int) toNodes.size() - 1);
        Node fromNode = fromNodes[fromIndex];
        Node toNode = toNodes[toIndex];
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

void Mutator::changeWeightMutation(Genome &genome) {
    vector<Connection> connections = genome.getConnections();
    int index = RNG::randomIntBetween(0, (int) connections.size() - 1);
    genome.setConnectionWeight(index, RNG::randomFloatBetweenMinus1And1(true));
}
