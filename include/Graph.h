#include <Vertex.h>
#include <Edge.h>
#include <list>
// #include <map>
#include <unordered_map>
#include <list>

class Graph 
{
public:
	Graph();
	void addEdge(Vertex* v, Vertex* u);
	void addVertex(); 
	void draw( sf::RenderWindow* window );

private:
	int m_verticesno=0;
	int m_edgesno=0;

public:
	static std::list<Vertex*> vertices;
	// static std::map< Vertex* , std::list<Vertex*> > m_adj;
	std::unordered_map< Vertex* , std::list<Vertex*> > m_adj;
	static std::map< std::pair<Vertex*, Vertex*> , Edge*> m_edgeList;
	Edge* getEdge(Vertex*, Vertex*);
	


	//for graphics
	std::vector<Edge*> edges;
	// std::vector<Vertex*> vertices;


	//bfs,dfs, krusal, prim, dijstra 


};
