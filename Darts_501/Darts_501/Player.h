/*
 *	This is the Player class and handles all things related to the player including:
 *		-	Throwing darts.
 *		-	Deciding which numbers to aim for.
 *		-	Figuring out whether the player can finish or not.
 *		-	Searching through all the potential finishes and choosing the most appropriate dart.
 *		-	Keeping track of games won and how many darts it took to finsh per game.
 *		-	Tallying the above tracked data into one collection and printing the resluts at the end of ALL games.
 *
 *
 *	Original @author D. Green.
 *
 *	© D. Green. 2020.
 *
 */

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// INCLUDES.
#include<iostream>
#include<vector>
#include "DartBoard.h"

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
constexpr int N_DART_FINISHES_SIZE = 15;

class Player
{
public:
	// CONSTRUCTORS & DESTRUCTOR.
	Player(std::string l_name, int l_innerBullSuccessRate, int l_outerBullSuccessRate, int l_singleSuccessRate, int l_doubleSuccessRate, int l_trebleSuccessRate);
	~Player();

	// MEMBER FUNCTIONS
	int throwDart(int l_throwingFor, char l_type);
	int throwForBull(int l_throwingFor);
	int throwForSingle(int l_throwingFor);
	int throwForDouble(int l_throwingFor);
	int throwForTreble(int l_throwingFor);
	int throwForFinish();
	bool searchFinishesArray();
	int searchDartBoardArr(int l_number, int randNum);
	void incrementGamesWon();
	void incrementLegsWon();
	void incrementSetsWon();
	void incrementMatchesWon();
	void increment_N_DartFinishes();
	void printWinFreqs(int l_numOfGamesPlayed);
	void resetGame();


	// GETTERS & SETTERS
	std::string getName();

	int getDartsThrownInRnd();
	void setDartsThrownInRnd(int l_thrown);

	int getNumOfDartsToThrow();

	int getRemainingScore();
	void setRemainingScore(int l_remainingScore);

	int getNumOfBullHit();
	void incrementBullHit();

	int getTurnsTaken();
	void incrementTurnsTaken();

	int getGamesWon();

	bool getIsPlaying();
	void setIsPlaying(bool l_isPlaying);

	bool getHasWon();
	void setHasWon(bool l_hasWon);

	int getLegsWon();
	void setLegsWon(int l_legsWon);

	int getSetsWon();
	void setSetsWon(int l_setsWon);

private:
	// DATA MEMBERS
	std::string m_name;

	int m_innerBullSuccessRate;
	int m_outerBullSuccessRate;
	int m_singleSuccessRate;
	int m_doubleSuccessRate;
	int m_trebleSuccessRate;
	int m_numOfDartsToThrow;
	int m_dartsThrownInRnd;
	int m_totalDartsThrownInGame;
	int m_remainingScore;
	int m_numOfBullHit;
	int m_turnsTaken;
	int m_gamesWon;
	int m_legsWon;
	int m_setsWon;
	int m_matchesWon;

	DartBoard m_dartBoard;
	int m_nDartFinishes[N_DART_FINISHES_SIZE] = { 0 };		// For tracking frequencies of n dart finishes.

	bool m_isPlaying;
	bool m_hasWon;
};