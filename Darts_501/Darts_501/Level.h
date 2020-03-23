/*
 *	This is the 'Level' class and handles all things related to generating a window to display a checkout table: *
 *
 *	Original @author D. Green.
 *
 *	© D. Green. 2020.
 *
 */

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// INCLUDES.
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Level
{
public:
	// CONSTRUCTORS & DESTRUCTOR.
	Level(sf::RenderWindow* p_window);
	~Level();

	// MEMBER FUNCTIONS.
	void render();

private:
	// DATA MEMBERS.
	sf::RenderWindow* m_window;
	sf::Texture bgTexture;
	sf::RectangleShape rect;

	// MEMBER FUNCTIONS.
	void beginDraw();
	void endDraw();
};