#include <iostream>
#include "Edge.h"
Edge::Edge(  Vertex* v1,  Vertex* v2, int weight )
{
	m_v1		= v1;
	m_v2		= v2;
	m_weight	= weight;

	//for graphics
	m_color			= sf::Color::Red;
	float OFFSET	= 0;

	float x1 = v1->getPosition().x;
	float y1 = v1->getPosition().y;

	float x2 = v2->getPosition().x;
	float y2 = v2->getPosition().y;

	m_line = new sf::RectangleShape;
	m_line->setPosition( x1 + OFFSET, y1 - OFFSET );
	m_linesize.x = sqrt( pow(x2-x1, 2) + pow(y2-y1, 2) );
	m_linesize.y = 2;
	m_line->setSize( m_linesize );

	double angle;
	if ( fabs(x2 - x1) < 0.005 ) {
		if ( y2 > y1 )
			angle = -90;
		else
			angle = 90;
	} else {
		float x = x2 - x1;
		float y = y2 - y1;
		float slope = (y2 - y1) / (x2 - x1);
		angle = 180/3.14 * atan( slope );

		if ( x < 0 ) {
			if ( y < 0 ) 
				angle -= 180;
			else 
				angle += 180;
		}
	}
	// std::cerr << x1 << ","<<y1;

	m_line->setRotation( angle );

}

void Edge::draw( sf::RenderWindow* window )
{
	m_line->setFillColor( m_color );
	window->draw( *m_line );

}

 Edge::~Edge()
{
	if ( m_v1 )
		delete m_v1;
	if ( m_v2 )
		delete m_v2;
	if ( m_line )
		delete m_line;
}