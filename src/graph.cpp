#include "Graph.h"

std::map< Vertex* , std::list<Vertex*> > Graph::m_adj;
std::map< std::pair<Vertex*, Vertex*> , Edge*> Graph::m_edgeList;
std::vector<Vertex*> Graph::vertices;
std::vector<Edge*> Graph::edges;
int Graph::m_verticesno = 0;
int Graph::m_edgesno = 0;
Graph::Graph()
{

}

void Graph::addVertex(float x, float y)
{
	Vertex* v = new Vertex( x, y );
	// Vertex* v2 = new Vertex(100, 100);
	// Vertex* v3 = new Vertex(200, 300);
 
	vertices.push_back(v);
	// vertices.push_back(v2);
	m_verticesno++;
	// addEdge( v1, v2 );
	// addEdge( v1, v3 );

}

void Graph::removeVertex()
{
	if(!vertices.empty())
		vertices.pop_back();
}

Vertex* Graph::getVertex(sf::Vector2f pos)      //returns vertex, this is used when making edges
{
	for( Vertex* vertex : vertices)
	{
		if (vertex->m_sprite->getGlobalBounds().contains(pos))
		{
			return vertex;
		}
	}
	return NULL;
}

void Graph::addEdge( Vertex* v, Vertex* u )
{
	
	m_adj[v].push_front( u );
	m_adj[u].push_front( v );

	for( Edge* edge : edges)
	{
		if(edge->m_v1 == v && edge->m_v2 == u)    //check if edge already exists
			return;
	}
	Edge* e = new Edge( u, v );
	edges.push_back( e );
	m_edgesno++;
	
}
void Graph::draw( sf::RenderWindow* window )
{
	for ( Vertex* v : Graph::vertices )
		v->draw( window );
	for ( Edge* e : Graph::edges )
		e->draw( window );

}
