//using binary heap, a minimum heap
#pragma once

#include <iostream>
#include <vector>
#include "Edge.h"
#include "Graph.h"
#include "Vertex.h"

class priorityqueue;
class heap
{
    std::pair<Vertex*, std::list<Edge*>> *elements;    //for adding vertex and all the edges from source to the vertex
    int lastindex;
    int size;

public:
    heap();
    ~heap();
    void swap(int, int);   //swaps the elements 
    int parentnode(int);   //get the parent node
    int leftchild(int);     //get the left child node
    int rightchild(int);    //get the right child node
    void shiftup(int);         //when adding new element, to reconfigure the heap tree
    void shiftdown(int);       //when popping the root element, to reconfigure the heap tree
    float getDist(std::list<Edge*>);   //adds the edge weights that correspond to the vertex in the heap
    friend class priorityqueue;
};

class priorityqueue
{
    heap* h;    
public:
    priorityqueue();
    void enqueue(std::pair<Vertex*, std::list<Edge*>>);  //add the pair of vertex and list of edges of the route from the source
    std::pair<Vertex*, std::list<Edge*>> dequeue();     //pops the element
    bool empty();         //check if queue is empty
    ~priorityqueue();
    friend class Dijkstra;
};