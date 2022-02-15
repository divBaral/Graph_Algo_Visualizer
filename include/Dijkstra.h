/****
 * 
 * This file contains code implementing dijkstra algorithm
 * 
 ***/

#pragma once
#include <iostream>
#include "Graph.h"
#include "priorityqueue.h"
#include <map>
#include <limits>
#define inf std::numeric_limits<float>::infinity()

class Dijkstra
{
    std::map<Vertex*, bool> visited;  //relaxing the edges
    std::map<Vertex*, float> dist;     //for checking if the distance is lesser than that of the distance in priority queue
    std::map<Vertex*, std::list<Edge*>> shortestLink;    //this is the final shortest routes of all vertices from the source
    sf::RenderWindow *m_window;
public:
    Dijkstra( sf::RenderWindow* );
    ~Dijkstra();
    void run( Graph*, Vertex* );

};