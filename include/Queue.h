#pragma once
#include "Vertex.h"

class Queue
{
    struct node
    {
        Vertex *data;
        node *next = nullptr;
    };

    node *Front = nullptr;
    node *Rear = nullptr;

public:
    bool empty(){return Front==nullptr; }
	void enqueue( Vertex *x )
	{
        node *newNode = new node;
        newNode->data = x;

        if( Front == nullptr )
            Front = Rear = newNode;
        else
        {
            Rear->next = newNode;
            Rear = newNode;
        }
	}

	Vertex* dequeue()
	{
        if( Front != nullptr )
        {
            Vertex *info = Front->data;
            node *tempNode = Front;
            Front = Front->next;
            delete tempNode;

            return info;
        }
            return NULL;
	}
};