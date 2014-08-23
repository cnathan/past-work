// ----------------------------------------------------------------------- //
//
// MODULE  : Room.h
//
// CREATED : 04.24.2009
// PURPOSE : Definition of the Room object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#pragma once
#pragma warning( disable : 4996 )
#include <iostream>
#include <fstream>
#include <cstring>
#include "Treasure.h"
#include "Monster.h"
#include "Sign.h"

using namespace std;

//room header file
class Room
{
public:
	Room(void);
	~Room(void);
	void setName(char* n);
	void setDescription(char* n);
	void setItem(Treasure& item);
	void setMonster(Monster& monster);
	//void setSign(Sign& sign);
	void getName(char n[]);
	void getDescription(char n[]);
	int getExit(char nsew);
	void input(ifstream &in);
	void output(ostream &out);

private:
	char name[50]; //ensures user cannot modify name
	char description[300];//ensures user cannot modify description
	int exit[4]; //ensures user cannot modify exits
	Treasure item; //ensures every room has a treasure
	Monster monster;
	Sign sign;
	

};