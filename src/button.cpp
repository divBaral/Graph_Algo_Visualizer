#include "Button.h"

std::map<button*, int> button::m_modes;

button::button(){}
button::~button(){}

void button::createButton(sf::Vector2f size, sf::Vector2f pos)
{
	/*setting coordinates for generating button area*/
	buttonArea.width = size.x;
	buttonArea.height = size.y;
	//top left corner coordinates of rectangular button
	buttonArea.left = pos.x;
	buttonArea.top = pos.y;

	shape.setSize(size);
	shape.setPosition(pos);
	
	if ( !m_font.loadFromFile( "../res/font.ttf" ) )
		std::cerr << "Font not loaded\n";
	
	m_text.setFont( m_font );
	m_text.setString( name );
	m_text.setPosition( pos );
	m_text.setCharacterSize( 20 );
	m_text.setFillColor( sf::Color::Black );
}

void button::draw(sf::RenderWindow* window)
{
	window->draw( shape );
	window->draw( m_text );
}

void button::update( sf::RenderWindow* window )
{
	int MouseX = sf::Mouse::getPosition(*window).x;
	int MouseY = sf::Mouse::getPosition(*window).y;

	if(buttonArea.contains(MouseX, MouseY))
	{
		shape.setFillColor(sf::Color(217, 106, 149));
	}
	else
	{
		shape.setFillColor(sf::Color(209, 188, 186));
	}

}
