#pragma once

#include <string>
#include <stack>
#include <list>

using namespace std;

class CXMLElement {
public:
	CXMLElement(string elementName);
	virtual ~CXMLElement();
	void addAttribute(string &name, string &value);
	void addElement(CXMLElement* element);
	void addXMLData(stringstream& ss, const int level, const bool prettyPrint) const;
protected:
	string* _elementName;
	list<string*>* _attributes;
	list<CXMLElement*>* _subElements;
	void addXMLStartTag(stringstream& ss, const int level, const bool prettyPrint) const;
	void addXMLEndTag(stringstream& ss, const int level, const bool prettyPrint) const;	
};

class CXMLBuilder
{
public:
	CXMLBuilder(string rootName);
	virtual ~CXMLBuilder();
	void addElement(string elementName);
	void finishElement();
	void addAttribute(string &name, string &value);	
	void saveToFile(string fileName, const bool prettyPrint) const;
protected:
	stack<CXMLElement*>* _currentElement;
	CXMLElement* _root;	
	bool isValidAttributeName(const string attributeName) const;
	bool isValidElementName(const string elementName) const;
};

