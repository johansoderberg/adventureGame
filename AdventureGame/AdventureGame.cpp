// AdventureGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include "Game.h"
#include "AGCommand.h"
#include "Player.h"
#include "HelpCommand.h"

using namespace std;

void createWorld(CLocation* start) {
	CLocation* loc = new CLocation("Hallway", "The hallway outside your appartment.", "The hallways is semi dark and cold.");
	CLocation* loc2 = new CLocation("Staircase", "The staircase in the building.", "The stair case is old and dark.");
	start->connectDual("Door", loc, "AppartmentDoor");
	loc->connectDual("Staircase", loc2, "Up");
}

int main()
{
	cout << "Welcome to the Adventure Game.\n\n";

	string playerName;
	CGame* game;
	CLocation* startLocation;

	while (true) {
		cout << "What's your name? ";
		cin >> playerName;

		startLocation = new CLocation("appartment", "Your appartment is where you live.", "The appartment is kind of small and not very nice. It is almost empty.");
		
		createWorld(startLocation);

		try {
			game = new CGame(playerName, startLocation);
		}
		catch (invalid_argument) {
			cout << "bad programmer, have to quit now.\n";
			return 1;
		}
		catch (exception e){
			cout << "\n\tHmm, that name doesn't seem appropriate. Let's try again. \n";
			continue;
		}
		break;
	}		
	
	game->play();
	
	delete game;
	delete startLocation;
    return 0;
}

