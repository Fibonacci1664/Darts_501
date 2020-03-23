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

#pragma once

// INCLUDES.
#include<vector>
#include "Player.h"
#include "MyGraphics.h"
#include "Match.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game
{
public:
	// CONSTRUCTORS & DESTRUCTOR.
	Game(int l_numOfPlayers, int l_gamesToPlay, MyGraphics l_graphics);
	~Game();

	// MEMBER FUNCTIONS.
	void playDarts();
	void whoIsThrowingFirst();
	void showTitle();
	void showDartArt();
	void printGameOptions();
	void chooseGame(int l_gameChoice);
	void printMatchResults();

	// GETTERS & SETTERS
	int getGamesPlayed();
	void setGamesPlayed(int l_gamesPlayed);

	int getNumOfPlayers();

	void setWhoIsPlayingFirst(std::string& l_playingFirst);

	bool getIsRunning();
	void setIsRunning(bool l_isRunning);

	int getMatchesPlayed();

private:
	// DATA MEMBERS.
	std::vector<Player> m_players;
	std::vector<Match> m_matchResults;

	MyGraphics m_graphics;

	std::string m_playingFirstName;

	int m_matchesToPlay;
	int m_matchesPlayed;
	int m_gamesPlayed;
	int m_numOfPlayers;
	int m_gameChoice;

	bool m_isRunning;

	// MEMBER FUNCTIONS.
	void autoInitPlayers();
	void initPlayers();
	void determineWinner();
	void takeTurn(Player& l_player);
	void swapTurns();
};