#include "stdafx.h"
#include "AGCommand.h"
#include "PAPStringUtil.h"

using namespace std;

CAGCommand::CAGCommand(CGame *game)
{
	_game = game;
}


CAGCommand::~CAGCommand()
{
}

// return the name of the command.
string CAGCommand::getCommandName()
{
	return string();
}

// returns a description on what the command does.
string CAGCommand::getCommandHelp()
{	return string();
}

// call the command(!)
string CAGCommand::call()
{
	return string();
}

CQuitCommand::CQuitCommand(CGame * game)
	: CAGCommand(game)
{

}

string CQuitCommand::getCommandName()
{
	return "Quit";
}

string CQuitCommand::call()
{
	_game->gameOver = true;
	return string();
}

string CQuitCommand::getCommandHelp()
{
	return "Exists the game.";
}

CAGExamineCommand::CAGExamineCommand(CGame *game) : CAGCommand(game) {
	
}

string CAGExamineCommand::getCommandName() {
	return "Examine";
}

string CAGExamineCommand::call() {
	string thing = string();
	cin >> thing;

	CLocation * currLoc = _game->player->getCurrentLocation();

	if (strCompareLC(thing, (currLoc->getName()))){
		return currLoc->getLongDescription();
	}

	// look for a exit with this name.

	// look for an item with this name.

	// look for a character with this name.

	

	return "Examine is not finished\n";
}

string CAGExamineCommand::getCommandHelp(){
	return "Examine describes an object, location, character or other thing in detail.";
};

CAGGoCommand::CAGGoCommand(CGame * game)
	: CAGCommand(game)
{
}

string CAGGoCommand::getCommandName()
{
	return "Go";
}

string CAGGoCommand::call()
{
	string exitName;
	cin >> exitName;
	
	if (_game->player->GoTo(exitName)) {		
		return "You walk there.\n";
	}
	else
		return "There is no exit with that name.\n";
}

string CAGGoCommand::getCommandHelp()
{
	return "Use this command to navigate. Just write Go followed by the name of an exit";
}
