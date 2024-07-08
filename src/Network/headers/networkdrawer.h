//
// Created by oscar on 03/07/2024.
//

#ifndef PENDULUMBALANCERAI_NETWORKDRAWER_H
#define PENDULUMBALANCERAI_NETWORKDRAWER_H
#include "genome.h"
#include "../../config/configuration.h"
#include <SFML/Graphics.hpp>
#include <map>

using sf::Vector2f;
using std::map;

class NetworkDrawer {
    Genome genome;
    map<int, Vector2f> nodesPositions;
    const Vector2f origin = Vector2f(config::layout::net::originX, config::layout::net::originY);
    const Vector2f allowedSpace = Vector2f(config::layout::net::width, config::layout::net::height);

public:
    explicit NetworkDrawer(Genome &genome);

    void draw(sf::RenderWindow& window);
    void setGenome(const Genome &gen);

    void calculateNodesPositions();
    void drawNodes(sf::RenderWindow &window);
    static void drawNode(sf::RenderWindow &window, float xPos, float yPos);

    void drawConnections(sf::RenderWindow &window);
    static sf::RectangleShape drawConnection(sf::Vector2f from, sf::Vector2f to, float thickness);

};


#endif //PENDULUMBALANCERAI_NETWORKDRAWER_H
