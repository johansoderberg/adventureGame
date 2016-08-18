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
	_uniqueObjects = new list<void*>();
}


CXMLBuilder::~CXMLBuilder()
{	
	delete _root;
	delete _currentElement;
	delete _uniqueObjects;
}

void CXMLBuilder::startElement(string elementName, void* uniqueObject) {
	trim(elementName);
	if (!isValidElementName(elementName)) {
		stringstream ss = stringstream();
		ss << "Invalid attributename: " << elementName << endl;
		throw(CXMLException(ss.str()));
	}

	CXMLElement* lElement = new CXMLElement(elementName);
	_currentElement->top()->addElement(lElement);
	_currentElement->push(lElement);

	if (uniqueObject != NULL) {
	_uniqueObjects->push_back(uniqueObject);
	}
}

bool CXMLBuilder::isObjectAdded(void* uniqueObject) {
	if (_uniqueObjects->empty()) {
		return false;
	}

	for (list<void*>::iterator i = _uniqueObjects->begin(); i != _uniqueObjects->end(); i++) {		
		if (uniqueObject == *i) {
			return true;
		}
	}

	return false;
}

void CXMLBuilder::finishElement() {
	_currentElement->pop();
}


void CXMLBuilder::addAttribute(string name, string& value) {
	trim(name);
	if (!isValidAttributeName(name)) {
		stringstream ss = stringstream();
		ss << "Invalid attributename: " << name << endl;
		throw(CXMLException(ss.str()));
	}

	trim(value);
	_currentElement->top()->addAttribute(name, value);
}

void CXMLBuilder::addText(string text){
	CXMLTextElement* textElement = new CXMLTextElement(text);
	_currentElement->top()->addElement(textElement);
}

void CXMLBuilder::addComment(string comment) {
	CXMLComment* _comment = new CXMLComment(comment);
	_currentElement->top()->addElement(_comment);
}

void CXMLBuilder::addCData(string data) {
	CXMLCData* _data = new CXMLCData(data);
	_currentElement->top()->addElement(_data);
}

// Todo: add verification if the file already exists.
void CXMLBuilder::exportXMLToFile(string fileName, const bool& prettyPrint) const {
	ofstream* file = new ofstream();
	file->open(fileName);
	*file << "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>";
	
	if (prettyPrint) {
		*file << endl;
	}

	stringstream* ss = new stringstream();

	_root->addXMLData(*ss, 0, prettyPrint);
	*file << ss->str();
	file->close();
	delete file;
	delete ss;
}


bool CXMLBuilder::isValidAttributeName(const string attributeName) const {
	regex pattern(attributeNamePattern);
	return regex_match(attributeName, pattern);
}

bool CXMLBuilder::isValidElementName(const string elementName) const {
	regex pattern(attributeNamePattern);
	return regex_match(elementName, pattern);
}

////////////////////////////// Element ///////////////////////////////////////////////////////////////////////////////////////////////

CXMLElement::CXMLElement(string ElementName) {
	_elementName = new string(ElementName);
	_attributes = new list<string*>();
	_subElements = new list<CXMLComposite*>() ;
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

void CXMLElement::addElement(CXMLComposite* element){
	_subElements->push_back(element);
}

void CXMLElement::addXMLData(stringstream& ss, const int level, const bool prettyPrint) const{
	addXMLStartTag(ss, level + 1, prettyPrint);

	// Add elements
	for (list<CXMLComposite*>::iterator i = _subElements->begin(); i != _subElements->end(); i++) {
		CXMLComposite* lElement = *i;
		lElement->addXMLData(ss, level + 1, prettyPrint);
	}

	// unless single tag, add end tag.
	if (_subElements->size() > 0) {
		addXMLEndTag(ss, level + 1, prettyPrint);
	}
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

	if (_subElements->size() == 0) {
		ss << "/>";
	}
	else{
		ss << ">";
	}
	
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

	ss << "</" << string(*_elementName) << ">";

	if (prettyPrint) {
		ss << endl;
	}
}


///////////////////////

CXMLException::CXMLException(string message) {
	_message = message;
}

CXMLException::~CXMLException() {

}

string CXMLException::getMessage() {
	return string(_message);
}

////////////////////// 

CXMLTextElement::CXMLTextElement(string& text) {
	_text = new string(encodeText(trimmed(text)));
}

CXMLTextElement::~CXMLTextElement() {
	delete _text;
}

void CXMLTextElement::addXMLData(stringstream& ss, const int level, const bool prettyPrint) const {
	if (prettyPrint) {
		for (int i = 0; i != level; i++) {
			ss << "\t";
		}
	}

	ss << *_text;

	if (prettyPrint) {
		ss << endl;
	}
}


// There are five characters that needs to be reaplced.
// "   &quot;
// '   &apos;
// <   &lt;
// >   &gt;
// &   &amp;

string CXMLTextElement::encodeText(string text) {
	// have to start with ampersand since it will be introduced into the result too. 
	stringstream ss = stringstream();
	for (string::iterator i = text.begin(); i != text.end(); i++) {
		if (*i == '&')
			ss << "&amp";
		else if (*i == '\'')
			ss << "&apos";
		else if (*i == '\"')
			ss << "&quot";
		else if (*i == '<')
			ss << "&lt";
		else if (*i == '>')
			ss << "&gt";
		else
			ss << *i;
	}

	return ss.str();
}

/////////CXMLComposite

CXMLComposite::~CXMLComposite() {

}

///////// CXMLComment

CXMLComment::CXMLComment(string& comment) {
	_comment = new string(comment);
}

CXMLComment::~CXMLComment() {
	delete _comment;
}

void CXMLComment::addXMLData(stringstream& ss, const int level, const bool prettyPrint) const {
	if (prettyPrint) {
		for (int i = 0; i != level; i++) {
			ss << "\t";
		}
	}

	ss << commentStart << *_comment << commentEnd;

	if (prettyPrint) {
		ss << endl;
	}
}

/// CData

CXMLCData::CXMLCData(string& CData) {
	if (CData.find(CDataEnd, 0) != string::npos){
		throw CXMLException("Invalid CData section: contains CData end sequence. This data needs to be escaped by caller. ");
	}
	_CData = new string(CData);
}

CXMLCData::~CXMLCData() {
	delete _CData;
}

void CXMLCData::addXMLData(stringstream& ss, const int level, const bool prettyPrint) const {
	if (prettyPrint) {
		for (int i = 0; i != level; i++) {
			ss << "\t";
		}
	}

	ss << CDataStart << *_CData << CDataEnd;

	if (prettyPrint) {
		ss << endl;
	}
}


