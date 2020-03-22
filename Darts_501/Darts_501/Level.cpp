#include "Level.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORS / DESTRUCTOR
// Constructor initializer list, expilcitly initializing the m_window(Type Window) when a game object is created.
Level::Level(sf::RenderWindow* l_window)
{
	m_window = l_window;

	if (!bgTexture.loadFromFile("gfx/finishes.jpg"))
	{
		std::cerr << "Could not load finishes image!\n";
	}

	rect.setSize(sf::Vector2f(l_window->getSize().x, l_window->getSize().y));
	rect.setTexture(&bgTexture);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

Level::~Level() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void Level::render()
{
	beginDraw();					// Clear screen.
	m_window->draw(rect);
	endDraw();						// Display.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prep the buffer for drawing.
void Level::beginDraw()
{
	m_window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	m_window->display();
}