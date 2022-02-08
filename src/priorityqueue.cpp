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
    return dis;
}

int heap::parentnode(int index)
{
    if (index == 0 || index == 1 || index == 2)
        return 0;
    return index / 2;
}

int heap::leftchild(int index)
{
    int left;
    if (index == 0)
        left = 1;
    else
        left = index * 2;
    return (left <= lastindex) ? left : -1;
}

int heap::rightchild(int index)
{
    int right;
    if (index == 0)
        right = 2;
    else
        right = index * 2 + 1;
    return (right <= lastindex) ? right : -1;
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
        }
        else
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
        int child;
        if(left != -1 && right != -1)
        {
            child = getDist(elements[left].second) <= getDist(elements[right].second) ? left : right;
        }
        else if(left == -1 && right != -1)
        {
            child = right;
        }
        else if(left != -1 && right == -1)
        {
            child = left;
        }
        else return;

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
    h->elements.pop_back();
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
