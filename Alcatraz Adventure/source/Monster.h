// ----------------------------------------------------------------------- //
//
// MODULE  : Monster.h
//
// CREATED : 04.24.2009
// PURPOSE : Definition of the Monster object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#pragma once
#include <iostream>
#include "Room.h"
#include "Treasure.h"
#include <fstream>
#include "Monster.h"

class Monster
{
protected:
	char name[40];
	char description[300];
	int health;
public:
	Monster(void);
	Monster(char n[],  char d[],  int v);
	~Monster(void);
	void setName(char* n);
	void setDescription(char* n);
	void setHealth(int h);
	int getHealth();
	void getName(char n[]);
	void getDescription(char n[]);
	void input(ifstream &in);
	void output(ostream &out);
};