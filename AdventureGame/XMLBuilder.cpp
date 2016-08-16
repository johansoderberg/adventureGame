#include "stdafx.h"
#include "XMLBuilder.h"
#include <sstream>
#include <fstream>
#include <iostream>

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

// Todo: need to check that element name is valid.
void CXMLBuilder::addElement(string elementName) {	
	CXMLElement* lElement = new CXMLElement(elementName);		
	_currentElement->top()->addElement(lElement);
	_currentElement->push(lElement);
}

void CXMLBuilder::finishElement() {
	_currentElement->pop();
}

// Todo: need to check that attribute names are valid.
void CXMLBuilder::addAttribute(string &name, string &value) {
	if (_currentElement->empty()) {
		return;
	}

	_currentElement->top()->addAttribute(name, value);
}

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

	return true;
}

bool CXMLBuilder::isValidElementName(const string elementName) const {

	return true;
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
