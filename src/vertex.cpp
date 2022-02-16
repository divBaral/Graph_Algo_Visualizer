#include "Vertex.h"

Vertex::Vertex( float x, float y )
{
	m_font.loadFromFile( "../res/Walkway_Black.ttf" );
	m_text.setFont( m_font );
	
	m_dist	= inf;   // this is for label of Dijkstra algorithm

	m_text.setString( std::to_string( m_dist ) );
	//m_text.setCharacterSize(24); // in pixels, not points!
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(18);

	m_texture = new sf::Texture[4];
	if ( !m_texture[0].loadFromFile("../res/vertex0.png") || !m_texture[1].loadFromFile("../res/vertex1.png") || !m_texture[2].loadFromFile("../res/vertex2.png") )
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
	m_text.setPosition( x - m_radius / 3 , y - m_radius * 1.5 );
	
  

	m_color			= sf::Color::Blue;
	m_scanned 		= false;
	m_scanning		= false;

}

void Vertex::draw( sf::RenderWindow* window, int mode )
{
	
	window->draw( *m_sprite );
	if( mode == 0 )    //dijkstraMode = 0
		window->draw( m_text );

}

void Vertex::update()
{
	if ( m_scanned )
		m_sprite->setTexture( m_texture[2] );
	else if ( m_scanning )
		m_sprite->setTexture( m_texture[0] );
	else
		m_sprite->setTexture( m_texture[1] );  //default

	std::stringstream ss;  //for converting float to string
	ss << m_dist;
	m_text.setString( ss.str() );   //change the label in dijkstra algorithm
}

void Vertex::restoreDefault()		 //restore default the edges for running algorithms again
{
	m_scanned = m_scanning = false;
	m_dist = inf;
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