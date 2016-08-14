#include "stdafx.h"
#include "Player.h"



CPlayer::CPlayer(string name, CLocation* startingLocation)
{
	if (!isValidPlayerName(name)) {
		throw new exception("Illegal name!");
	}

	_currentLocation = startingLocation;

	_name = new string(name);
}


CPlayer::~CPlayer()
{
	delete _name;
}


string CPlayer::getName()
{
	return string(*_name);
}


CLocation* CPlayer::getCurrentLocation() {
	return _currentLocation;
}

// function for approving player names. Could be used to disapprove obcenities.
bool isValidPlayerName(string playerName)
{		
	if (playerName.length() == 0) 
		return false;

	if (playerName.compare("Idiot") == 0) {
		return false;
	}

	return true;
}


bool  CPlayer::GoTo(string NameOfExit) {
	CExit* localExit = _currentLocation->getExit(NameOfExit);
	if (localExit == NULL) {
		return false;
	}
	else
	{
		_currentLocation = localExit->getLocation();
		return true;
	}
}