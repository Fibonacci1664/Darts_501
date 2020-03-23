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

// INCLUDES.
#include "Player.h"
#include <Windows.h>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORS & DESTRUCTOR.
Player::Player(std::string l_name, int l_innerBullSuccessRate, int l_outerBullSuccessRate, int l_singleSuccessRate, int l_doubleSuccessRate, int l_trebleSuccessRate) :
	m_name(l_name),
	m_innerBullSuccessRate(l_innerBullSuccessRate),
	m_outerBullSuccessRate(l_outerBullSuccessRate),
	m_singleSuccessRate(l_singleSuccessRate),
	m_doubleSuccessRate(l_doubleSuccessRate),
	m_trebleSuccessRate(l_trebleSuccessRate)
{
	m_numOfDartsToThrow = 3;
	m_dartsThrownInRnd = 0;
	m_totalDartsThrownInGame = 0;
	m_remainingScore = 501;
	m_numOfBullHit = 0;
	m_turnsTaken = 0;
	m_gamesWon = 0;
	m_legsWon = 0;
	m_setsWon = 0;
	m_matchesWon = 0;

	m_isPlaying = false;
	m_hasWon = false;
}

Player::~Player()
{
	std::cout << "Player object destroyed!\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS.
int Player::throwDart(int l_throwingFor, char l_type)
{
	// Put in a sleep call to slow things down and print of the scores as the go, including numbers hit.
	//Sleep(1000);

	++m_dartsThrownInRnd;						// Tracks darts in each round.
	++m_totalDartsThrownInGame;					// Tracks total darts in each game.

	int numberHit = 0;

	/*
	 * treble = 't'
	 * double = 'd'
	 * single = 's'
	 * inner bull = 'i'
	 * outer bull = 'o'
	 */

	switch (l_type)
	{
	case 't':
		numberHit = throwForTreble(l_throwingFor);
		break;
	case 'd':
		numberHit = throwForDouble(l_throwingFor);
		break;
	case 's':
		numberHit = throwForSingle(l_throwingFor);
		break;
	case 'i': case 'o':
		numberHit = throwForBull(l_throwingFor);
		break;
	default:
		std::cout << "Oops, somthing went wrong switching the type you were throwing for!\n";
	}

	return numberHit;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::throwForBull(int l_throwingFor)
{
	int randNum = rand() % 100 + 1;		// Generate a random number between 1 - 100.

	// Prints the random number that was rolled if the user needs to check things are working correctly.
	std::cout << m_name << "Throwing for " << l_throwingFor << '\n';
	std::cout << m_name << "Random number rolled for : " << " = " << randNum << '\n';

	if (l_throwingFor == 50)
	{
		if (randNum <= m_innerBullSuccessRate)
		{
			std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " scored a 50!\n";
			++m_numOfBullHit;
			return 50;
		}
		else
		{
			int randTwenty = rand() % 20 + 1;
			std::cout << m_name << " Missed a 50 and scored : " << randTwenty << '\n';
			return randTwenty;				// Return a random num between 1 - 20.
		}
	}
	else if (l_throwingFor == 25)
	{
		if (randNum <= m_outerBullSuccessRate)
		{
			std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " scored a 25!\n";
			return 25;
		}
		else
		{
			int randTwenty = rand() % 20 + 1;
			std::cout << m_name << " Missed a 50 and scored : " << randTwenty << '\n';
			return randTwenty;				// Return a random num between 1 - 20.
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::throwForSingle(int l_throwingFor)
{
	int randNum = rand() % 100 + 1;

	if (randNum <= m_singleSuccessRate)		// singlesuccesRate <= 80%
	{
		std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " Scored : " << l_throwingFor << '\n';	// NAILED IT!
		return l_throwingFor;
	}
	else if (randNum <= 90)					// Added another 10% to 90%, MISS 'LEFT', 81% - 90% is missing left.
	{
		return searchDartBoardArr(l_throwingFor, randNum);

	}
	else if (randNum <= 100)				// Added another 10% to 100%, MISS 'RIGHT', 91% - 100% is missing right.
	{
		return searchDartBoardArr(l_throwingFor, randNum);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::throwForDouble(int l_throwingFor)
{
	int randNum = rand() % 100 + 1;

	if (randNum <= m_doubleSuccessRate)
	{
		return (2 * l_throwingFor);
	}
	else if (randNum <= 90)
	{
		return (2 * searchDartBoardArr(l_throwingFor, randNum));
	}
	else if (randNum <= 100)
	{
		return (2 * searchDartBoardArr(l_throwingFor, randNum));
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::throwForTreble(int l_throwingFor)
{
	int randNum = rand() % 100 + 1;

	if (randNum <= m_trebleSuccessRate)
	{
		return (3 * l_throwingFor);
	}
	else if (randNum <= 90)
	{
		return (3 * searchDartBoardArr(l_throwingFor, randNum));
	}
	else if (randNum <= 100)
	{
		return (3 * searchDartBoardArr(l_throwingFor, randNum));
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::searchDartBoardArr(int l_number, int randNum)
{
	// Loop through the dartBoard array looking for the number we were aiming at.
	for (int i = 0; i < 20; ++i)
	{
		// If we find the number that was passed, then check its element position.
		if (m_dartBoard.m_singlesArr[i] == l_number)
		{
			if (i == 0 && randNum <= 90)				// If its the first index position and were missing 'LEFT'
			{
				//std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " aiming for " << l_number << " missed and so hit " << m_dartBoard.m_singlesArr[19] << '\n';

				return m_dartBoard.m_singlesArr[19];	// Return the value stored at the last index position.
			}
			else if (i == 19 && randNum <= 100)			// If its the last element in the array and were missing 'RIGHT'
			{
				//std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " aiming for " << l_number << " missed and so hit " << m_dartBoard.m_singlesArr[0] << '\n';

				return m_dartBoard.m_singlesArr[0];		// Wrap around to the 'RIGHT' and return the value stroed at the first index position.
			}
			else
			{
				if (randNum <= 90)						// Check what the randnum was. If were missing 'LEFT', Its impossible to get this far with index 0 and be missing 'LEFT' which would of course be index out of bounds.
				{
					int value = m_dartBoard.m_singlesArr[i - 1];

					//std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " aiming for " << l_number << " missed and so hit " << value << '\n';

					// Return the value stored at the index position, moving 1 to the left.
					return value;
				}
				else									// Otherwise were missing 'RIGHT'. Likewise, Its impossible to get this far with index 19 and be missing 'RIGHT'.
				{
					int value = m_dartBoard.m_singlesArr[i + 1];

					//std::cout << m_name << " Dart number : " << getDartsThrownInRnd() << " aiming for " << l_number << " missed and so hit " << value << '\n';

					// Return the value stored at the index position, moving 1 to the right.
					return value;
				}
			}
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::incrementGamesWon()
{
	++m_gamesWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::increment_N_DartFinishes()
{
	switch (m_totalDartsThrownInGame)
	{
	case 7:
		++m_nDartFinishes[0];
		break;
	case 8:
		++m_nDartFinishes[1];
		break;
	case 9:
		++m_nDartFinishes[2];
		break;
	case 10:
		++m_nDartFinishes[3];
		break;
	case 11:
		++m_nDartFinishes[4];
		break;
	case 12:
		++m_nDartFinishes[5];
		break;
	case 13:
		++m_nDartFinishes[6];
		break;
	case 14:
		++m_nDartFinishes[7];
		break;
	case 15:
		++m_nDartFinishes[8];
		break;
	case 16:
		++m_nDartFinishes[9];
		break;
	case 17:
		++m_nDartFinishes[10];
		break;
	case 18:
		++m_nDartFinishes[11];
		break;
	case 19:
		++m_nDartFinishes[12];
		break;
	case 20:
		++m_nDartFinishes[13];
		break;
	case 21:
		++m_nDartFinishes[14];
		break;
	default:
		std::cout << "Oops, something went wrong trying to populate the nDartFinishes array!.\n";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::printWinFreqs(int l_numOfGamesPlayed)
{
	double totalGamesWinPercent = ((double)m_gamesWon / l_numOfGamesPlayed) * 100;

	double sevenDartFinPercentage = ((double)m_nDartFinishes[0] / m_gamesWon) * 100;
	double eightDartFinPercentage = ((double)m_nDartFinishes[1] / m_gamesWon) * 100;
	double nineDartFinPercentage = ((double)m_nDartFinishes[2] / m_gamesWon) * 100;
	double tenDartFinPercentage = ((double)m_nDartFinishes[3] / m_gamesWon) * 100;
	double elevenDartFinPercentage = ((double)m_nDartFinishes[4] / m_gamesWon) * 100;
	double twelveDartFinPercentage = ((double)m_nDartFinishes[5] / m_gamesWon) * 100;
	double thirteenDartFinPercentage = ((double)m_nDartFinishes[6] / m_gamesWon) * 100;
	double fourteenDartFinPercentage = ((double)m_nDartFinishes[7] / m_gamesWon) * 100;
	double fifteenDartFinPercentage = ((double)m_nDartFinishes[8] / m_gamesWon) * 100;
	double sixteenDartFinPercentage = ((double)m_nDartFinishes[9] / m_gamesWon) * 100;
	double seventeenDartFinPercentage = ((double)m_nDartFinishes[10] / m_gamesWon) * 100;
	double eighteenDartFinPercentage = ((double)m_nDartFinishes[11] / m_gamesWon) * 100;
	double nineteenDartFinPercentage = ((double)m_nDartFinishes[12] / m_gamesWon) * 100;
	double twentyDartFinPercentage = ((double)m_nDartFinishes[13] / m_gamesWon) * 100;
	double twentyoneDartFinPercentage = ((double)m_nDartFinishes[14] / m_gamesWon) * 100;

	std::cout << "\n##########  HERE ARE TOTAL THE RESULTS FOR " << m_name << "  ##########\n";

	std::cout << "\n" << m_name << " won " << m_gamesWon << " games out of a total of " << l_numOfGamesPlayed << " games, which is " << totalGamesWinPercent << "%\n";

	std::cout << "\n##########  AND HERE ARE THE FREQUENCIES OF N DART FINISHES FOR " << m_name << "  ##########\n";

	std::cout << "\n	(N) DART FINISHES			FREQUENCIES\n";
	std::cout << "\n		7				 : " << sevenDartFinPercentage << "%\n";
	std::cout << "\n		8				 : " << eightDartFinPercentage << "%\n";
	std::cout << "\n		9				 : " << nineDartFinPercentage << "%\n";
	std::cout << "\n		10				 : " << tenDartFinPercentage << "%\n";
	std::cout << "\n		11				 : " << elevenDartFinPercentage << "%\n";
	std::cout << "\n		12				 : " << twelveDartFinPercentage << "%\n";
	std::cout << "\n		13				 : " << thirteenDartFinPercentage << "%\n";
	std::cout << "\n		14				 : " << fourteenDartFinPercentage << "%\n";
	std::cout << "\n		15				 : " << fifteenDartFinPercentage << "%\n";
	std::cout << "\n		16				 : " << sixteenDartFinPercentage << "%\n";
	std::cout << "\n		17				 : " << seventeenDartFinPercentage << "%\n";
	std::cout << "\n		18				 : " << eighteenDartFinPercentage << "%\n";
	std::cout << "\n		19				 : " << nineteenDartFinPercentage << "%\n";
	std::cout << "\n		20				 : " << twentyDartFinPercentage << "%\n";
	std::cout << "\n		21				 : " << twentyoneDartFinPercentage << "%\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::searchFinishesArray()
{
	// Loop over all elements in the finishes array, checking our remaining score
	// against the total stored at each index position, if our score is found then we are able to finish
	// so return true, else return false.

	// 162 is the number of possible finishes.
	for (int i = 0; i < 162; ++i)
	{
		if (m_remainingScore == m_dartBoard.m_allFinishesArr[i].m_finishTotal)
		{
			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::throwForFinish()
{
	// Loop over all finishes and find our score remaining
	// Then pass in dart 1 num and type to the throwDart function.

	for (int i = 0; i < 162; i++)
	{
		if (m_remainingScore == m_dartBoard.m_allFinishesArr[i].m_finishTotal)
		{
			int throwingFor = m_dartBoard.m_allFinishesArr[i].m_dart_1[0];
			char typeThrowingFor = m_dartBoard.m_allFinishesArr[i].m_dart_1[1];

			return throwDart(throwingFor, typeThrowingFor);
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::resetGame()
{
	m_dartsThrownInRnd = 0;
	m_totalDartsThrownInGame = 0;
	m_remainingScore = 501;
	m_numOfBullHit = 0;
	m_turnsTaken = 0;

	m_hasWon = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GETTERS & SETTERS.
std::string Player::getName()
{
	return m_name;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getDartsThrownInRnd()
{
	return m_dartsThrownInRnd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::setDartsThrownInRnd(int l_thrown)
{
	m_dartsThrownInRnd = l_thrown;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getNumOfDartsToThrow()
{
	return m_numOfDartsToThrow;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getRemainingScore()
{
	return m_remainingScore;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::setRemainingScore(int l_remainingScore)
{
	m_remainingScore = l_remainingScore;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getNumOfBullHit()
{
	return m_numOfBullHit;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::incrementBullHit()
{
	++m_numOfBullHit;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getTurnsTaken()
{
	return m_turnsTaken;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::incrementTurnsTaken()
{
	++m_turnsTaken;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getGamesWon()
{
	return m_gamesWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::incrementLegsWon()
{
	++m_legsWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getLegsWon()
{
	return m_legsWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::setLegsWon(int l_legsWon)
{
	m_legsWon = l_legsWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::incrementMatchesWon()
{
	++m_matchesWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::incrementSetsWon()
{
	++m_setsWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getSetsWon()
{
	return m_setsWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::setSetsWon(int l_setsWon)
{
	m_setsWon = l_setsWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::getIsPlaying()
{
	return m_isPlaying;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::setIsPlaying(bool l_isPlaying)
{
	m_isPlaying = l_isPlaying;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::getHasWon()
{
	return m_hasWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::setHasWon(bool l_hasWon)
{
	m_hasWon = l_hasWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getInnerBullSuccessRate()
{
	return m_innerBullSuccessRate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getOuterBullSuccessRate()
{
	return m_outerBullSuccessRate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getSingleSuccessRate()
{
	return m_singleSuccessRate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getDoubleSuccessRate()
{
	return m_doubleSuccessRate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getTrebleSuccessRate()
{
	return m_trebleSuccessRate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////