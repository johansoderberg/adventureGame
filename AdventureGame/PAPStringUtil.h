#pragma once
#include <string>

using namespace std;

// Compares two strings case insensitively by tranforming both to lowercase first.
bool strCompareLC(const string str1, const string str2);

// Trim a string from start (modifies the reference)
void trimFromLeft(std::string &s);

// Trim a string from end (modifies your reference)
void trimFromRight(std::string &s);

// Trim a string from both ends (modifies your reference)
void trim(std::string &s);

// Trim a string from start (returns a copy)
string trimmedFromLeft(string s);

// Trim a string from end (returns a copy)
string trimmedFromRight(string s);

// Trim a string from both ends (returns a copy)
string trimmed(string s);

// Returns a lowercase copy of the string
string strToLower(string *str);