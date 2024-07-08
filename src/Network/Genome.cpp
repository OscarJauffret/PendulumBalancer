#include "headers/genome.h"

Genome::Genome(int inputSize, bool randomBiases, bool randomlyWeightedConnections) {
    float bias;

    for (int i = 0; i < inputSize; i++) {
        bias = RNG::randomFloatBetweenMinus1And1(randomBiases);
        createNode(bias, Activation::None, 0);
    }

    bias = RNG::randomFloatBetweenMinus1And1(randomBiases);
    createNode(bias, Activation::Tanh, -1);

    addWeightedConnections(randomlyWeightedConnections);
    fitness = 0;
}

int Genome::createNode(float bias, Activation activation, int layer) {
    Node node{};
    node.id = (int) nodes.size();
    node.bias = bias;
    node.activation = ActivationFunction::getFunction(activation);
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

void Genome::linkNodeToAdjacentLayers(int nodeId, int layer) {
    if (layer == 0 || layer == getDepth() - 1) {
        throw std::invalid_argument("Cannot link node to adjacent layers in input or output layer");
    }
    vector<Node> nodesInLayer = getNodesInLayer(layer);
    vector<Node> nodesInPreviousLayer = getNodesInLayer(layer - 1);
    int randomIndex = RNG::randomIntBetween(0, (int) nodesInPreviousLayer.size() - 1);
    addConnection(RNG::randomFloatBetweenMinus1And1(true), nodesInPreviousLayer[randomIndex].id, nodeId);
    int nextLayer = layer + 1;
    if (nextLayer == getDepth() - 1) {
        nextLayer = -1;
    }
    vector<Node> nodesInNextLayer = getNodesInLayer(nextLayer);
    randomIndex = RNG::randomIntBetween(0, (int) nodesInNextLayer.size() - 1);
    addConnection(RNG::randomFloatBetweenMinus1And1(true), nodeId, nodesInNextLayer[randomIndex].id);
}

int Genome::checkIfLayerIsLast(int layer) {
    if (layer == - 1) {
        return getDepth() - 1;
    }
    return layer;
}

bool Genome::checkIfRoomForNode(int fromLayer, int toLayer) {
    if (fromLayer == toLayer) {
        return false;
    }
    if (fromLayer + 1 == toLayer) {
        return false;
    }
    return true;
}

void Genome::updateLayersAfter(int layer) {
    for (Node& node : nodes) {
        if (node.layer >= layer) {
            node.layer++;
        }
    }
}

void Genome::removeConnection(int from, int to) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].from == from && connections[i].to == to) {
            connections.erase(connections.begin() + i);
            return;
        }
    }
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

vector<Node> Genome::getNodesInLayer(int layer) {
    if (layer == getDepth() - 1) {
        layer = -1;
    }
    vector<Node> layerNodes;
    for (Node& node : nodes) {
        if (node.layer == layer) {
            layerNodes.push_back(node);
        }
    }
    return layerNodes;
}

void Genome::addWeightedConnections(bool randomWeights) {
    for (Node from : getNodesInLayer(0)) {
        for (Node to : getNodesInLayer(-1)) {
            float weight = RNG::randomFloatBetweenMinus1And1(randomWeights);
            addConnection(weight, from.id, to.id);
        }
    }
}

vector<Connection> Genome::getConnections() {
    return connections;
}

vector<Node> Genome::getNodesExceptLayer(int layer) {
    vector<Node> n;
    for (Node& node : nodes) {
        if (node.layer != layer) {
            n.push_back(node);
        }
    }
    return n;
}

double Genome::predict(vector<float> inputs) {
    for (int i = 0; i < inputs.size(); i++) {
        nodes[i].value = inputs[i];
    }
    float output = forward();
    return output;
}

float Genome::forward() {
    int depth = getDepth();
    for (int i = 0; i < depth; i++) {                                       // Pour chaque couche
        for (Node& node : nodes) {                                          // Pour chaque nœud
            if (node.layer == i || (i == depth - 1 && node.layer == -1)) {  // Si le nœud est dans la couche actuelle
                double sum = 0;
                for (const Connection& connection : connections) {          // Pour chaque connexion
                    if (connection.to == node.id) {                         // Si la connexion est vers le nœud actuel
                        sum += connection.weight * getNode(connection.from).value;
                    }
                }
                node.value = node.activation(sum + node.bias + node.value);              // Appliquer la fonction d'activation et le biais
            }
        }
    }
    for (const Node& node : nodes) {
        if (node.layer == -1) {
            return node.value;
        }
    }
    return 0.0f; // Valeur de retour par défaut si aucun nœud de sortie n'est trouvé
}


Node & Genome::getNode(int id) {
    for (Node& node : nodes) {
        if (node.id == id) {
            return node;
        }
    }
    throw std::invalid_argument("Node with id " + std::to_string(id) + " not found");
}

void Genome::setFitness(int fit) {
    this->fitness = fit;
}

int Genome::getFitness() {
    return fitness;
}

void Genome::setConnectionWeight(int index, float weight) {
    connections[index].weight = weight;
}
