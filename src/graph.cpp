#include "Graph.h"

Graph::Graph()
{

}
void Graph::addVertex()
{
	Vertex* v1 = new Vertex( 400, 500 );
	Vertex* v2 = new Vertex(100, 100);

	vertices.push_back(v1);
	vertices.push_back(v2);
	m_verticesno++;
	addEdge( v1, v2 );
	


}
void Graph::addEdge( Vertex* v, Vertex* u )
{
	
	m_adj[v].push_front( u );
	m_adj[u].push_front( v );

	Edge* e = new Edge( u, v );
	edges.push_back( e );
	m_edgesno++;
	
}
void Graph::draw( sf::RenderWindow* window )
{
	for ( Vertex* v : vertices )
		v->draw( window );
	for ( Edge* e : edges )
		e->draw( window );

}
