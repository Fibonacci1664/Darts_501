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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Game
{
public:
	Game(int l_numOfPlayers, int l_gamesToPlay, MyGraphics l_graphics);
	~Game();

	// MEMBER FUNCTIONS.
	void playDarts();
	void whoIsThrowingFirst();
	void showTitle();
	//void showCheckOutTable();

	// GETTERS & SETTERS.
	int getGamesToPlay();
	void setGamesToPlay(int l_gamesToPlay);

	int getGamesPlayed();
	void setGamesPlayed(int l_gamesPlayed);

	int getNumOfPlayers();

	void setWhoIsPlayingFirst(std::string& l_playingFirst);

	bool getIsRunning();
	void setIsRunning(bool l_isRunning);

private:
	// DATA MEMBERS.
	std::vector<Player> m_players;
	int m_gamesToPlay;
	int m_gamesPlayed;
	int m_numOfPlayers;
	MyGraphics m_graphics;

	std::string m_playingFirstName;

	bool m_isRunning;

	// MEMBER FUNCTIONS.
	void autoInitPlayers();
	void initPlayers();
	void determineWinner();
	void overallWinner();
	void takeTurn(Player& l_player);
	void swapTurns();
};

