#include "../include/Vertex.h"

Vertex::Vertex( float x, float y )
{

	m_shape			= new sf::CircleShape( m_radius ) ;
	m_position		= sf::Vector2f(x - m_radius , y - m_radius );
	m_color			= sf::Color::Red;
	m_scanned 		= false;
	m_scanning		= false;
	m_val			= 0;

}

void Vertex::draw( sf::RenderWindow* window )
{
	m_shape->setPosition( m_position );
	m_shape->setFillColor( m_color );
	window->draw( *m_shape );

}

void Vertex::update()
{

	if ( m_scanned )
		m_color = sf::Color::Blue;
	if ( m_scanning )
		m_color = sf::Color::Green;
}

sf::Vector2f Vertex::getPosition()
{
	return m_position;
}

Vertex::~Vertex()
{
	if ( m_shape ) {
		delete m_shape;
		m_shape = nullptr;
	}
}
