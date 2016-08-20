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
#include "PAPStringUtil.h"
#include "irrXML.h"

using namespace std;
using namespace irr;
using namespace io;

CLocation* createWorld(string fileName) {
	IrrXMLReader* xml = createIrrXMLReader(fileName.c_str());

	string lName;
	CLocation* start = NULL;

	while (xml->read()) {
		switch (xml->getNodeType()) {
		case EXN_ELEMENT:
			lName = xml->getNodeName();
			if (strCompareLC(lName, string("location"))) {
				// create a location. Must get all the attributes first.
				string lShortDescription;
				string lLongDescription;

				for (int i = 0; i < xml->getAttributeCount(); i++) {
					if (strCompareLC(xml->getAttributeName(i), CLocation::STR_SHORT_DESCRIPTION)) {
						lShortDescription = xml->getAttributeValue(i);
					}
					else
						if (strCompareLC(xml->getAttributeName(i), CLocation::STR_LONG_DESCRIPTION)) {
							lLongDescription = xml->getAttributeValue(i);
						}
						else
							if (strCompareLC(xml->getAttributeName(i), CLocation::STR_NAME)) {
								lName = xml->getAttributeValue(i);
							}

				}

				CLocation* loc = new CLocation(lName, lShortDescription, lLongDescription);
				if (start == NULL) {
					start = loc;
				}
			}
			break;
		case EXN_ELEMENT_END:

			break;
		case EXN_TEXT:

			break;
		case EXN_COMMENT:

			break;
		case EXN_CDATA:

			break;
		}

	}

	delete xml;
	return NULL;

	/*
	CLocation* loc = new CLocation("Hallway", "The hallway outside your appartment.", "The hallways is semi dark and cold.");
	CLocation* loc2 = new CLocation("Staircase", "The staircase in the building.", "The stair case is old and dark.");
	start->connectDual("Door", loc, "AppartmentDoor");
	loc->connectDual("Staircase", loc2, "Up");

	*/
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

		startLocation =	createWorld("gameWorld.xml");

		if (startLocation == NULL) {
			cout << "No startin gpoint provided. Exiting.\n";
			return 0;
		}

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

