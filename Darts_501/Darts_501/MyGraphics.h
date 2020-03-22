#pragma once

// INCLUDES
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>  
#include <conio.h> 
#include <windows.h> 
#include <time.h> 
#include <string> 
#include <iostream>

class MyGraphics
{
public:
	// DATA MEMBERS
	HANDLE hconsole;

	// CONSTRUCTOR / DESTRUCTOR
	MyGraphics();
	~MyGraphics();

	// MEMBER FUNCTIONS
	void publicShowConsoleCursor(bool showFlag);
	void publicSetColor(int foreColor, int backColor);
	void publicDrawString(int& x, int y, std::string str);
	bool publicClearTitleScreen();
	void publicClearGameOverScreen();
	void publicClearScreenFull();
	void publicClearScreenHalf();
	void clearCheckOutTable();

private:
	// MEMBER FUNCTIONS
	void initGraphics();
	void showConsoleCursor(bool showFlag);
	void setColor(int foreColor, int backColor);
	void drawString(int& x, int y, std::string str);
	bool clearTitleScreen();
	void clearGameOverScreen();
	void clearScreenFull();
	void clearScreenHalf();
	//void resizeConsoleWindow();
};

