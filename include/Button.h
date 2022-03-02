/****
 * 
 * This headerfile contains code for designing buttons, only rectangular buttons
 * 
 ****/
#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class button
{
public:	//methods
	button();
	~button();

	void createButton(sf::Vector2f, sf::Vector2f); //(size, position)
	void draw(sf::RenderWindow*);
	void update(sf::RenderWindow*);
	sf::Rect<float> getRect(){return buttonArea;}
	button* getButtonByPosition( int x, int y ) 
	{
		if ( buttonArea.contains (x, y))
			return this;
		return nullptr;
	}

	std::string name;
	sf::Font m_font;
	sf::Text m_text;

public:	//data members
	sf::Rect<float> buttonArea;
	sf::RectangleShape shape;
	static std::map<button*, int> m_modes;
	
};
