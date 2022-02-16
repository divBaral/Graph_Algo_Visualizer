#include "Graph.h"

Graph::Graph( sf::RenderWindow* window, int& mode ) :m_window( window ), m_mode( mode ) {}

Graph::~Graph()
{
	this->m_window = NULL; //m_window is actually just a reference to the main sfml window
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
			vertices.pop_back();
			free(temp); 
		}

		else  	 //if in delete mode, and a vertex is passed as parameter
		{     
			vertices.remove( v );
			removeEdge( v );
			free(v);
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
	for( Vertex *vertex: vertices )
	{
		if( sameVertex == true) start = vertex;  
		if( vertex == start) sameVertex = true;

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

						// Edge *e = new Edge(u,v);
						// e->m_color = sf::Color::Blue;
						// std::replace( edges.begin(), edges.end(), m_edgeList[{u,v}] , e );
						// std::replace( edges.begin(), edges.end(), m_edgeList[{v,u}] , e );
						m_edgeList[{ u, v }]->m_scanning = true;    //changing color of edge 
            			m_edgeList[{ v, u }]->m_scanning = true;

						update();
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
	if( !start ) return;
    for( Vertex *v:vertices )
    {
        visited[v]=0;   //initially not visited
    }
	//this->edges.clear();
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

			
			// Edge *e = new Edge(u,v);
			// e->m_color = sf::Color::Blue;
			// std::replace( edges.begin(), edges.end(), m_edgeList[{u,v}] , e );
			// std::replace( edges.begin(), edges.end(), m_edgeList[{v,u}] , e );
			m_edgeList[{ u, v }]->m_scanning = true;    //changing color of edge 
            m_edgeList[{ v, u }]->m_scanning = true;

			update();

			dftraverse( u );
			u->m_scanned = true;
			u->m_scanning = false;			
		}
	}
}

void Graph::update()
{
	m_window->clear( sf::Color::Black );
	//m_window->clear(sf::Color::Cyan);
	draw();
	m_window->display();
	sleep(1);
}

void Graph::restoreDefault()  //restore default everything about vertex and edges to run algorithms again
{
	m_window->clear( sf::Color::Black );
	//m_window->clear(sf::Color::Cyan);

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