//using binary heap, a minimum heap
#include <iostream>
#include <vector>
#include "Edge.h"
#include "Graph.h"
#include "Vertex.h"

class priorityqueue;
class heap
{
    std::vector<std::pair<Vertex*, std::list<Edge*>>> elements;
    int size;
    int lastindex;

public:
    heap();
    void swap(int, int);
    int parentnode(int);
    int leftchild(int);
    int rightchild(int);
    void shiftup();
    void shiftdown();
    float getDist(std::list<Edge*>);
    friend class priorityqueue;
};

class priorityqueue
{
    heap* h;
public:
    priorityqueue();
    void enqueue(std::pair<Vertex*, std::list<Edge*>>);
    std::pair<Vertex*, std::list<Edge*>> dequeue();
    ~priorityqueue();
};