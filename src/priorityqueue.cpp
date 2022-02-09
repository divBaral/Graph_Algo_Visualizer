// using binary heap, a minimum heap
#include "priorityqueue.h"

heap::heap()
{
    size = 1;
    lastindex = -1;
    elements = new std::pair<Vertex*, std::list<Edge*>>[size];
}

void heap::swap(int index1, int index2)
{
    std::pair<Vertex*, std::list<Edge*>> temp = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = temp;
}

float heap::getDist(std::list<Edge*> routes)
{
    if(routes.empty()) return 0;
    float dis = 0;
    for( Edge* edge : routes)
    {
        dis += edge->m_weight;
    }
    return dis;
}

int heap::parentnode(int index)
{
    return (index - 1) / 2;
}

int heap::leftchild(int index)
{
    return ((2 * index) + 1); 
}

int heap::rightchild(int index)
{
    return ((2 * index) + 2);
}

void heap::shiftup(int i)
{
    while (getDist(elements[parentnode(i)].second) < getDist(elements[i].second)) 
    {
        // Swap parent and current node
        swap(parentnode(i), i);
        i = parentnode(i);
    }
}

void heap::shiftdown(int i = 0)
{
    int maxIndex = i;
    
    int left = leftchild(i);
    
    if (left <= lastindex && getDist(elements[left].second) < getDist(elements[maxIndex].second)) {
        maxIndex = left;
    }
    
    int right = rightchild(i);
    
    if (right <= lastindex && getDist(elements[right].second) < getDist(elements[maxIndex].second)) {
        maxIndex = right;
    }
    
    // If i is not same as maxIndex
    if (i != maxIndex){
        swap(i, maxIndex);
        shiftdown(maxIndex);
    }


}

priorityqueue::priorityqueue()
{
    h = new heap();
}

void priorityqueue::enqueue(std::pair<Vertex*, std::list<Edge*>> e)
{
    if(h->lastindex >= h->size - 1)
    {
        std::pair<Vertex*, std::list<Edge*>>* temp = h->elements;
        h->elements = new std::pair<Vertex*, std::list<Edge*>>[h->size * 2];
        for(int i = 0; i< h->size; i++)
        {
            h->elements[i] = temp[i];
        }
        h->size *= 2;
    }
    h->lastindex++;
    h->elements[h->lastindex] = e;
    h->shiftup(h->lastindex);
}

std::pair<Vertex*, std::list<Edge*>>  priorityqueue::dequeue()
{
    std::pair<Vertex*, std::list<Edge*>> popped = h->elements[0];
    h->elements[0] = h->elements[h->lastindex];
    h->lastindex--;
    h->shiftdown();
    return popped;
}

bool priorityqueue::empty()
{
    if(h->lastindex == -1)
    {
        return 1;
    }
    return 0;
}

priorityqueue::~priorityqueue()
{
    delete h;
}
