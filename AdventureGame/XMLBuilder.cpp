#include "stdafx.h"
#include "XMLBuilder.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>


#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
static inline std::string ltrimmed(std::string s) {
	ltrim(s);
	return s;
}

// trim from end (copying)
static inline std::string rtrimmed(std::string s) {
	rtrim(s);
	return s;
}

// trim from both ends (copying)
static inline std::string trimmed(std::string s) {
	trim(s);
	return s;
}

CXMLBuilder::CXMLBuilder(string rootName)
{	
	_currentElement = new stack<CXMLElement*>();
	_root = new CXMLElement(rootName);
	_currentElement->push(_root);	
}


CXMLBuilder::~CXMLBuilder()
{	
	delete _currentElement;
}

void CXMLBuilder::addElement(string elementName) {	
	trim(elementName);
	if (!isValidElementName(elementName)) {
		stringstream ss = stringstream();
		ss << "Invalid attributename: " << elementName << endl;
		throw(MyException(ss.str()));
	}

	CXMLElement* lElement = new CXMLElement(elementName);		
	_currentElement->top()->addElement(lElement);
	_currentElement->push(lElement);
}

void CXMLBuilder::finishElement() {
	_currentElement->pop();
}


void CXMLBuilder::addAttribute(string name, string value) {
	trim(name);
	if (!isValidAttributeName(name)) {
		stringstream ss = stringstream();
		ss << "Invalid attributename: " << name << endl;
		throw(MyException(ss.str()));
	}

	trim(value);
	_currentElement->top()->addAttribute(name, value);
}

// Todo: add verification if the file already exists.

void CXMLBuilder::saveToFile(string fileName, const bool prettyPrint) const {
	ofstream* file = new ofstream();
	file->open(fileName);
	*file << "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>" << endl;

	stringstream* ss = new stringstream();

	_root->addXMLData(*ss, 0, prettyPrint);
	*file << ss->str();
	file->close();
	delete file;
	delete ss;
}

bool CXMLBuilder::isValidAttributeName(const string attributeName) const {
	regex pattern("[a-zA-Z_:]([a-zA-Z0-9_:.])*");	
	return regex_match(attributeName, pattern);
}

bool CXMLBuilder::isValidElementName(const string elementName) const {
	regex pattern("[a-zA-Z_:]([a-zA-Z0-9_:.])*");
	return regex_match(elementName, pattern);
}

////////////////////////////// Element ///////////////////////////////////////////////////////////////////////////////////////////////

CXMLElement::CXMLElement(string ElementName) {
	_elementName = new string(ElementName);
	_attributes = new list<string*>();
	_subElements = new list<CXMLElement*>() ;
}

CXMLElement::~CXMLElement() {
	// Delete all attributes 	
	while (_attributes->size() > 0) {
		delete _attributes->front();		
		_attributes->pop_front();		
	}
	delete _attributes;

	// Delete all sub elements
	while (_subElements->size() > 0) {
		delete _subElements->front();
		_subElements->pop_front();
	}
	delete _subElements;
	delete _elementName;
}

void CXMLElement::addAttribute(string &name, string &value) {
	stringstream ss = stringstream();
	ss << name << "=\"" << value << "\"";
	_attributes->push_back(new string(ss.str()));
}

void CXMLElement::addElement(CXMLElement* element){
	_subElements->push_back(element);
}

void CXMLElement::addXMLData(stringstream& ss, const int level, const bool prettyPrint) const{
	addXMLStartTag(ss, level + 1, prettyPrint);

	// Add elements
	for (list<CXMLElement*>::iterator i = _subElements->begin(); i != _subElements->end(); i++) {		
		CXMLElement* lElement = *i;
		lElement->addXMLData(ss, level + 1, prettyPrint);
	}

	addXMLEndTag(ss, level + 1, prettyPrint);
}

void CXMLElement::addXMLStartTag(stringstream& ss, const int level, const bool prettyPrint) const {
	if (prettyPrint) {
		for (int i = 1; i != level; i++) {
			ss << "\t";
		}
	}
	ss << "<" << string(*_elementName);

	if (_attributes != NULL) {
		if (!_attributes->empty()) {
			for (list<string*>::iterator i = _attributes->begin(); i != _attributes->end(); i++) {				
				ss << " ";
				ss << **i;
			}			
		}		
	}		

	ss << ">";
	if (prettyPrint) {
		ss << endl;
	}
}

void CXMLElement::addXMLEndTag(stringstream& ss, const int level, const bool prettyPrint) const {
	if (prettyPrint) {
		for (int i = 1; i != level; i++) {
			ss << "\t";
		}
	}

	ss << "<\\" << string(*_elementName) << ">";

	if (prettyPrint) {
		ss << endl;
	}
}


///////////////////////

MyException::MyException(string message) {
	_message = message;
}

MyException::~MyException() {
	
}

string MyException::getMessage() {
	return string(_message);
}