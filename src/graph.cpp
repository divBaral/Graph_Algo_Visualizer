#include "Graph.h"

Graph::Graph( sf::RenderWindow* window, int& mode ) :m_window( window ), m_mode( mode ) {}

Graph::~Graph()
{
	this->m_window = NULL; //m_window is actually just a reference to the main sfml window
	vertices.clear();
	edges.clear();
}

void Graph::addVertex( float x, float y )
{
	Vertex *v = new Vertex( x, y );
 
	vertices.push_back( v );
}

void Graph::removeVertex( Vertex* v )		//remove vertex v or remove the vertex at the top of vertices vector
{
	if( !vertices.empty() )  
	{
		if( v == NULL)  //if ctrl + Z
		{
			Vertex* temp = vertices.back();
			removeEdge( vertices.back() );
		
			m_adj.erase(temp);
			visited.erase(temp);

			for( Vertex* ver : vertices)
			{
				m_adj[ver].remove( temp );
			}

			vertices.pop_back();
			if( temp )
			{
				delete temp;
				temp = NULL;
			}
		}

		else  	 //if in delete mode, and a vertex is passed as parameter
		{     
			vertices.remove( v );
			removeEdge( v );
			m_adj.erase(v);
			visited.erase(v);
			for( Vertex* ver : vertices)
			{
				m_adj[ver].remove( v );
			}
		}
	}
}

void Graph::removeEdge( Vertex* vertex )       //remove edge with ctrl+z
{
	for( Vertex *v : m_adj[vertex] )
	{
		if( m_edgeList[{v, vertex}] || m_edgeList[{vertex, v}])
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

void Graph::addEdge( Vertex* u, Vertex* v )
{
	
	for( Edge* edge : edges )
	{
		if( edge->m_v1 == v && edge->m_v2 == u )    //check if edge already exists
			return;
	}
	m_adj[v].push_back( u );
	m_adj[u].push_back( v );

	Edge* e = new Edge( u, v );
	edges.push_back( e );
	m_edgeList[{u, v}] = e;
	m_edgeList[{v, u}] = e;
	
}
void Graph::draw()
{
	for ( Edge* e : edges )
	{
		e->update();
		e->draw( m_window, m_mode );
	}
	for ( Vertex* v :vertices )
	{
		v->update();
		v->draw( m_window, m_mode );
	}
}

void Graph::BFS( Vertex *start ) 
{	
	if( !start ) return;
    for( Vertex *v : vertices )
    {
        visited[v]=0;   //initially not visited
    }

	bool sameVertex = false;  //checks if vertex used in the statement below is equal to start
	auto prev_start = start;

	for( Vertex *vertex: vertices ) 
	{
		if( sameVertex == true) start = vertex;  
		if( vertex == prev_start) sameVertex = true;

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

						m_edgeList[{ u, v }]->m_scanning = true;    //changing color of edge 
            			m_edgeList[{ v, u }]->m_scanning = true;

						update();
					}
					u->m_scanned = true;
					u->m_scanning = false;
				}
			}
		}

		update( false );
		start = vertex; 
	}
}

void Graph::DFS( Vertex *start )
{
	if( !start ) return;
    for( Vertex *v:vertices )
    {
        visited[v]=0;   //initially not visited
    }

	bool sameVertex = false;
	auto prev_start = start;

	for( Vertex *vertex : vertices )
	{
		if( sameVertex == true) start = vertex;  
		if( vertex == prev_start) sameVertex = true;

		if( !visited[start] )
		{	
			start->m_scanned = true;
			dftraverse( start );
		}
		
		update( false );
		start = vertex;
	}
}

void Graph::dftraverse( Vertex *v )
{
	visited[v] = 1;
	for( Vertex *u: m_adj[v] )
	{
		if( !visited[u] )
		{
			u->m_scanning = true;

			m_edgeList[{ u, v }]->m_scanning = true;    //changing color of edge 
            m_edgeList[{ v, u }]->m_scanning = true;

			update();

			dftraverse( u );
			u->m_scanned = true;
			u->m_scanning = false;			
		}
	}
}

void Graph::update( bool slp )
{
	m_window->clear( sf::Color(33, 31, 32) );

	draw();
	m_window->display();
	if( slp )sleep(1); 
}

void Graph::restoreDefault()  //restore default everything about vertex and edges to run algorithms again
{
	m_window->clear( sf::Color(33, 31, 32) );

	for ( Edge* e : edges )
	{
		e->restoreDefault();
		e->draw( m_window, m_mode );
	}

	for ( Vertex* v :vertices )
	{
		v->restoreDefault();
		v->draw( m_window, m_mode );
	}

	m_window->display();
}