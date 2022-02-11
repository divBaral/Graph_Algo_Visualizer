/****
 * 
 * It contains class for vertices used in the program
 * 
 ****/

#pragma once
#include <cmath>
#include "Vertex.h"
// #include "priorityqueue.h" 

class Edge
{
public: //methods
	Edge( Vertex* v1,  Vertex* v2, int weight = 1  );
	void draw( sf::RenderWindow* window );

	~Edge();


private:
	Vertex* m_v1, *m_v2;

	//members required for graphics
	sf::RectangleShape* m_line;
	sf::Vector2f m_linesize;

public: //data members
	sf::Color m_color;
	float m_weight;
	// friend class heap;
	friend class Graph;
};