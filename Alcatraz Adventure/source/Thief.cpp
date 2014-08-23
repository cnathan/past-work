// ----------------------------------------------------------------------- //
//
// MODULE  : Thief.cpp
//
// CREATED : 04.24.2009
// PURPOSE : Implementation of the Thief object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#include "Thief.h"

Thief::Thief(void)
{
}
int Thief::getLocation()
{
	return location;
}

void Thief::setLocation(int x)
{
	location= x;
}
Thief::~Thief(void)
{
}