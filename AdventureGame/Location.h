#pragma once

#include <string>
#include <map>
#include "PAPXMLBuilder.h"


using namespace std;

class CExit;

class CLocation
{
public:
	CLocation(string name, string shortDesc, string longDesc);
	virtual ~CLocation();
	
	string getName();
	string getshortDescription();
	string getLongDescription();	
	void connect(string exitName, CLocation* location);
	void connectDual(string exitName, CLocation* location, string remoteExitName);
	string DescribeExits();
	CExit* getExit(string ExitName);
	void exportToXML(CXMLBuilder& xb);
	static const string STR_SHORT_DESCRIPTION ;
	static const string STR_LONG_DESCRIPTION;
	static const string STR_NAME;
protected:
	string* _name;
	string* _shortDesc;
	string* _longDesc;
	map<string, CExit*>* exits;
};

class CExit
{
public:
	CExit(CLocation* location, string name);
	~CExit();
	string getName();
	CLocation* getLocation();
protected:
	string _name;
	CLocation* _location;
};
