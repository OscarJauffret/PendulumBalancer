#include "headers/genome.h"

Genome::Genome(int inputSize, bool randomBiases, bool randomlyWeightedConnections) {
    srand(time(nullptr));
    float bias;

    for (int i = 0; i < inputSize; i++) {
        bias = generateBias(randomBiases);
        createNode(bias, Activation::None, 0);
    }

    bias = generateBias(randomBiases);
    createNode(bias, Activation::Tanh, -1);

    addWeightedConnections(randomlyWeightedConnections);
    fitness = 0;
}

float Genome::generateBias(bool randomBiases) {
    float bias = randomBiases ? (float) rand() / RAND_MAX : 0;
    if (rand() % 2 == 0) {
        bias = -bias;
    }
    return bias;
}

void Genome::addWeightedConnections(bool randomWeights) {
    for (Node from : getNodesInLayer(0)) {
        for (Node to : getNodesInLayer(-1)) {
            float weight = randomWeights ? (float) rand() / RAND_MAX : 0;
            addConnection(weight, from.id, to.id);
        }
    }
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

vector<Connection> Genome::getConnections() {
    return connections;
}

double Genome::predict(vector<float> inputs) {
    for (int i = 0; i < inputs.size(); i++) {
        nodes[i].value = inputs[i];
    }
    float output = forward();
    cout << "Returning output: " << output << endl;
    return output;
}

float Genome::forward() {
    for (Node& node : nodes) {
        if (node.layer == 0) {
            cout << "Input node " << node.id << " initial value: " << node.value << endl;
        }
    }

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
//            cout << "Output node id: " << node.id << " Output node layer: " << node.layer << endl;
//            cout << "Output node value: " << node.value << endl;
//            cout << "Returning output node value: " << node.value << endl;
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
