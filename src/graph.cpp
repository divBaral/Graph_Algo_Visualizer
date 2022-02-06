#include "../include/Graph.h"

Graph::Graph( int v = 0, int e = 0 )
{

}

bool addVertex()
{

	
	if ( m_vertexmode ) {
		Vertex* v1 = new Vertex(400, 500);
    	Vertex* v2 = new Vertex(100, 100);
		m_verticesno++;
	}


}

bool addEdge( Vertex* v, Vertex* u )
{
	if ( m_edgemode ) {
		m_adj[v].push_front( u );
		m_adj[u].push_front( v );
		m_edgesno++;
		return true;
	}
	return false;
}

	Edge* Graph::getEdge(Vertex*, Vertex*)
	{

	}