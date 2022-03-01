#include "Dijkstra.h"

Dijkstra::Dijkstra( sf::RenderWindow * m_window )
{
    this->m_window = m_window;
}

Dijkstra::~Dijkstra()
{
    this->m_window = NULL; //m_window is actually reference to the actual sfml window
}

void Dijkstra::run( Graph *graph, Vertex *start = NULL )
{
    if( graph->vertices.empty() || ( !start && !m_start )) return;   //if no vertices are there and if the algorithm was restored, or not run before, and no start is given now 

    if( m_start && start )   //if dijkstra is already run and not restored, then we assign
    {                                   //start to destination if start is given
        m_destination = start;
    }

    else if( !start && m_start ) //if no start given but the algo was already run and not restored,
    {                            //showing the previous starting vertex, so that users know the source to trace
        m_start->m_scanned = true;
        m_start->m_dist = 0;
        graph->update();
    }
    else if( start )           //if the algorithm is run first time, or run after restoring
        m_start = start;  

    priorityqueue queue;

    if( !m_destination && m_start && start )       //if there is destination in cache, we trace shortest route only
    {
        for( Vertex *vertex : graph->vertices )  
        {
            dist[ vertex ] = inf;       //initializing distances of all vertices from source as infinite
            visited[ vertex ] = false;
        }
        start = m_start;
        dist[start] = 0;             //distance of source is 0
        queue.enqueue({start, {}});
        while ( !queue.empty() )
        {
            std::pair<Vertex*, std::list<Edge*>> popped = queue.dequeue();
            start = popped.first; 
            if( visited[start] ) continue;

            start->m_dist = queue.h->getDist(popped.second); 

            shortestLink[start] = popped.second;
            visited[start] = true;            //relaxing the edges

            start->m_scanned = true;
            start->m_scanning = false;

            for( Edge* e : popped.second )
            {
                e->m_scanned = true;
            }

            graph->update();

            if( graph->m_adj[popped.first].empty()) continue;

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
                        temp.push_back(graph->m_edgeList[{start, neighbour}]);     //just pushing the edge start -> neighbour
                        queue.enqueue({neighbour, temp});                    //enqueuing into the heap tree
                        dist[neighbour] = dis;

                        neighbour->m_dist = dis;    //updating the label of neighbour vertex

                        graph->m_edgeList[{ start, neighbour }]->m_scanning = true;    //changing color of edge 
                        graph->m_edgeList[{ neighbour, start }]->m_scanning = true;
                        
                        neighbour->m_scanning = true;

                        graph->update();
                    }
                }
            }
        }
    }


    //this portion of code is for showing the shortest route from the source to the destination
    if( m_destination )  
    {
        m_start->m_scanned = true;
        m_start->m_dist = 0; 
        m_destination->m_scanned = true;
        graph->update();
        for( Edge* e : shortestLink[m_destination])   //we just show all the edges in the shortestlink of that vertex
        {
            e->m_scanned = true;
            auto v1 = e->m_v1;
            auto v2 = e->m_v2;
            v1->m_dist = queue.h->getDist(shortestLink[v1]);
            v2->m_dist = queue.h->getDist(shortestLink[v2]);
            v1->m_scanned = true;
            v2->m_scanned = true;
            
            graph->update();
        }

        float dis = queue.h->getDist(shortestLink[m_destination]);  
        if( dis != 0 )
        {
            m_destination->m_dist = dis;  
        }

        graph->update();

        m_destination = NULL;  //we clean destination everytime the route is traced for it
    }

}