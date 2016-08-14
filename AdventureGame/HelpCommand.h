#pragma once
#include <list>
#include "AGCommand.h"


using namespace std;

class CHelpCommand :
	public CAGCommand
{	
public:
	CHelpCommand(CGame* game);
	virtual ~CHelpCommand();
	virtual string getCommandName() override;	
	virtual string getCommandHelp() override;
	virtual string call() override;	
};

