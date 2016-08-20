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
	list<CAGCommand*> _commands;
	CLocation* rootLocation;
	/* Starts the game loop.*/
	bool gameOver = false;
	void play();	
	/* Exports the world to XML.*/
	void exportWorldAsXML(string fileName);	
	CPlayer* player;
protected:
	void playRound();
	
	CAGCommand* getCommand(string commandStr);
	void describeLocation();	
};


