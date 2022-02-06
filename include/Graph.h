#include <Vertex.h>
#include <Edge.h>
#include <list>
#include <map>

class Graph 
{
public:
	Graph();
	Graph::Graph( int, int );
private:
	void addEdge();
	void addVertex();
	void draw();

private:
	int m_verticesno=0;
	int m_edgesno=0;

public:
	static std::list<Vertex*> vertices;
	static std::map< Vertex* , std::list<Vertex*> > m_adj;
	static std::map< std::pair<Vertex*, Vertex*> , Edge*> m_edgeList;
	//bfs,dfs, krusal, prim, dijstra 




};