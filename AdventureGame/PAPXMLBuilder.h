#pragma once

#include <string>
#include <stack>
#include <list>
#include "PAPXMLElements.h"

using namespace std;

class CXMLElement;

class PAPException
{
public:
	PAPException(string message);
	virtual ~PAPException();
	string getMessage();
protected:
	string _message;	
};

class CXMLBuilder
{
public:
	CXMLBuilder(string rootName);
	virtual ~CXMLBuilder();
	/* Adds an new element. It is not finished until finishElement(..) has been called. These calls should be balanced*/
	void startElement(string elementName, void* uniqueObject);
	/*Used to finalise a call to startElement(...) */
	void finishElement();
	/* Adds an attribute to the current element.*/
	void addAttribute(string name, string& value);
	/* Adds a text to the current element. */
	void addText(string text);
	/* Adds a CData section to the current element. Throws an PAPException if the data contains the secuence ]]>.*/
	void addCData(string data);
	/* Adds a comment to the current element. */
	void addComment(string comment);
	/* Saves the current data to a file. Can only be used once per build of data.*/
	void exportXMLToFile(string fileName, const bool& prettyPrint) const;
	/* Utility function to test if an attribute name is valid XML. */
	bool isValidAttributeName(const string attributeName) const;
	/* Utility function to test if an element name is valid XML. */
	bool isValidElementName(const string elementName) const;
	/* Utility function to test an object is already added to the build. */
	bool isObjectAdded(void* uniqueObject);
protected:
	stack<CXMLElement*>* _currentElement;
	CXMLElement* _root;
	list<void*>* _uniqueObjects;	
	const string attributeNamePattern = "[a-zA-Z_:]([a-zA-Z0-9_:.])*";  // This pattern is a bit too restrictive.
};

