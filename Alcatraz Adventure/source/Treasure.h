// ----------------------------------------------------------------------- //
//
// MODULE  : Treasure.h
//
// CREATED : 04.24.2009
// PURPOSE : Definition of the Treasure object
// AUTHOR  : Justin Mckennon, Barry Gaffey II, Craig Nathan
//
// ----------------------------------------------------------------------- //
#pragma once
#pragma warning( disable : 4996 )
#include <iostream>
#include <iomanip>
#include <vector>  // Currently Unnecessary

using namespace std;
//treasure header file
class Treasure
{
protected:
	char name[50]; //ensures user cannot modify name
	char description[300]; //ensures user cannot modify description
	int value; //ensures user cannot modify value
public:
	Treasure(void);
	//Treasure(Treasure& a);
	Treasure(char n[],  char d[],  int v);
	~Treasure(void);
	
	void setName(char* n);
	void setDescription( char* n);
	void setValue( int v);
	int getValue() ;
	void getName(char n[]);
	void getDescription( char n[]);
	void input( ifstream& in);
	void output( ostream& out);
	void pickUpItem(char n[]);
	void printTreasure(); // unused?
	char* Aname(void); // New Asscessor for name
	char* Adescription(void); // New Asscessor for description
	bool operator ==(const Treasure& rhs) const; //new
	bool operator !=(const Treasure& rhs) const; //new
};