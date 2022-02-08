#include "Graph.h"

std::map< Vertex* , std::list<Vertex*> > Graph::m_adj;
std::map< std::pair<Vertex*, Vertex*> , Edge*> Graph::m_edgeList;
std::list<Vertex*> Graph::vertices;
std::list<Edge*> Graph::edges;
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

void Graph::removeVertex()		//remove edge with ctrl+z
{
	if(!vertices.empty())
		removeEdge(vertices.back());
		vertices.pop_back();
}

void Graph::removeEdge(Vertex* vertex)       //remove edge with ctrl+z
{
	for(Vertex* v : Graph::m_adj[vertex])
	{
		Graph::m_edgeList.erase({vertex, v});
		Graph::m_edgeList.erase({v, vertex});
		for(std::list<Edge*>::iterator it = edges.begin(); it != edges.end(); it++)
		{
			if((vertex == (*it)->m_v1 && v == (*it)->m_v2) || (vertex == (*it)->m_v2 && v == (*it)->m_v1))
			{
				edges.erase(it);
				break;
			}
		}
	}
}

Vertex* Graph::getVertex(sf::Vector2f pos)      //returns vertex, this is used when making edges
{
	for( Vertex* vertex : vertices)
	{
		if (vertex->m_sprite->getGlobalBounds().contains(pos))   //for checking if vertex is already there
		{
			return vertex;
		}
	}
	return NULL;
}

void Graph::addEdge( Vertex* v, Vertex* u )
{
	
	m_adj[v].push_back( u );
	m_adj[u].push_back( v );

	for( Edge* edge : edges)
	{
		if(edge->m_v1 == v && edge->m_v2 == u)    //check if edge already exists
			return;
	}
	Edge* e = new Edge( u, v );
	edges.push_back( e );
	Graph::m_edgeList[{v, u}] = e;
	Graph::m_edgeList[{u, v}] = e;
	m_edgesno++;
	
}
void Graph::draw( sf::RenderWindow* window )
{
	for ( Vertex* v : Graph::vertices )
	{
		v->update();
		v->draw( window );
	}
	for ( Edge* e : Graph::edges )
		e->draw( window );

}
