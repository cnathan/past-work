// ----------------------------------------------------------------------- //
//
// MODULE  : Thief.h
//
// CREATED : 04.24.2009
// PURPOSE : Definition of the Thief object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#pragma once

class Thief
{
private:
	int location;



public:
	Thief(void);
	~Thief(void);
	int getLocation();
	void setLocation( int x);
};