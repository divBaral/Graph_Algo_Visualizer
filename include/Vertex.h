#pragma once
#include <SFML/Graphics.hpp>

class Vertex
{
public:
	Vertex(float x, float y);
	void draw( sf::RenderWindow* window );
	void update();
	sf::Vector2f getPosition();
	~Vertex();
	
public:
	int m_val;
	sf::Vector2f m_position;
	sf::CircleShape* m_shape;
	bool m_scanned, m_scanning;
	sf::Color m_color;
	static const int m_radius 	= 20.f;

};
