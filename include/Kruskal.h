#include <iostream>
#include "Graph.h"
#include <stack>
namespace KRUSKAL {
bool sortComparer( Edge* a, Edge* b ) {
    return a->m_weight <= b->m_weight;
}


std::vector<Edge*> sortEdges( std::vector <Edge*> edges ) {
    std::sort(edges.begin(), edges.end(), sortComparer);
    return edges;
}

struct subset {
  int rank;
  int parent;
};

int find( std::vector<subset> & subsets, int i ) {
    if ( subsets[i].parent != i ) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void union_edges( std::vector<subset> & subsets, int a, int b) 
{
    int aroot = find(subsets, a);
    int broot = find(subsets, b);

    if ( subsets[aroot].rank < subsets[broot].rank ) {
        subsets[aroot].parent = broot;
    }
    else if ( subsets[aroot].rank > subsets[broot].rank ) 
    {
        subsets[broot].parent = aroot;
    }
    else 
    {
        subsets[broot].parent = aroot;
        subsets[broot].rank++;
    }
}
bool isConnected( Graph* g )
{
    //DFS 
    Vertex *s = g->vertices.front();

    std::stack<Vertex*> S;
    S.push( s );
    std::map < Vertex* , bool > visited;
    visited[s] = true;

    while (  ! S.empty() ) {
        auto v = S.top();
        S.pop();
        for ( auto u : g->m_adj[v] )
        {
            if ( !visited[u] ) {
                S.push( u );
                visited[u] = true;

            }
        }



    }
    for ( auto it : g->vertices ) {
        
        if ( ! visited[it] )
            return false;
    }
    return true;




   /* //
*/
   
}

void  kruskalMST( Graph* g ) 
{
    int i = 0;
    //maps vertices to integer index

    if( !g || g->vertices.empty() || g->edges.empty() || !isConnected( g )) return; 

    for ( auto it = g->vertices.begin(); it != g->vertices.end() ; ++it )
        g->visited[*it] = i++;
    //construct array of edges from list or change list in graph to vector
    std::vector<Edge*> edges;
    for ( auto it = g->edges.begin(); it != g->edges.end() ; ++it )
        edges.push_back( *it );
   
    edges  =  sortEdges( edges );

    std::vector<subset> subsets( edges.size() );

    for ( int i = 0; i < edges.size() ; ++i ) 
    {
        subsets[i].rank = 0;
        subsets[i].parent = i;
    }

    int e = 0;
     i = 0;
     //don't run if already tree
	if ( g->edges.size() == g->vertices.size() - 1 ) {
        for ( auto it : edges )
        {
            it->m_scanned = true;
            it->m_v1->m_scanned = true;
            it->m_v2->m_scanned = true;
            g->update();
        }
        return ;
    }

    while ( e < ( g->vertices.size()  - 1) ) 
    {
        Edge* next_edge = edges[i++];

        next_edge->m_scanning = true;
        next_edge->m_v1->m_scanning = true;
        next_edge->m_v2->m_scanning = true;


        int a = find( subsets, g->visited[next_edge->m_v1] );   //visited[next_edges->m_v1]
        int b = find( subsets, g->visited[next_edge->m_v2] );

        if ( a != b ) 
        {
			//resultMST.push_back(next_edge);
            next_edge->m_scanned = true;
            next_edge->m_v1->m_scanned = true;
            next_edge->m_v2->m_scanned = true;
            union_edges(subsets, a, b);
            ++e;
        }
        g->update();
    }
    //return resultMST;
}
}