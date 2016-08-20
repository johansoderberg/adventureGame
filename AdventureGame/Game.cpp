#include "stdafx.h"
#include <iostream>

#include "Game.h"
#include "HelpCommand.h"
#include "TestCommand.h"
#include "PAPXMLBuilder.h"
#include "PAPStringUtil.h"

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
	_commands.push_back(new CTestCommand(this));   // just for testing things.
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


CAGCommand* CGame::getCommand(string commandStr) {
	list<CAGCommand*>::iterator itr = _commands.begin();	
	
	while (itr != _commands.end()) {		
		CAGCommand* cmd = *itr;		
	
		string tmp = cmd->getCommandName();
		if (strCompareLC(tmp, commandStr)) {
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

void CGame::exportWorldAsXML(string fileName) {
	try {
		CXMLBuilder xb = CXMLBuilder(string("gameWorld"));
		rootLocation->exportToXML(xb);
		xb.exportXMLToFile(string("gameWorld.xml"), true);
	}
	catch (PAPException E) {
		cout << E.getMessage();
	}
}
