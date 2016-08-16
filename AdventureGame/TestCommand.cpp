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

string CTestCommand::call() {
	stringstream ss = stringstream();
	ss << "Creating XML Builder" << endl;

	CXMLBuilder XB = CXMLBuilder("testObject");
	ss << "XMLBuilder created:\n";	

	XB.addElement("subElement");
	XB.addAttribute(string("attributeName1"), string("attribute value1"));
	XB.addAttribute(string("attributeName2"), string("attribute value2"));
	XB.finishElement();

	XB.saveToFile("test_pretty.xml", true);
	XB.addElement("test");
	XB.saveToFile("test.xml", false);
			
	return ss.str();
}

string CTestCommand::getCommandHelp() {
	return "This calls the currently configured test to be called.";
}
