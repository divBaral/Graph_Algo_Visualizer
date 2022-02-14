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

void Dijkstra::run( Vertex *start, Graph *graph )
{
    priorityqueue queue;
    for( Vertex *vertex : graph->vertices )  
    {
        dist[vertex] = inf;       //initializing distances of all vertices from source as infinite
    }

    dist[start] = 0;             //distance of source is 0
    queue.enqueue({start, {}});
    while ( !queue.empty() )
    {
        std::pair<Vertex*, std::list<Edge*>> popped = queue.dequeue();
        start = popped.first;  

        shortestLink[start] = popped.second;
        visited[popped.first] = true;            //relaxing the edges

        start->m_scanned = true;
        start->m_scanning = false;

        graph->update();

        for( Vertex* neighbour : graph->m_adj[popped.first])      //we look for the neighbours of the vertex
        {
            if( !visited[neighbour] )
            {
                std::list<Edge*> temp;  
                temp = popped.second;    //pushes the edges that correspond to the vertex from source, just 
                //so that we can add the edges of its neighbours too and push to the heap tree
                float dis = queue.h->getDist(popped.second) + graph->m_edgeList[{neighbour, start}]->m_weight;    //gets the distance of the route to check below
                if(dist[neighbour] > dis)                          //checking if distance is lesser from this route
                {
                    temp.push_back(graph->m_edgeList[{neighbour, start}]);     //just pushing the edge start -> neighbour
                    queue.enqueue({neighbour, temp});                    //enqueuing into the heap tree
                    dist[neighbour] = dis;
                    
                    neighbour->m_scanning = true;

                    graph->update();
                }
            }
        }
    }
}