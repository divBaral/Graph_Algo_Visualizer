#include "Edge.h"

Edge::Edge(  Vertex* v1,  Vertex* v2, int weight )
{
	m_font.loadFromFile( "res/font.ttf" );
	m_text.setFont( m_font );
	
	m_v1		= v1;
	m_v2		= v2;
	m_weight	= weight;

	m_text.setCharacterSize(20); // in pixels, not points!
	m_text.setFillColor(sf::Color::White);
	

	//for graphics
	m_color			= sf::Color::White;
	float OFFSET	= 0;

	float x1 = v1->getPosition().x;
	float y1 = v1->getPosition().y;

	float x2 = v2->getPosition().x;
	float y2 = v2->getPosition().y;

	m_text.setPosition( (x1+x2) /2, (y1+y2)/2 );

	m_line = new sf::RectangleShape;
	m_line->setPosition( x1 + OFFSET, y1 - OFFSET );
	m_linesize.x = sqrt( pow(x2-x1, 2) + pow(y2-y1, 2) );
	m_linesize.y = 2;
	m_line->setSize( m_linesize );
	m_weight = m_linesize.x;
	m_text.setString( std::to_string(m_weight) );

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

	m_scanning = false;
	m_scanned = false;

}

void Edge::draw( sf::RenderWindow* window, int mode )
{
	m_line->setFillColor( m_color );
	window->draw( *m_line );
	
	if( mode != 1 && mode != 2 )   // bfsMode = 1 , dfsMode = 2
		window->draw( m_text );

}

void Edge::update()
{
	if( m_scanned )
		m_color = sf::Color::Black;
	else if( m_scanning )
		m_color = sf::Color::Green;
	else
		m_color = sf::Color::White;	//default
}

void Edge::restoreDefault()   //restore default the edges for running algorithms again
{
	m_scanned = m_scanning = false;
	m_line->setSize( m_linesize );
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

