/****
 * 
 * It contains class for vertices used in the program
 * 
 ****/

#pragma once
#include <SFML/Graphics.hpp>

class Vertex
{
public: //methods
	Vertex( float x, float y );
	void draw( sf::RenderWindow* window );
	void update();
	sf::Vector2f getPosition();
	~Vertex();
	
public:	//data members
	sf::Vector2f m_position;
	bool m_scanned, m_scanning;
	sf::Color m_color;
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;
	static const int m_radius 	= 25.f;

};
