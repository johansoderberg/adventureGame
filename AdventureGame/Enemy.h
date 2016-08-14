#pragma once

#include <string>
using namespace std;

class CEnemy
{
public:
	CEnemy();
	virtual ~CEnemy();
	string getShortDescription();
	string getLongDescription();
protected:
	string _shortDescription;
};

