#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class Level
{
public:

	Level(sf::RenderWindow* p_window);
	~Level();

	void render();

private:
	void beginDraw();
	void endDraw();

	sf::RenderWindow* m_window;

	sf::Texture bgTexture;
	sf::RectangleShape rect;
};

