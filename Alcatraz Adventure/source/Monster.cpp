// ----------------------------------------------------------------------- //
//
// MODULE  : Monster.cpp
//
// CREATED : 04.24.2009
// PURPOSE : Implementation of the Monster object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#pragma warning( disable : 4996 )
#include <iostream>
#include "Room.h"
#include "Treasure.h"
#include <fstream>
#include "Monster.h"

Monster::Monster(void) {
	name[0] = '\0';
	description[0] = '\0';
	health = -1;
}
Monster::Monster(char n[], char d[], int v) {
	strcpy(name, n);
	strcpy(description, d);
	health = v;
}
void Monster::setName(char* n) {
	strcpy(name,n); //copies name to n
}

void Monster::setDescription(char* n) {
	strcpy(description,n); //copies description to n
}

int Monster::getHealth(void) {
	return health; //returns treasure value
}

void Monster::getName(char n[]) {
	strcpy(name, n); //copies n to name
}
void Monster::setHealth(int h){
	health=h;
}

void Monster::getDescription(char n[]) {
	strcpy(description, n);
}
void Monster::input(ifstream& in2) {
	in2.ignore(1);
	in2.getline(name,50);
	in2.getline(description,300);
	in2 >> health;
	in2.ignore(1);
	
}
//handles all output
void Monster::output(ostream& out2) {
	out2 << "In here is " << name << endl<< description << endl;
		cout<< name <<" currently has " << health << " hp" << endl;
}
Monster::~Monster(void)
{
}