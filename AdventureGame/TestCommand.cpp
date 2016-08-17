#include "stdafx.h"
#include "TestCommand.h"
#include <sstream>
#include "XMLBuilder.h"


CTestCommand::CTestCommand(CGame* game)
	: CAGCommand(game)
{

}


CTestCommand::~CTestCommand()
{
}

string CTestCommand::getCommandName()
{
	return "Test";
}

void TestAttributeName(stringstream& ss, CXMLBuilder& XB, string attributeName) {	
	ss << attributeName << " ";
	if (XB.isValidAttributeName(attributeName)) {
		ss << " Ok.\n";
	}
	else
		ss << " Not OK.\n";
}

string CTestCommand::call() {
	/*
	stringstream ss = stringstream();
	ss << "Creating XML Builder" << endl;

	CXMLBuilder XB = CXMLBuilder("testObject");
	ss << "XMLBuilder created:\n";	

	try {
	
		XB.addElement("subElement", NULL);
		XB.addAttribute(string("attributeName1"), string("attribute value1"));
		XB.addAttribute(string(" attributeName2"), string("attribute value2"));
		XB.finishElement();

		XB.addElement("subElement", NULL);
		XB.addAttribute(string("attributeName1"), string("attribute value3"));
		XB.addAttribute(string("attributeName5 "), string("attribute value4"));

		XB.addElement("subElement", NULL);
		XB.addAttribute(string("attributeName1"), string("attribute value1"));
		XB.addText(string("This is a test to add text"));
		XB.addAttribute(string("attributeName2"), string("attribute value2"));
		XB.finishElement();

		XB.finishElement();

		
		XB.addElement("test", NULL);
		XB.finishElement();
		XB.exportXMLToFile(string("test.xml"), false);
		XB.exportXMLToFile(string("test_pretty.xml"), true);
		
	}
	catch (CXMLException E) {
		cout << "Exception caught: " << E.getMessage();
	}

	ss << "Testing attributenames" << endl;
	TestAttributeName(ss, XB, "Hello world");
	TestAttributeName(ss, XB, "helloworld");
	TestAttributeName(ss, XB, "3elloworld");
	TestAttributeName(ss, XB, "_elloworld");
	TestAttributeName(ss, XB, " _elloworld");
	TestAttributeName(ss, XB, "_elloworld  ");
	TestAttributeName(ss, XB, "Hell<o");
	TestAttributeName(ss, XB, "Hello\"d");


	return ss.str();

	*/
	_game->exportWorldAsXML("test_pretty.xml");
	return "World exported";

}

string CTestCommand::getCommandHelp() {
	return "This calls the currently configured test to be called.";
}
