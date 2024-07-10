//
// Created by oscar on 09/07/2024.
//

#ifndef PENDULUMBALANCERAI_GENOMEJSONREPOSITORY_HPP
#define PENDULUMBALANCERAI_GENOMEJSONREPOSITORY_HPP
#include "../../include/nlohmann/json.hpp"
#include "genome.h"
#include <fstream>
#include <filesystem>
using json = nlohmann::json;
namespace fs = std::filesystem;

class GenomeJSonRepository {
public:
    static nlohmann::json saveGenome(Genome &genome);
    static Genome loadGenome(const nlohmann::json &j);

    static void saveGenomeToFile(Genome &genome);
    static Genome loadGenomeFromFile(const string &filename);

    static vector<string> getFiles();

    static string getFilename();
};


#endif //PENDULUMBALANCERAI_GENOMEJSONREPOSITORY_HPP
