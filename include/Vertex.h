/****
 * 
 * It contains class for vertices used in the program
 * 
 ****/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>
#include "sstream"

#define inf std::numeric_limits<float>::infinity()

class Vertex
{
public: //methods
	Vertex( float x, float y );
	void draw( sf::RenderWindow*, int );
	void update();
	void restoreDefault();
	sf::Vector2f getPosition();
	~Vertex();
	
public:	//data members
	float m_dist;
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_position;
	bool m_scanned, m_scanning;
	sf::Color m_color;
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;
	static const int m_radius 	= 25.f;

};