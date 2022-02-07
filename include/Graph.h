#pragma once
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
	void addEdge(Vertex* v, Vertex* u);
	void addVertex(float, float); 
	void draw( sf::RenderWindow* window );

private:
	static int m_verticesno;
	static int m_edgesno;

public:
	// static std::map< Vertex* , std::list<Vertex*> > m_adj;
	static std::map< Vertex* , std::list<Vertex*> > m_adj;
	static std::map< std::pair<Vertex*, Vertex*> , Edge*> m_edgeList;
	


	//for graphics
	static std::vector<Vertex*> vertices;
	static std::vector<Edge*> edges;
	// std::vector<Vertex*> vertices;


	//bfs,dfs, krusal, prim, dijstra 


};
