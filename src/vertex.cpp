#include "Vertex.h"
#include <iostream>

Vertex::Vertex( float x, float y )
{


	m_texture = new sf::Texture;
	if ( !m_texture->loadFromFile("res/vertex1.png") )
		std::cerr << "Texture not loaded ";
	m_sprite = new sf::Sprite;
	m_texture->setSmooth( true );
	m_sprite->setTexture( *m_texture[0] );
	m_sprite->setOrigin( m_radius, m_radius );
	
	
	m_position		= sf::Vector2f( x, y );
	m_sprite->setPosition( m_position );
	
  

	m_color			= sf::Color::Blue;
	m_scanned 		= false;
	m_scanning		= false;

}

void Vertex::draw( sf::RenderWindow* window )
{
	
	window->draw( *m_sprite );

}

void Vertex::update()
{

	if ( m_scanned )
		m_sprite->setTexture( * m_texture[2] )
	if ( m_scanning )
		m_sprite->setTexture( * m_texture[1] );
}

sf::Vector2f Vertex::getPosition()
{
	return m_position;
}

Vertex::~Vertex()
{
	if ( m_texture )
		delete m_texture;
	if ( m_sprite )
		delete m_sprite;
}
