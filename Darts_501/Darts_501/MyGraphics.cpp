/*
 *	A small class to handle some of the more purely graphics related stuff in the game, buffers etc.
 *
 *	Created on: 28 Oct 2019
 *
 *	Original @author:	© Abertay University. 2019.
 *
 *	Update by @author:	© D. Green. 2020.
 *
 */

 // INCLUDES
#include "MyGraphics.h"
#include <stdio.h> 
#include <ctype.h>  
#include <conio.h> 
#include <windows.h> 
#include <string> 
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
CONSOLE_SCREEN_BUFFER_INFO con_info;												// Holds screen info.

// CONSTRUCTORS / DESTRUCTOR
MyGraphics::MyGraphics()
{
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);		// Open i/o channel to console screen.
	//resizeConsoleWindow();
	initGraphics();
}

MyGraphics::~MyGraphics()
{
	std::cout << "MyGraphics object destroyed!\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS

// This function initializes the console graphics engine 
void MyGraphics::initGraphics()
{
	COORD console_buffer_size = { 120, 30 };													/*
																							 * Size of console buffer. This will NOT set the buffer to the specified size if EITHER of the dimensions are smaller than
																							 * The corresponding dimensions of the buffers window. This can be difficult to judge as the window is set in px and
																							 * The buffer size is set in character size and rows.
																							 * 195 is the exact x dimensions of a 1600 window and can be seen if one changes this to 196, they will be able to scroll
																							 * in the x-axis as the buffer is now one character bigger than the window in the x -axis.
																							 *
																							 * 47 is the exact y dimensions of an 800 window and can be seen if one changes this to 47, they will not longer be able to
																							 * scroll in the y-axis, this however is also true for once the simulation is finished and so therefore in
																							 * order to view results cannot this value must be set to a value greater than 47 by the amount that will be required
																							 * once the results have been printed, this requires a bit of trial and error.
																							 */

	bool test = SetConsoleScreenBufferSize(hconsole, console_buffer_size);					/*
																							 * Make sure we are in 196 x 116. This ensures the buffer is large enough that the results will be seen and that it is also
																							 * greater than the window size and will not cause the setting of it to fail.
																							 */

	/*
	 * A quick test to ensure that the buffer is set correctly.
	 */
	/*if (test)
	{
		std::cout << "Buffer set\n";
	}
	else
	{
		std::cerr << "Buffer not set\n";
	}*/

	GetConsoleScreenBufferInfo(hconsole, &con_info);										// Get details for console screen.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes
void MyGraphics::publicShowConsoleCursor(bool showFlag)
{
	showConsoleCursor(showFlag);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *Small function to be able to show and hide the output windows blinking cursor.

 This IS NOT my code and has been provided by Captain Oblivious at:
 https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
 */
void MyGraphics::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;													// Set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes.
void MyGraphics::publicSetColor(int foreColor, int backColor)
{
	setColor(foreColor, backColor);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function sets the color of the console output.
void MyGraphics::setColor(int fcolor, int bcolor)
{
	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) | fcolor));				// Set color.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes.
void MyGraphics::publicDrawString(int& x, int y, std::string str)
{
	drawString(x, y, str);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function draws a given string at the passed in coords.
void MyGraphics::drawString(int& x, int y, std::string str)
{
	COORD cursor_pos;																// Used to pass coords.

	// Set printing position.
	cursor_pos.X = x;
	cursor_pos.Y = y;

	SetConsoleCursorPosition(hconsole, cursor_pos);

	std::cout << str;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes.
bool MyGraphics::publicClearTitleScreen()
{
	return clearTitleScreen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function clears the title screen.
bool MyGraphics::clearTitleScreen()
{
	int count = 0;

	//setColor(10, 0);																// Set color to green on black.

	while (count < 5)
	{
		for (int index = 37; index < 82; index++)									// Clear the screen with a scrolling effect.
		{
			switch (count)
			{
			case 0:
				MyGraphics::drawString(index, 0, " ");
				Sleep(20);
				break;
			case 1:
				MyGraphics::drawString(index, 1, " ");
				Sleep(20);
				break;
			case 2:
				MyGraphics::drawString(index, 2, " ");
				Sleep(20);
				break;
			case 3:
				MyGraphics::drawString(index, 3, " ");
				Sleep(20);
				break;
			case 4:
				MyGraphics::drawString(index, 4, " ");
				Sleep(20);
				break;
			default:
				std::cout << "Oops, couldn't clear title screen correctly!\n";
			}
		}

		++count;

		std::cout << '\n';
	}

	return true;
}
// End clearTitleScreen.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes.
void MyGraphics::publicClearGameOverScreen()
{
	clearGameOverScreen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyGraphics::clearGameOverScreen()
{
	int count = 0;

	//setColor(10, 0);																// Set color to green on black.

	while (count < 3)
	{
		for (int index = 5; index < 81; index++)									// Clear the screen with a scrolling effect.
		{
			switch (count)
			{
			case 0:
				MyGraphics::drawString(index, 0, " ");
				Sleep(20);
				break;
			case 1:
				MyGraphics::drawString(index, 1, " ");
				Sleep(20);
				break;
			case 2:
				MyGraphics::drawString(index, 2, " ");
				Sleep(20);
				break;
			default:
				std::cout << "Oops, something went wrong!\n";
			}
		}

		++count;

		std::cout << '\n';
	}
}
// End clearGameOverScreen.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes.
void MyGraphics::publicClearScreenFull()
{
	clearScreenFull();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function clears the screen.
void MyGraphics::clearScreenFull()
{
	//setColor(10, 0);																// Set green to white on black.

	int xPos = 0;

	for (int index = 0; index < 30; index++)										// Clear all of the screen as a block of blank text.
	{
		MyGraphics::drawString(xPos, index, "                                                                                             ");
	}

	std::cout << '\n';
}
// End clearScreen.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyGraphics::clearCheckOutTable()
{
	int xPos = 164;

	for (int index = 0; index < 30; index++)										// Clear all of the screen as a block of blank text.
	{
		MyGraphics::drawString(xPos, index, "                               ");
	}

	std::cout << '\n';
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is the public interface that simply calls the subsequent and private function, thus not allowing direct access from outside classes.
void MyGraphics::publicClearScreenHalf()
{
	clearScreenHalf();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyGraphics::clearScreenHalf()
{
	int xPos = 164;

	for (int index = 0; index < 30; index++)										// Clear the upper half of the screen as a block of blank text.
	{
		MyGraphics::drawString(xPos, index, "                               ");
	}

	std::cout << '\n';
}