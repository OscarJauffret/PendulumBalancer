//
// Created by oscar on 08/07/2024.
//

#ifndef PENDULUMBALANCERAI_MUTATOR_HPP
#define PENDULUMBALANCERAI_MUTATOR_HPP
#include "genome.h"

class Mutator {
private:
    static int calculateNewNodeLayer(Genome &genome, const Node &fromNode, int toLayer);
    static void initializeNewNodeAndConnections(Genome &genome, const Node &fromNode, const Node &toNode, int newNodeLayer);
    static Connection getRandomConnection(Genome &genome);

public:
    static void addNodeMutation(Genome &genome);
    static void addConnectionMutation(Genome &genome);
    static void changeWeightMutation(Genome &genome);

    static bool connectionsExists(vector<Connection> &connections, int from, int to);
};


#endif //PENDULUMBALANCERAI_MUTATOR_HPP
