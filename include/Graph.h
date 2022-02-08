#pragma once
#include <iostream>
#include "Vertex.h"
#include "Edge.h"
#include <list>
// #include <unordered_map>
#include <map>
#include <vector>

class Graph 
{
public:
	Graph();
	void addEdge(Vertex*, Vertex*);
	void addVertex(float, float); 
	void draw( sf::RenderWindow* window );
	void removeVertex();
	void removeEdge(Vertex* vertex);
	Vertex* getVertex(sf::Vector2f);

private:
	static int m_verticesno;
	static int m_edgesno;

public:
	// static std::map< Vertex* , std::list<Vertex*> > m_adj;
	static std::map< Vertex* , std::list<Vertex*> > m_adj;
	static std::map< std::pair<Vertex*, Vertex*> , Edge*> m_edgeList;
	


	//for graphics
	static std::list<Vertex*> vertices;
	static std::list<Edge*> edges;
	// std::vector<Vertex*> vertices;


	//bfs,dfs, kruskal, prim, dijkstra 


};
