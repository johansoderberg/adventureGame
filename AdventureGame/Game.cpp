#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "HelpCommand.h"
#include <algorithm>


CGame::CGame(string playerName, CLocation* startingLocation)
{	
	rootLocation = startingLocation;

	_commands = list<CAGCommand*>();
	try {
		player = new CPlayer(playerName, rootLocation);
	}
	catch (exception e) {
		throw e;
	}
		
	_commands.push_back(new CHelpCommand(this));
	_commands.push_back(new CQuitCommand(this));
	_commands.push_back(new CAGExamineCommand(this));
	_commands.push_back(new CAGGoCommand(this));
}


CGame::~CGame()
{

}

void CGame::play() {
	cout << "Welcome " << player->getName() << ".\n";
		
	while (!gameOver) {
		playRound();
	}
}


void CGame::playRound() {
	cout << "\n";
	describeLocation();

	string commandStr;
	cout << "-> ";
	cin >> commandStr;

	CAGCommand* cmd = getCommand(commandStr);

	if (cmd == NULL) {
		cout << "Sorry, didn't get that. Type ? for help\n";
		return;
	}

	cout << cmd->call();
	cout << "\n";
}

bool CGame::stringCompareLC(string* str1, string* str2) {
	string tmp1 = string(*str1);
	string tmp2 = string(*str2);
	transform(str1->begin(), str1->end(), tmp1.begin(), tolower);
	transform(str2->begin(), str2->end(), tmp2.begin(), tolower);
	return ((tmp1.compare(tmp2)) == 0);
}

CAGCommand* CGame::getCommand(string commandStr) {
	list<CAGCommand*>::iterator itr = _commands.begin();	
	
	while (itr != _commands.end()) {		
		CAGCommand* cmd = *itr;		
	
		string tmp = cmd->getCommandName();
		if (stringCompareLC(&tmp, &commandStr)) {
			return cmd;
		}
		itr++;
	}
	return NULL;
}

void CGame::describeLocation() {
	CLocation* loc = player->getCurrentLocation();

	cout << "You are in " << (loc->getName()) << ".\n";
	cout << loc->DescribeExits();

}

