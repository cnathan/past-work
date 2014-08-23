// ----------------------------------------------------------------------- //
//
// MODULE  : Treasure.cpp
//
// CREATED : 04.24.2009
// PURPOSE : Implementation of the Treasure object
// AUTHOR  : Justin Mckennon, Barry Gaffey, Craig Nathan
//
// ----------------------------------------------------------------------- //
#include <iostream>
#include <cstring>
#include "Treasure.h"
#include <fstream>
#include <vector>
using namespace std;

//default constructor
Treasure::Treasure(void) {
	name[0] = '\0';
	description[0] = '\0';
	value = -1;
}
//copy constructor
//Treasure::Treasure(Treasure &a) {
//	//char title[50];
//	//char Descrip[300];
//	//a.getName(title);	
//	//a.getDescription(Descrip);
//	//strcpy(name, title);
//	//strcpy(description, Descrip);
//
//	value = a.getValue();
//
//	char* Nptr = new char [50];
//	for(int i(0);i<50;i++)
//		Nptr[i] = a.name[i];
//	for(int j(0);j<50;j++)
//		name[j] = Nptr[j];
//	delete [] Nptr;
//
//	char* Dptr = new char [300];
//	for(int k(0);k<300;k++)
//		Dptr[k] = a.description[k];
//	for(int ii(0);ii<300;ii++)
//		description[ii] = Dptr[ii];
//	delete [] Dptr;
//}
//copies name description and value
Treasure::Treasure(char n[], char d[], int v) {
	strcpy(name, n);
	strcpy(description, d);
	value = v;
}
Treasure::~Treasure(void)
{}
void Treasure::setName(char* n) {
	strcpy(name,n); //copies name to n
}
void Treasure::setDescription(char* n) {
	strcpy(description,n); //copies description to n
}
void Treasure::setValue(int v) {
	value = v; //sets value based on input file
}
int Treasure::getValue(void) {
	return value; //returns treasure value
}
void Treasure::getName(char n[]) {
	strcpy(name, n); //copies n to name
}
void Treasure::getDescription(char n[]) {
	strcpy(description, n);
}
//handles input to treasure
void Treasure::input(ifstream& in1) {
	in1.getline(name,50);
	in1.getline(description,300);
	in1 >> value;
	in1.ignore(1);
}
//handles all output
void Treasure::output(ostream& out) {
	out << "You notice " << name << "  in here" <<" ("<<  description << ")" << endl
		<< "Using your expertise, you know the " << name << " is valued at about: $" << value << endl;
}
void Treasure::pickUpItem(char n[])
{
	vector<string>treasurelist;
	strcpy(n,name);
	treasurelist.push_back(n);
}
bool Treasure::operator ==(const Treasure& rhs) const
{
	for(int i(0);i<50;i++)
	{
		if(name[i]!=rhs.name[i])
			return false;
	}
	for(int j(0);j<300;j++)
	{
		if(description[j]!=rhs.description[j])
			return false;
	}
	return true;
}
bool Treasure::operator !=(const Treasure &rhs) const
{
	if(rhs==*this)
		return false;
	else
		return true;
}
char* Treasure::Aname()
{
	return name;
}
char* Treasure::Adescription()
{
	return description;
}