#pragma once
#include <string>

using namespace std;

class CItem
{
public:
	CItem();
	virtual ~CItem();
	string getName();
	string getShortDescription();
};

