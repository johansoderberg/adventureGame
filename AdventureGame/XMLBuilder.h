#pragma once

#include <string>
#include <stack>
#include <list>
#include "XMLElements.h"

using namespace std;

class CXMLElement;

class CXMLException
{
public:
	CXMLException(string message);
	virtual ~CXMLException();
	string getMessage();
protected:
	string _message;	
};

class CXMLBuilder
{
public:
	CXMLBuilder(string rootName);
	virtual ~CXMLBuilder();
	void addElement(string elementName, void* uniqueObject);
	void finishElement();
	void addAttribute(string name, string& value);
	void addText(string& text);
	void exportXMLToFile(string& fileName, const bool& prettyPrint) const;
	bool isValidAttributeName(const string attributeName) const;
	bool isValidElementName(const string elementName) const;
	bool isObjectAdded(void* uniqueObject);
protected:
	stack<CXMLElement*>* _currentElement;
	CXMLElement* _root;
	list<void*>* _uniqueObjects;
};

