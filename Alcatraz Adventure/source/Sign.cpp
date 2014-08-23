// ----------------------------------------------------------------------- //
//
// MODULE  : Sign.cpp
//
// CREATED : 04.24.2009
// PURPOSE : Implementation of the Sign object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#include "Sign.h"
#include <iostream>
#include <fstream>

using namespace std;

Sign::Sign(void)
{
	info[0]='\0';
}

void Sign::input(ifstream& in2) 
{
	in2.getline(info,300);
}
void Sign::output(ostream& out4)
{
	out4<<" You walk over to the sign. It reads : "<< info<<endl;
}
void Sign::setName(char* n) {
	strcpy(info,n);
}

Sign::~Sign(void)
{
}