#include "Dijkstra.h"
#include <unistd.h>

Dijkstra::Dijkstra( sf::RenderWindow * m_window )
{
    this->m_window = m_window;
}
Dijkstra::~Dijkstra()
{
    this->m_window = NULL; //m_window is actually reference to the actual sfml window
}

void Dijkstra::run( Vertex *start, Graph *g )
{
    priorityqueue queue;
    for( Vertex *vertex : g->vertices )  
    {
        dist[vertex] = inf;       //initializing distances of all vertices from source as infinite
    }

    dist[start] = 0;             //distance of source is 0
    queue.enqueue({start, {}});
    while ( !queue.empty() )
    {
        std::pair<Vertex*, std::list<Edge*>> popped = queue.dequeue();
        start = popped.first;  

        std::cout << dist[start] << " Finalized" << std::endl;

        shortestLink[start] = popped.second;
        visited[popped.first] = true;            //relaxing the edges

        start->m_scanned = true;
        start->m_scanning = false;

        m_window->clear(sf::Color::White);
        g->draw();
        m_window->display();
        sleep(2);

        for( Vertex* neighbour : g->m_adj[popped.first])      //we look for the neighbours of the vertex
        {
            if( !visited[neighbour] )
            {
                std::list<Edge*> temp;  
                temp = popped.second;    //pushes the edges that correspond to the vertex from source, just 
                //so that we can add the edges of its neighbours too and push to the heap tree
                float dis = queue.h->getDist(popped.second) + g->m_edgeList[{neighbour, start}]->m_weight;    //gets the distance of the route to check below
                if(dist[neighbour] > dis)                          //checking if distance is lesser from this route
                {
                    temp.push_back(g->m_edgeList[{neighbour, start}]);     //just pushing the edge start -> neighbour
                    queue.enqueue({neighbour, temp});                    //enqueuing into the heap tree
                    dist[neighbour] = dis;

                    std::cout << dist[neighbour] << std::endl;
                    
                    neighbour->m_scanning = true;
                    m_window->clear(sf::Color::White);
                    g->draw();
                    m_window->display();
                    sleep(2);
                }
            }
        }
    }

    //  for( Vertex* vertex : g->vertices )  
    // {
    //     std::cout<<"----------------"<<std::endl;
    //     std::cout<<dist[vertex]<<std::endl;       //initializing distances of all vertices from source as infinite
    // }
}