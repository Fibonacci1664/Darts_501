// INCLUDES
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MyGraphics.h"
#include "Level.h"
#include "Game.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////

const int WINDOW_WIDTH = 675;
const int WINDOW_HEIGHT = 675;

// For handling window events: Close and Resize.
void windowProcess(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		default:
			// Don't handle other events.
			break;
		}
	}
}

// MAIN
int main()
{
	static bool seeded = false;

	if (!seeded)
	{
		srand(std::time(nullptr));
		seeded = true;
	}

	//Create the window.
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CHECKOUT TABLE");
	window.setPosition(sf::Vector2i(1900 - WINDOW_WIDTH, 200));

	// Initialise input and level objects.
	Level level(&window);
	MyGraphics graphics;

	//graphics.publicShowConsoleCursor(false);		// Disable the output windows cursor from blinking.
	graphics.publicSetColor(14, 0);					// Set colour to yellow on black.

	bool gameCreated = false;	

	// Game Loop.
	while (window.isOpen())
	{
		// Handle window events, closing or resizing.
		windowProcess(&window);

		// Call standard game loop functions (input, update and render).
		level.render();

		/*
		 * This was required because if a game was created before the level then the darts checkout image
		 * would not render and the SFML window would simply be a white window.
		 */
		if (!gameCreated)
		{
			// Fixed at two players only. If more players are passed, this is checked and causes an error and the program to exit.
			int numOfPlayers = 2;
			int gamesToPlay = 100;

			/*
			 * Create a game with 2 players to play 1000 games(not rounds), each game consists of xyz amount of rounds,
			 * dependant on how long it takes a player to win.
			 */
			Game game(numOfPlayers, gamesToPlay, graphics);

			gameCreated = true;

			if (!(game.getIsRunning()))
			{
				return 0;
			}
			else
			{
				if (numOfPlayers > 1)
				{
					// Decide who goes first.
					game.whoIsThrowingFirst();
				}

				// MAIN GAME LOOP.
				while (game.getGamesPlayed() < gamesToPlay)
				{
					game.playDarts();
				}

				game.printMatchResults();
			}			
		}
	}

	return 0;
}