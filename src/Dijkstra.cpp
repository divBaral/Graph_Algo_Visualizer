#include "Dijkstra.h"
#include <unistd.h>

Dijkstra::Dijkstra(){}
void Dijkstra::run(Vertex *start, sf::RenderWindow* window, Graph* g)
{
    priorityqueue queue;
    for(Vertex* vertex : Graph::vertices)  
    {
        dist[vertex] = inf;       //initializing distances of all vertices from source as infinite
    }

    dist[start] = 0;             //distance of source is 0
    queue.enqueue({start, {}});
    while (!queue.empty())
    {
        std::pair<Vertex*, std::list<Edge*>> popped = queue.dequeue();
        start = popped.first;                
        std::cout<<dist[start]<<" Finalized"<<std::endl;
        shortestLink[start] = popped.second;
        visited[popped.first] = true;            //relaxing the edges
        start->m_scanned = true;
        start->m_scanning = false;
        window->clear(sf::Color::White);
        g->draw(window);
        window->display();
        sleep(2);

        for( Vertex* neighbour : Graph::m_adj[popped.first])      //we look for the neighbours of the vertex
        {
            if(!visited[neighbour])
            {
                std::list<Edge*> temp;  
                temp = popped.second;    //pushes the edges that correspond to the vertex from source, just 
                //so that we can add the edges of its neighbours too and push to the heap tree
                float dis = queue.h->getDist(popped.second) + Graph::m_edgeList[{neighbour, start}]->m_weight;    //gets the distance of the route to check below
                if(dist[neighbour] > dis)                          //checking if distance is lesser from this route
                {
                    temp.push_back(Graph::m_edgeList[{neighbour, start}]);     //just pushing the edge start -> neighbour
                    queue.enqueue({neighbour, temp});                    //enqueuing into the heap tree
                    dist[neighbour] = dis;
                    std::cout<<dist[neighbour]<<std::endl;
                    neighbour->m_scanning = true;
                    window->clear(sf::Color::White);
                    g->draw(window);
                    window->display();
                    sleep(2);
                }
            }
        }
    }

     for(Vertex* vertex : Graph::vertices)  
    {
        std::cout<<"----------------"<<std::endl;
        std::cout<<dist[vertex]<<std::endl;       //initializing distances of all vertices from source as infinite
    }
}