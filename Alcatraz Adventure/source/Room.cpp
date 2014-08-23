// ----------------------------------------------------------------------- //
//
// MODULE  : Room.cpp
//
// CREATED : 04.24.2009
// PURPOSE : Implementation of the Room object
// AUTHOR  : Justin Mckennon
//
// ----------------------------------------------------------------------- //
#include <iostream>
#include "Room.h"
#include "Treasure.h"
#include <fstream>
#include "Monster.h"

using namespace std;

//default constructor
Room::Room(): item("", "", 0), monster("","",0) {
	name[0] = '\0';
	description[0] = '\0';
	for(int a=0; a<4; a++)
		exit[a] = -1;
}

//destructor
Room::~Room(void) {
}
//takes name and copies it to n
void Room::setName(char* n) {
	strcpy(name, n);
}
//copies description to n
void Room::setDescription(char* n) {
	strcpy(description, n);
}

void Room::setItem(Treasure& a) {
	item = a;
}
void Room::setMonster(Monster& a){
	monster=a;
}
//copies n to name
void Room::getName(char n[]) {
	strcpy(name, n);
}
//copies n to description
void Room::getDescription(char n[]) {
	strcpy(description, n);
}
//based on file exits, returns exit value
int Room::getExit(char nsew) 
{
	switch (nsew) {
		case 'n':
			return exit[0];
		case 's':
			return exit[1];
		case 'e':
			return exit[2];
		case 'w':
			return exit[3];
		default:
			cout << "\n\n\tI need to take my pill, BrB~\n\n" << endl;
			return -1;
			break;
	}
}

// handles all file inputs
void Room::input(ifstream& in1) {
	in1.getline(name,50);
	in1.ignore(1);
	in1.getline(description,300);
	in1 >> exit[0] >> exit[1] >> exit[2] >> exit[3];
	in1.ignore(1);
}
//handles all outputs
void Room::output(ostream& out1) {
	out1 <<endl<<"You are now in the "<< name << endl
		<< description << endl;
}