#pragma once
#include "AGCommand.h"
class CTestCommand :
	public CAGCommand
{
public:
	CTestCommand(CGame* game);
	virtual ~CTestCommand();
	virtual string getCommandName();
	virtual string call();
	virtual string getCommandHelp();
	
};

