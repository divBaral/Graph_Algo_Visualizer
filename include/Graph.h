#include <Vertex.h>
#include <Edge.h>
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

	

	std::unordered_map< Vertex* , std::list<Vertex*> > m_adj;

	//for graphics
	std::vector<Edge*> edges;
	std::vector<Vertex*> vertices;


	//bfs,dfs, krusal, prim, dijstra 




};
