// using binary heap, a minimum heap
#include "priorityqueue.h"

heap::heap()
{
    lastindex = -1;   //keeping track of the last item of heap tree
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
}

int heap::parentnode(int index)
{
    if (index == 0 || index == 1 || index == 2)
        return 0;
    return index / 2;
}

int heap::leftchild(int index)
{
    int leftchild;
    if (index == 0)
        leftchild = 1;
    else
        leftchild = index * 2;
    return (leftchild <= lastindex) ? leftchild : -1;
}

int heap::rightchild(int index)
{
    int rightchild;
    if (index == 0)
        rightchild = 2;
    else
        rightchild = index * 2 + 1;
    return (rightchild <= lastindex) ? rightchild : -1;
}

void heap::shiftup()
{
    int minindex = lastindex;
    int parentindex;
    while (minindex > 0)
    {
        parentindex = parentnode(minindex);
        if (getDist(elements[parentindex].second) < getDist(elements[minindex].second))
        {
            swap(parentindex, minindex);
            minindex = parentindex;
            continue;
        }
        break;
    }
}

void heap::shiftdown()
{
    int minindex = 0;
    while (minindex <= lastindex)
    {
        int left = leftchild(minindex);
        int right = rightchild(minindex);
        int child = getDist(elements[left].second) <= getDist(elements[right].second) ? left : right;
        if (child <= lastindex && getDist(elements[child].second) < getDist(elements[minindex].second))
        {
            swap(child, minindex);
            minindex = child;
            continue;
        }
        return;
    }
}

priorityqueue::priorityqueue()
{
    h = new heap();
}

void priorityqueue::enqueue(std::pair<Vertex*, std::list<Edge*>> e)
{
    h->lastindex++;
    h->elements.push_back(e);
    h->shiftup();
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
