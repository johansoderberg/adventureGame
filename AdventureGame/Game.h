#pragma once

#include <string>
#include <list>
#include "Player.h"
#include "Location.h"
#include "AGCommand.h"


using namespace std;

class CAGCommand;

class CGame
{
public:
	CGame(string playerName, CLocation* startingLocation);
	~CGame();
	void play();
	list<CAGCommand*> _commands;
	bool gameOver = false;
	CLocation* rootLocation;
	static bool stringCompareLC(string* str1, string* str2);
	void exportWorldAsXML(string fileName);
	CPlayer* player;
protected:	
	void playRound();
	CAGCommand* getCommand(string commandStr);
	void describeLocation();
};

