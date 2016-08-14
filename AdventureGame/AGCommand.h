#pragma once
#include <iostream>
#include <string>
#include "game.h"


using namespace std;

class CGame;

class CAGCommand
{	
protected:
	CGame* _game;
public:	
	CAGCommand(CGame *game);
	virtual ~CAGCommand();	
	virtual string getCommandName();
	virtual string call();
	virtual string getCommandHelp();
};

class CQuitCommand :
	public CAGCommand{
public:
	CQuitCommand(CGame* game);	
	virtual string getCommandName();
	virtual string call();
	virtual string getCommandHelp();	
};

class CAGExamineCommand :
	public CAGCommand {
public:
	CAGExamineCommand(CGame *game);
	virtual string getCommandName();
	virtual string call();
	virtual string getCommandHelp();
};


class CAGGoCommand :
	public CAGCommand {
public:
	CAGGoCommand(CGame *game);
	virtual string getCommandName();
	virtual string call();
	virtual string getCommandHelp();
};