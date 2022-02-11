#include "Graph.h"
#include <unistd.h>
#include <algorithm>

Graph::Graph( sf::RenderWindow* m_window )
{
	this->m_window = m_window;
}
Graph::~Graph()
{
	this->m_window = NULL; //m_window is actually just a reference to the main sfml window
}

void Graph::addVertex( float x, float y )
{
	Vertex *v = new Vertex( x, y );
 
	vertices.push_back( v );

	m_verticesno++;
}

void Graph::removeVertex()		//remove edge with ctrl+z
{
	if( !vertices.empty() )
	{
		removeEdge( vertices.back() );
		vertices.pop_back();
	}
}

void Graph::removeEdge( Vertex* vertex )       //remove edge with ctrl+z
{
	for( Vertex *v : m_adj[vertex] )
	{
		m_edgeList.erase({vertex, v});
		m_edgeList.erase({v, vertex});
		for( std::list<Edge*>::iterator it = edges.begin(); it != edges.end(); it++ )
		{
			if( (vertex == (*it)->m_v1 && v == (*it)->m_v2) || (vertex == (*it)->m_v2 && v == (*it)->m_v1) )
			{
				edges.erase(it);
				break;
			}
		}
	}
}

Vertex* Graph::getVertex( sf::Vector2f pos )      //returns vertex, this is used when making edges
{
	for( Vertex* vertex : vertices )
	{
		if ( vertex->m_sprite->getGlobalBounds().contains(pos) )   //for checking if vertex is already there
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

	for( Edge* edge : edges )
	{
		if( edge->m_v1 == v && edge->m_v2 == u )    //check if edge already exists
			return;
	}
	Edge* e = new Edge( u, v );
	edges.push_back( e );
	m_edgeList[{v, u}] = e;
	m_edgeList[{u, v}] = e;
	m_edgesno++;
	
}
void Graph::draw()
{
	for ( Edge* e : edges )
	e->draw( m_window );
	for ( Vertex* v :vertices )
	{
		v->update();
		v->draw( m_window );
	}
}

void Graph::traverse( Vertex *start )
{
	for( Edge* e: edges )
		edgesBackup.push_back( e );	//if we want to revert to the original graph use this 
	//BFS( start );
	DFS( start );
}

void Graph::BFS( Vertex *start )
{
    for( Vertex *v:vertices )
    {
        visited[v]=0;   //initially not visited
    }

	this->edges.clear();
	for( Vertex *vertex: vertices )
	{
		if( !visited[start] )
		{
			visited[start] = 1;
			searchQ.enqueue(start);

			start->m_scanned = true;

			while( !searchQ.empty() )
			{
				auto v = searchQ.dequeue();
				for( Vertex *u: m_adj[v] )
				{
					if( !visited[u] )
					{
						u->m_scanning = true;
						visited[u] = 1;
						searchQ.enqueue(u);
						Edge *e = new Edge(u,v);
						e->m_color = sf::Color::Blue;

						//can we replace the edges?
						// std::replace( edges.begin(), edges.end(), my_edgeList[{u,v}] , e );
						// std::replace( edges.begin(), edges.end(), my_edgeList[{v,u}] , e );

						edges.push_back( e );
				        m_window->clear(sf::Color::White);
        				draw();
        				m_window->display();
        				sleep(1);
					}
					u->m_scanned = true;
					u->m_scanning = false;
				}
			}
		}

		start = vertex;
	}
}

void Graph::DFS( Vertex *start )
{
    for( Vertex *v:vertices )
    {
        visited[v]=0;   //initially not visited
    }
	this->edges.clear();
	for( Vertex *vertex:vertices )
	{
		if( !visited[start] )
		{	
			start->m_scanned = true;
			dftraverse( start );
		}
		
		start = vertex;
	}
}
void Graph::dftraverse( Vertex *v )
{
	visited[v]++;
	for( Vertex *u: m_adj[v] )
	{
		if( !visited[u] )
		{
			u->m_scanning = true;
			visited[u] = 1;
			Edge *e = new Edge(u,v);
			e->m_color = sf::Color::Blue;

			//can we replace the edges?
			// std::replace( edges.begin(), edges.end(), my_edgeList[{u,v}] , e );
			// std::replace( edges.begin(), edges.end(), my_edgeList[{v,u}] , e );

			edges.push_back( e );
			m_window->clear(sf::Color::White);
			draw();
			m_window->display();
			sleep(1);

			dftraverse( u );
			u->m_scanned = true;
			u->m_scanning = false;			
		}
	}
}
