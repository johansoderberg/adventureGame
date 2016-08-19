#include "stdafx.h"
#include <sstream>
#include <iostream>
#include "PAPStringUtil.h"
#include "Location.h"

CLocation::CLocation(string name, string shortDesc, string longDesc)
{	
	_name = new string(name);
	_shortDesc= new string(shortDesc);
	_longDesc = new string(longDesc);
	exits = new map < string, CExit*>();
}

CLocation::~CLocation()
{
	delete _name;
	delete _shortDesc;
	delete _longDesc;
	delete exits;
}

string CLocation::getshortDescription()
{
	return string(*_shortDesc);
}

string CLocation::getLongDescription()
{
	return string(*_longDesc);
}

void CLocation::connect(string exitName, CLocation * location)
{
	exits->insert(std::pair<string, CExit*> (strToLower(&exitName), new CExit(location, exitName)));
}

void CLocation::connectDual(string exitName, CLocation * location, string remoteExitName)
{
	connect(exitName, location);
	location->connect(remoteExitName, this);
}

string CLocation::getName()
{
	return string(*_name);
}

string CLocation::DescribeExits() {
	if (exits->size() == 0) {
		return "There is no way out of this location.";
	}

	if (exits->size() == 1) {
		pair<string, CExit*> p;
		p = *exits->begin();

		stringstream strb = stringstream();
		strb << "There is a single way out of this location, " << p.first << ".\n";		
		return strb.str();
	}

	// Go through the whole list and list exits.
	stringstream strb = stringstream("There are multiple exits from this location.\n");

	for (map<string, CExit*>::iterator i = exits->begin(); i != exits->end(); i++) {
		strb << "\t " << i->first << "\n";
	}

	return strb.str();
}

CExit * CLocation::getExit(string ExitName){
	try {
		string tmp = strToLower(&ExitName);
		return exits->at(tmp);
	}
	catch (out_of_range) {
		return NULL;
	}
}



void CLocation::exportToXML(CXMLBuilder& xb) {
	// Verify that the object hasn't been added before.
	if (xb.isObjectAdded(this)) {
		return;
	}

	xb.startElement("location", this);
	xb.addAttribute("name", *_name);

	if (getshortDescription().size() > 0) {
		xb.startElement("shortDescription", NULL);
		xb.addText(getshortDescription());
		xb.finishElement(); // Short desc
	}

	if (getLongDescription().size() > 0) {
		xb.startElement("longDescription", NULL);
		xb.addText(getLongDescription());
		xb.finishElement(); // long desc.
	}

	/*
	xb.addComment("Adding a comment too.");
	xb.addText("Adding a little text with quots \". At least two of them \" and some others && \' < ><> < >	");
	xb.addComment("This comment contains \" characters = that are valid in comments such as < and >. Not to mention: \' ");
	xb.addCData("this is a CData section. It can contain anything such as \" \' & <!-- <> ");
	*/

	// Export all exits.
	for (map<string, CExit*>::iterator i = exits->begin(); i != exits->end(); i++) {
		CExit* exit = i->second;
		xb.startElement("exit", exit);
		xb.addAttribute("name", exit->getName());
		xb.addAttribute("leadsTo", exit->getLocation()->getName());
		xb.finishElement();
	}

	xb.finishElement(); // location

	// export all adjacent locations.
	for (map<string, CExit*>::iterator i = exits->begin(); i != exits->end(); i++) {
		CExit* exit = i->second;	
		CLocation* loc = exit->getLocation();
		loc->exportToXML(xb);		
	}	
}

/////////////////////////////////////////////

CExit::CExit(CLocation* location, string name)
{
	_location = location;
	_name = name;
}

CExit::~CExit()
{
}

string CExit::getName()
{
	return _name;
}

CLocation*  CExit::getLocation()
{
	return _location;
}
