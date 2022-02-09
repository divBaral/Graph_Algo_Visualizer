#pragma once
#include <iostream>
// #include "Vertex.h"
#include "Graph.h"
// #include "Edge.h"
#include "priorityqueue.h"
#include <map>
#include <limits>
#define inf std::numeric_limits<float>::infinity()

class Dijkstra
{
    std::map<Vertex*, bool> visited;  //relaxing the edges
    std::map<Vertex*, float> dist;     //for checking if the distance is lesser than that of the distance in priority queue
    std::map<Vertex*, std::list<Edge*>> shortestLink;    //this is the final shortest routes of all vertices from the source
public:
    Dijkstra();
    void run(Vertex*, sf::RenderWindow*, Graph*);

};