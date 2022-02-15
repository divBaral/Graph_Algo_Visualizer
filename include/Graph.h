/****
 * 
 * This header file contains class for representing graph structure.
 * It has methods for manipulating the graph.
 * 
 ****/

#pragma once

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

#include "Vertex.h"
#include "Edge.h"
#include "Queue.h"

class Graph 
{
public:	//methods
	Graph( sf::RenderWindow* );
	void addEdge( Vertex*, Vertex* );
	void addVertex(float, float); 
	void draw();
	void removeVertex( Vertex* vertex = NULL);
	void removeEdge( Vertex* vertex );
	Vertex* getVertex( sf::Vector2f );

	void DFS( Vertex* );
	void dftraverse( Vertex* );
	void BFS( Vertex* );

	void update();
	void restoreDefault();
	~Graph();

private: //data member
	sf::RenderWindow *m_window;

public:	//data members
	std::map< Vertex* , std::list<Vertex*> > m_adj;
	std::map< std::pair<Vertex*, Vertex*> , Edge*> m_edgeList;

	//for graphics
	std::list<Vertex*> vertices;
	std::list<Edge*> edges;

	//bfs,dfs, kruskal, prim, dijkstra 
    std::map<Vertex*, int> visited;
    Queue searchQ;
};
