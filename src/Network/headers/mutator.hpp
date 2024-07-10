//
// Created by oscar on 08/07/2024.
//

#ifndef PENDULUMBALANCERAI_MUTATOR_HPP
#define PENDULUMBALANCERAI_MUTATOR_HPP
#include "genome.h"

class Mutator {
private:
    static int calculateNewNodeLayer(Genome &genome, const Node &fromNode, int toLayer);
    static void
    initializeNewNodeAndConnections(Genome &genome, int fromNodeId, int toNodeId, int newNodeLayer,
                                    double previousWeight);

public:
    static Genome mutate(Genome &genome);

    static void newNode(Genome &genome);
    static void newConnection(Genome &genome);
    static void mutateWeights(Genome &genome);
    static void mutateBiases(Genome &genome);

    static bool connectionsExists(vector<Connection> &connections, int from, int to);

    static Connection getNewConnectionNodes(Genome &genome, vector<Node> &fromNodes, vector<Node> &toNodes);

    template<typename TDataType> static TDataType& pickRandom(vector<TDataType> &vector);
};


#endif //PENDULUMBALANCERAI_MUTATOR_HPP
