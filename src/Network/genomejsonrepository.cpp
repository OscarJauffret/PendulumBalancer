//
// Created by oscar on 09/07/2024.
//

#include "headers/genomejsonrepository.hpp"

nlohmann::json GenomeJSonRepository::saveGenome(Genome &genome) {
    json j;
    vector<Node> nodes = genome.getNodes();
    vector<Connection> connections = genome.getConnections();
    float fitness = genome.getFitness();
    unsigned long long int trainingTime = genome.getTrainingTime();

    j["nodes"] = json::array();
    for (const auto& node : nodes) {
        json nodeJson;
        nodeJson["id"] = node.id;
        nodeJson["layer"] = node.layer;
        nodeJson["bias"] = node.bias;
        nodeJson["activation"] = node.layer == -1 ? "Tanh" : "Relu";
        j["nodes"].push_back(nodeJson);
    }

    j["connections"] = json::array();
    for (const auto& connection : connections) {
        j["connections"].push_back({{"weight", connection.weight}, {"from", connection.from}, {"to", connection.to}});
    }

    j["fitness"] = fitness;
    j["trainingTime"] = trainingTime;
    return j;
}

Genome GenomeJSonRepository::loadGenome(const nlohmann::json &j) {
    Genome genome;

    for (const auto& node : j["nodes"]) {
        genome.createNode(node["bias"], node["activation"] == "Tanh" ? Activation::Tanh : Activation::Relu, node["layer"], node["id"]);
    }

    for (const auto& connection : j["connections"]) {
        genome.addConnection(connection["weight"], connection["from"], connection["to"]);
    }

    genome.setFitness(j["fitness"]);
    genome.setTrainingTime(j["trainingTime"]);
    return genome;
}

void GenomeJSonRepository::saveGenomeToFile(Genome &genome) {
    string filename = getFilename();
    json j = saveGenome(genome);
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    file << j.dump(4);
    file.close();
}

Genome GenomeJSonRepository::loadGenomeFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    json j;
    file >> j;
    file.close();
    return loadGenome(j);
}

string GenomeJSonRepository::getFilename() {
    string path = "genomes/";
    vector <string> files = getFiles();
    path += "genome" + to_string(files.size()) + ".json";
    return path;
}

vector<string> GenomeJSonRepository::getFiles() {
    vector<string> files;
    string path = "genomes/";
    if (!fs::exists(path)) {
        fs::create_directory(path);
    }
    for (const auto & entry : fs::directory_iterator(path)) {
        files.push_back(entry.path().string());
    }
    return files;
}