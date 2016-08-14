#include "stdafx.h"
#include <sstream>
#include <iostream>
#include "HelpCommand.h"



CHelpCommand::CHelpCommand(CGame* game)
	: CAGCommand(game)
{
	
}


CHelpCommand::~CHelpCommand()
{
}

string CHelpCommand::getCommandName()
{
	return "?";
}

string CHelpCommand::getCommandHelp() {
	return "This command lists all available commands.";
}

string CHelpCommand::call() {
	stringstream ss = stringstream();

	for (list<CAGCommand*>::iterator i = (*_game)._commands.begin(); i != (*_game)._commands.end(); i++){
		CAGCommand* cmd = *i;		
		ss << cmd->getCommandName() << ":  \t" << cmd->getCommandHelp() << "\n";
	}
	return ss.str();
}

