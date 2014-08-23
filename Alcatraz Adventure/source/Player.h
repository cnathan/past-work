// ----------------------------------------------------------------------- //
//
// MODULE  : Player.h
//
// CREATED : 04.24.2009
// PURPOSE : Definition of the Player object
// AUTHOR  : Justin Mckennon, Barry Gaffey
//
// ----------------------------------------------------------------------- //
#pragma once
#pragma warning( disable : 4996 )
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "Treasure.h"

using namespace std;
class Player
{
private:
	int health;
	char name[25];
	char weapon[15];
	char armor[20];
	int Money; //new
	vector<Treasure> Inventory; //new

public:
	void addMoney(int credit); //new
	void takeMoney(int debt); //new
	int getMoney(void); //new
	void weaponEquip(char* n);
	void getWeapon(char n[]);
	void armorEquip(char* n);
	void getArmor(char n[]);
	void setHealth(int v);
	void setName(char* n);
	void getName(char n[]);
	void input(istream &in);
	int getHealth();
	void output(ostream &out);
	void addItem(Treasure item);
	void removeItem(unsigned int nItem);
	void removeIt(Treasure Item);
	void emptyInventory(void);
	void printInventory(void);
	Treasure getInvItem(unsigned int ele);
	bool isInventoryEmpty(void);
	unsigned int getInvsize(void);
	unsigned int getInvcap(void);
	void printScore(void);

	Player(void);
	Player(char n[],char w[], char a[], int h, int mon);
	~Player(void);
};
#pragma message( "Craigs Mum overloaded at 0xEEF0" )