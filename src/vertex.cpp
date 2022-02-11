#include "Vertex.h"
#include <iostream>

Vertex::Vertex( float x, float y )
{

	m_texture = new sf::Texture[4];
	if ( !m_texture[0].loadFromFile("res/vertex0.png") || !m_texture[1].loadFromFile("res/vertex1.png") || !m_texture[2].loadFromFile("res/vertex2.png") )
	{
		std::cerr << "Texture not loaded ";
	}

	m_sprite = new sf::Sprite;
	m_texture[0].setSmooth( true );
	m_texture[1].setSmooth( true );
	m_texture[2].setSmooth( true );
	m_sprite->setTexture( m_texture[1] );
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
		m_sprite->setTexture( m_texture[2] );
	if ( m_scanning )
		m_sprite->setTexture( m_texture[0] );
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
