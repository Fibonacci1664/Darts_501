/*
 *	This is the Game class and handles all things rlated to the game such as:
 *		-	Initializing players.
 *		-	Controlling flow by alternating players turns.
 *		-	Keeping track of game state.
 *		-	Determining winner.
 *
 *
 *	Original @author D. Green.
 *
 *	© D. Green. 2020.
 */

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // INLCUDES.
#include "Game.h"
#include <iostream>
#include "MyGraphics.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORS & DESTRUCTOR.
Game::Game(int l_numOfPlayers, int l_matchesToPlay, MyGraphics l_graphics) :
	m_numOfPlayers(l_numOfPlayers), m_matchesToPlay(l_matchesToPlay), m_gamesPlayed(0), m_graphics(l_graphics)
{
	m_isRunning = true;
	m_gameChoice = 0;
	m_matchesPlayed = 0;

	// Carrry out basic validation to ensure maximum of 2 players only.
	if (m_numOfPlayers > 2)
	{
		std::cerr << "Sorry you cannot have more than 2 players!\n";
		m_isRunning = false;
		return;
	}

	printGameOptions();
	showDartArt();
	showTitle();
	Sleep(1000);
	m_graphics.publicClearTitleScreen();	
}

Game::~Game()
{
	std::cout << "Game object destroyed!\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS.
void Game::printGameOptions()
{
	do
	{
		std::cout << "Please choose from the following options:> \n"
			<< "\t1. Fully automated simulated.\n"
			<< "\t\t-	Simulation of a game of 501.\n"
			<< "\t\t-	Two Players.\n"
			<< "\t\t-	Pre-programmed success rates.\n"
			<< "\t2. Manual simulation.\n"
			<< "\t\t-	Simulation of a game of 501.\n"
			<< "\t\t-	Two Players.\n"
			<< "\t\t-	User entered success rates.\n"
			<< "\t3. Interactive game.\n"
			<< "\t\t-	Interactive game of 501.\n"
			<< "\t\t-	Two players; User and Computer; User enters their own success rates.\n"
			<< "\t\t-	Computer has pre-programmed success rates.\n"
			<< "\n:> ";

		std::cin >> m_gameChoice;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	} while (!std::cin.good() || (m_gameChoice > 3 || m_gameChoice < 1));

	chooseGame(m_gameChoice);	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::chooseGame(int l_gameChoice)
{
	std::cout << "this works\n";

	if (l_gameChoice == 1)
	{
		// Use this for auto creation of players. (MAX TWO PLAYERS)
		autoInitPlayers();
	}
	else if (l_gameChoice == 2)
	{
		// Use this for manually entering players names and success rates.
		initPlayers();
	}
	else
	{
		std::cout << "Interactive game not built yet.\n";
	}

	m_graphics.publicClearScreenFull();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::showDartArt()
{
	// We have this so we can pass by ref, not copy values.
	int xPos1 = 0;
	int xPos2 = 83;

	m_graphics.publicDrawString(xPos1, 0, "                       /''''''''''\\\n");			// 40 hashes
	m_graphics.publicDrawString(xPos1, 1, "----={{{{{{{}<<<<<====<------------>\n");
	m_graphics.publicDrawString(xPos1, 2, "                       \\,,,,,,,,,,/\n");

	m_graphics.publicDrawString(xPos2, 0, " /''''''''''\\\n");			
	m_graphics.publicDrawString(xPos2, 1, "<------------>====>>>>>{}}}}}}}=----\n");		// 40 hashes
	m_graphics.publicDrawString(xPos2, 2, " \\,,,,,,,,,,/ \n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::showTitle()
{
	int xPos = 37;

	m_graphics.publicDrawString(xPos, 0, "#############################################\n");			// 45 hashes
	m_graphics.publicDrawString(xPos, 1, "#########                           #########\n");
	m_graphics.publicDrawString(xPos, 2, "#########    WELCOME TO 501 DARTS   #########\n");
	m_graphics.publicDrawString(xPos, 3, "#########                           #########\n");
	m_graphics.publicDrawString(xPos, 4, "#############################################\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::autoInitPlayers()
{
	if (m_numOfPlayers > 1)
	{
		Player player_1("Joe", 71, 73, 80, 78, 80);
		Player player_2("Sid", 76, 66, 80, 82, 76);

		m_players.push_back(player_1);
		m_players.push_back(player_2);
	}
	else
	{
		Player player_1("Joe", 68, 70, 80, 75, 77);
		m_players.push_back(player_1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::initPlayers()
{
	int xPos = 0;

	for (int i = 0; i < getNumOfPlayers(); ++i)
	{
		// Formatting.
		if (i > 0)
		{
			std::cout << '\n';
		}

		std::string name;
		int innerBullSuccessRate;
		int outerBullSuccessRate;
		int singleSuccessRate;
		int doubleSuccessRate;
		int trebleSuccessRate;

		do
		{
			std::cout << "Please enter the name of Player " << (i + 1) << ":> ";
			std::cin >> name;
		} while (!isalpha(name[0]));

		do
		{
			std::cout << "\nNow please enter the percentage success rate of hitting an inner bull (50) for " << name << ":> ";
			std::cin.clear();							// Clear any previous input error flags that were set.
			std::cin.ignore(1000, '\n');				// Then ignore 1000 characters or until a new line is found.
			std::cin >> innerBullSuccessRate;
		} while (!std::cin.good());						// While the input is not good, i.e. it is not of the data type that was expected. Keep asking.

		do
		{
			std::cout << "\nNow please enter the percentage success rate of hitting an outer bull (25) for " << name << ":> ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cin >> outerBullSuccessRate;
		} while (!std::cin.good());

		do
		{
			std::cout << "\nNow please enter the percentage success rate of hitting singles for " << name << ":> ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cin >> singleSuccessRate;
		} while (!std::cin.good());

		do
		{
			std::cout << "\nNow please enter the percentage success rate of hitting doubles for " << name << ":> ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cin >> doubleSuccessRate;
		} while (!std::cin.good());

		do
		{
			std::cout << "\nNow please enter the percentage success rate of hitting trebles for " << name << ":> ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cin >> trebleSuccessRate;
		} while (!std::cin.good());

		std::cin.clear();
		std::cin.ignore(1000, '\n');

		// Create a vector that holds Player objects with their names and success rates.
		m_players.push_back(Player(name, innerBullSuccessRate, outerBullSuccessRate, singleSuccessRate, doubleSuccessRate, trebleSuccessRate));
	}
}
// End initPlayers().

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::whoIsThrowingFirst()
{
	std::string first;
	int xPos = 0;

	do
	{
		std::cout << "\nWho would you like to throw first ";

		// Print names of players.
		for (int i = 0; i < getNumOfPlayers(); ++i)
		{
			std::cout << ": " << m_players[i].getName() << " ";
		}

		std::cout << ":> ";

		std::cin >> first;
	} while (!isalpha(first[0]) || (m_players[0].getName() != first && m_players[1].getName() != first));
	/*
	 * A simple validation above - While the first element of whatever was typed is NOT a letter
	 * OR what was typed is not the same as any of the players names, then keep asking who you'd like to go first
	 * because your clearly either typing a number or a name that doesn't exist in the vector of players.
	 */

	setWhoIsPlayingFirst(first);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::playDarts()
{
	std::cout << '\n';
	std::cout << "\n##########  Game: " << getGamesPlayed() + 1 << "  ##########\n";
	std::cout << '\n';

	if (m_numOfPlayers == 1)
	{
		m_players[0].setIsPlaying(true);

		// START OF A 1 PLAYER GAME.
		while (m_players[0].getRemainingScore() > 0)
		{
			takeTurn(m_players[0]);
		}
		// END OF A 1 PLAYER GAME.
	}
	else
	{
		// START OF A 2 PLAYER GAME.
		while (m_players[0].getRemainingScore() > 0 && m_players[1].getRemainingScore() > 0)
		{
			takeTurn(m_players[0]);
			takeTurn(m_players[1]);
		}
		// END OF A 2 PLAYER GAME.
	}

	++m_gamesPlayed;

	if (m_numOfPlayers > 1)
	{
		determineWinner();
		swapTurns();
		m_players[0].resetGame();
		m_players[1].resetGame();
	}
	else
	{
		m_players[0].resetGame();
	}

	if (m_matchesPlayed == m_matchesToPlay)
	{
		for (int i = 0; i < m_numOfPlayers; ++i)
		{
			m_players[i].printWinFreqs(m_gamesPlayed);
		}
	}
}
// End playDarts().

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::takeTurn(Player& l_player)
{
	if (l_player.getIsPlaying())
	{
		std::cout << "\n##########  " << l_player.getName() << " Turn " << "  ##########" << '\n';

		if (m_numOfPlayers > 1)
		{
			// Swap players isPlaying status to the opposite of whatever it currently is, do this each turn.
			m_players[0].setIsPlaying(!m_players[0].getIsPlaying());
			m_players[1].setIsPlaying(!m_players[1].getIsPlaying());
		}

		// Keep looping until we've thrown the amount of darts we're supposed to throw in each round i.e. 3.
		while (l_player.getDartsThrownInRnd() < l_player.getNumOfDartsToThrow())
		{
			std::cout << l_player.getName() << " score : " << l_player.getRemainingScore() << '\n';
			int numberHit = 0;
			int scoreRemaining = l_player.getRemainingScore();

			// If our score is greater than 170, i.e. no potential finish, then simply throw for treble 20's
			if (scoreRemaining > 170)
			{
				numberHit = l_player.throwDart(20, 't');		// Throw for a treble 't' 20.
				std::cout << "Dart number " << l_player.getDartsThrownInRnd() << " scored: " << numberHit << '\n';
				l_player.setRemainingScore(l_player.getRemainingScore() - numberHit);
			}
			else              // Score must be <= 170
			{
				bool canFinish = l_player.searchFinishesArray();

				/*
				 * If we cant finish and yet our score is < 170, then our score remaining must be either,
				 * 169, 168, 166, 165, 163, 162 or 159, NO POSSIBLE FINISHES!, therefore just throw for treble 20.
				 */
				if (!canFinish)
				{
					numberHit = l_player.throwDart(20, 't');
					std::cout << "Dart number " << l_player.getDartsThrownInRnd() << " scored: " << numberHit << '\n';
				}
				else
				{
					numberHit = l_player.throwForFinish();
					std::cout << "Dart number " << l_player.getDartsThrownInRnd() << " scored: " << numberHit << '\n';
				}

				/*
				 * This check is due to the fact that you need a score of 2 at the very min to be able to finish on double 1.
				 */
				if (((scoreRemaining - numberHit) < 2) && (scoreRemaining - numberHit) != 0)
				{
					l_player.setRemainingScore(l_player.getRemainingScore());	// Player must have bust, so score remains at whatever it was.
					std::cout << "Dart number " << l_player.getDartsThrownInRnd() << " BUST!  ##########\n";
				}
				else
				{
					l_player.setRemainingScore(l_player.getRemainingScore() - numberHit);				// Reduce score by number hit amount.

					// Check if weve won (checked out).
					if (l_player.getRemainingScore() == 0)		// We must have finshed.
					{
						if (m_numOfPlayers > 1)
						{
							m_players[1].setIsPlaying(false);				/*
																			 * If player 1 has won the game we need to stop player 2 from entering the if statment
																			 * at the start of this entire function thereby stopping them taking their next turn as this
																			 * particular game is over. Without this we can have a situation were player 1 can win
																			 * AND then player 2 on the very next turn can also win should they be able to finish.
																			 * this leads to incorrect totalling of win frequencies and can be noticed if one pays
																			 * close attention to the total num of games played vs the total that is being tallied in the
																			 * nDartFinishes array while using the debugger.
																			 */
						}

						l_player.setHasWon(true);
						l_player.incrementGamesWon();			// Used for tracking n-darts finish frequencies.
						l_player.incrementLegsWon();			// Used for tracking leg/sets/match winning frequencies.

						// If the player has won 7 legs they have won a set, this is tallied and legs for both players are reset to 0.
						if (l_player.getLegsWon() == 7)
						{
							l_player.incrementSetsWon();
							m_players[0].setLegsWon(0);
							m_players[1].setLegsWon(0);

							// If the player has won 7 sets they have won a match.
							if (l_player.getSetsWon() == 7)
							{
								Match results;
								results.result_1 = m_players[0].getSetsWon();
								results.result_2 = m_players[1].getSetsWon();
								results.tally += 1;

								/*
								 * This ensures we populate the vector with the first set of results, and thereafter we are then checking against those and subsequent results
								 * If we find a match, increase the tally for those results otherwise, push back the new results onto the end of the vector.
								 * There are only 12 possible combinations of results. So the vector should NEVER end up larger than 12 elements.
								 */
								if (m_matchResults.size() == 0)
								{
									m_matchResults.push_back(results);
								}
								else
								{
									bool matchFound = false;

									for (int i = 0; i < m_matchResults.size(); ++i)
									{
										// Check if we have these exact results already, if so increment the tally.
										if (m_matchResults[i].result_1 == results.result_1 && m_matchResults[i].result_2 == results.result_2)
										{
											// We found a matching score so just add one to the tally for this result and get the hell out of this loop.
											m_matchResults[i].tally += 1;
											matchFound = true;
											break;
										}
									}

									// If we haven't found a match then we must have a new result out of the 12 possibilities.
									if (!matchFound)
									{
										/*
										 * If we dont break out here after adding a new element this new result will be accounted for in the for loops condition and we will continue to check
										 * beacuse we are not at m_matchResults.size() yet due to just adding another element, this ends up resulting in a match for the above if statement which
										 * will then tally incorrectly.
										 */
										m_matchResults.push_back(results);
									}
								}

								// By this point a match has been won, increment the amount of matches played and reset the amount of sets won back to zero
								l_player.incrementMatchesWon();
								++m_matchesPlayed;
								m_players[0].setSetsWon(0);
								m_players[1].setSetsWon(0);
							}	
						}

						l_player.increment_N_DartFinishes();
						break;
					}
				}
			}
		}

		l_player.setDartsThrownInRnd(0);		// Reset the amount of darts thrown.
		l_player.incrementTurnsTaken();
	}
}
// End takeTurn().

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::determineWinner()
{
	// Who has won.
	if (m_players[0].getHasWon())
	{
		std::cout << "\n##########  " << m_players[0].getName() << " HAS WON!  ##########\n";
	}
	else if (m_players[1].getHasWon())
	{
		std::cout << "\n##########  " << m_players[1].getName() << " HAS WON!  ##########\n";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::swapTurns()
{
	// Whoever won the last game throws last in the next game.
	if (m_players[0].getHasWon())
	{
		m_players[0].setIsPlaying(false);
		m_players[1].setIsPlaying(true);
	}
	else if (m_players[1].getHasWon())
	{
		m_players[1].setIsPlaying(false);
		m_players[0].setIsPlaying(true);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::printMatchResults()
{
	/*
	 * First to 7 legs in 1 set.
	 * First to 7 sets in 1 match.
	 * Even a small number of matches can result in thousands of individual 501 games being played.
	 */

	 /*
	  * Result 1 will ALWAYS be player 1 score and result 2 will ALWAYS be players 2 score
	  * this is due to how they are populated in the Match vector in the takeTurn function.
	  */

	std::cout << "\nComplete matches played : " << m_matchesPlayed << " over : " << getGamesPlayed() << " games.\n";

	std::cout << "\n\t" << m_players[0].getName() << "\t : \t" << m_players[1].getName() << "\t\t Frequency\n";

	// Loop over all match results calculating and printing each result and the frequency of occurence.
	for (int i = 0; i < m_matchResults.size(); ++i)
	{
		std::cout << "\n\t " << m_matchResults[i].result_1 << "\t : \t " << m_matchResults[i].result_2 << "\t\t    " << ((double)m_matchResults[i].tally / m_matchesPlayed) * 100 << "%\n";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GETTERS & SETTERS.
int Game::getGamesPlayed()
{
	return m_gamesPlayed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::setGamesPlayed(int l_gamesPlayed)
{
	m_gamesPlayed = l_gamesPlayed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Game::getMatchesPlayed()
{
	return m_matchesPlayed;
}

int Game::getNumOfPlayers()
{
	return m_numOfPlayers;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::setWhoIsPlayingFirst(std::string& l_playingFirst)
{
	m_playingFirstName = l_playingFirst;

	if (m_numOfPlayers > 1)
	{
		// Set who goes first.
		if (m_playingFirstName == m_players[0].getName())
		{
			m_players[0].setIsPlaying(true);
		}
		else
		{
			m_players[1].setIsPlaying(true);
		}
	}
	else
	{
		m_players[0].setIsPlaying(true);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::getIsRunning()
{
	return m_isRunning;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::setIsRunning(bool l_isRunning)
{
	m_isRunning = l_isRunning;
}

