// ----------------------------------------------------------------------- //
//
// MODULE  : Sign.h
//
// CREATED : 04.24.2009
// PURPOSE : Definition of the Sign object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#pragma once
#pragma warning( disable : 4996 )
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Sign
{
private:
	char info[300];
public:
	Sign(void);
	void input(ifstream& in);
	void output(ostream& out);
	void setName(char* n);
	~Sign(void);
};