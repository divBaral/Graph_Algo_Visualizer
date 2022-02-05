#include <Vertex.h>
#include <Edge.h>

class Graph 
{
public:
	Graph();
private:
	void addEdge();
	void addVertex();
	void draw();

private:
	int m_verticesno=0;
	int m_edgesno=0;

	//std::list<Vertex*> *vertices;

	std::unordered_map< Vertex* , std::list<Vertex*> > m_adj;

	//bfs,dfs, krusal, prim, dijstra 




};
