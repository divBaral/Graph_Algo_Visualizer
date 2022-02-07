#include "Dijkstra.h"

Dijkstra::Dijkstra(Vertex *start)
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
        if(!relaxed[popped.first])              
        {
            start = popped.first;                
            shortestLink[start] = popped.second;
            relaxed[popped.first] = true;            //relaxing the edges
        }
        else continue;             //if edge is relaxed, we don't need to check it

        for( Vertex* neighbour : Graph::m_adj[popped.first])      //we look for the neighbours of the vertex
        {
            std::list<Edge*> temp;  
            temp = popped.second;    //pushes the edges that correspond to the vertex from source, just 
            //so that we can add the edges of its neighbours too and push to the heap tree
            float dis = queue.h->getDist(popped.second);    //gets the distance of the route to check below
            if(dist[start] > dis)                          //checking if distance is lesser from this route
            {
                temp.push_back(Graph::m_edgeList[{neighbour, start}]);     //just pushing the edge start -> neighbour
                queue.enqueue({neighbour, temp});                    //enqueuing into the heap tree
                dist[start] = dis;
            }
        }
    }
}