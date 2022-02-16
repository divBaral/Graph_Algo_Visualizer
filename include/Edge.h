/****
 * 
 * It contains class for vertices used in the program
 * 
 ****/

#pragma once

#include <iostream>
#include <cmath>
#include "Vertex.h"
// #include "priorityqueue.h" 

class Edge
{
public: //methods
	Edge( Vertex* v1,  Vertex* v2, int weight = 1  );
	void draw( sf::RenderWindow* window, int );
	void update();
	void restoreDefault();
	Vertex* m_v1, *m_v2;

	~Edge();


private:

	//members required for graphics
	sf::Vector2f m_linesize;
	sf::RectangleShape* m_line;

public: //data members
	sf::Color m_color;
	bool m_scanning;
	bool m_scanned;
	long m_weight;
	sf::Font m_font;
	sf::Text m_text;
	// friend class heap;
	friend class Graph;
	friend class Dijkstra;
};