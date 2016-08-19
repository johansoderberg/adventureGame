#pragma once
#include "AGCommand.h"
class CTestCommand :
	public CAGCommand
{
public:
	CTestCommand(CGame* game);
	virtual ~CTestCommand();
	/* returns the command name (!) */
	virtual string getCommandName();
	/* Makes a function call the command (!) */
	virtual string call();
	/* Returns a description of the command does */
	virtual string getCommandHelp();
	
};

