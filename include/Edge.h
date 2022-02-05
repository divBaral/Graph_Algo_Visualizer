#pragma once
#include "Vertex.h"
#include <cmath> 


class Edge
{
public:
	Edge( Vertex* v1,  Vertex* v2, int weight = -1  );
	void draw( sf::RenderWindow* window );

	~Edge();


private:
	float m_weight;
	Vertex* m_v1, *m_v2;

	//members required for graphics
	sf::RectangleShape* m_line;
	sf::Vector2f m_linesize;
	sf::Color m_color;

};