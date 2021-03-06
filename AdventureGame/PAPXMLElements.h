#pragma once


#include <string>
#include <stack>
#include <list>
#include <sstream>

using namespace std;

class CXMLComposite {
public:
	virtual void addXMLData(stringstream& ss, const int level, const bool prettyPrint) const = 0;
	virtual ~CXMLComposite();
};

class CXMLElement : public CXMLComposite {
public:
	CXMLElement(string elementName);
	virtual ~CXMLElement() override;
	void addAttribute(string &name, string &value);
	void addElement(CXMLComposite* element);
	virtual void addXMLData(stringstream& ss, const int level, const bool prettyPrint) const override;
protected:
	string* _elementName;
	list<string*>* _attributes;
	list<CXMLComposite*>* _subElements;
	void addXMLStartTag(stringstream& ss, const int level, const bool prettyPrint) const;
	void addXMLEndTag(stringstream& ss, const int level, const bool prettyPrint) const;
};

class CXMLTextElement : public CXMLComposite {
public:
	CXMLTextElement(string& text);
	virtual ~CXMLTextElement() override;
	void addXMLData(stringstream& ss, const int level, const bool prettyPrint) const override;	
protected:
	string* _text;
	string encodeText(const string text);
};

class CXMLComment : public CXMLComposite {
public:
	CXMLComment(string& comment);
	virtual ~CXMLComment() override;
	void addXMLData(stringstream& ss, const int level, const bool prettyPrint) const override;
protected:
	string* _comment;
	const string commentStart = "<!-- ";
	const string commentEnd = "-->";
};

class CXMLCData : public CXMLComposite {
public:
	CXMLCData(string& CData);
	virtual ~CXMLCData() override;
	void addXMLData(stringstream& ss, const int level, const bool prettyPrint) const override;
protected:
	string* _CData;
	const string CDataEnd = "]]>";
	const string CDataStart = "<![CDATA[";
};
