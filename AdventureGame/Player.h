#pragma once

#include <string>
#include "Location.h"

using namespace std;

bool isValidPlayerName(string playerName);

class CPlayer
{
public:
	CPlayer(string name, CLocation* startingLocation);
	virtual ~CPlayer();
protected:
	string* _name;
	CLocation* _currentLocation;
public:
	string getName();	
	CLocation* getCurrentLocation();
	bool GoTo(string NameOfExit);
};

