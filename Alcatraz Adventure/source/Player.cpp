// ----------------------------------------------------------------------- //
//
// MODULE  : Player.cpp
//
// CREATED : 04.24.2009
// PURPOSE : Implementation of the Player object
// AUTHOR  : Justin Mckennon, Barry Gaffey
//
// ----------------------------------------------------------------------- //
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "windows.h"
#include "Player.h"
using namespace std;

Player::Player(void)
{
	name[0]='\0';
	weapon[0]= '\0';
	armor[0]= '\0';
	health = 50;
	Money = 0; // set this to 0 for releases... only for debugging purposes!
}
Player::Player(char n[],char w[], char a[], int h, int mon)
{
	strcpy(name, n);
	strcpy(weapon, w);
	strcpy(armor, a);
	health=h;
	Money = mon;
}
void Player::weaponEquip(char* n) {
	strcpy(weapon, n); 
}
void Player::armorEquip(char* n) {
	strcpy(n, armor);
}
void Player::setHealth(int h) {
	health = h;
}
int Player::getHealth(void) {
	return health; 
}
#pragma message( "Houghton Virus Constructed" )
void Player::getWeapon(char n[]) {
	strcpy(weapon,n); 
}
void Player::getArmor(char n[]) {
	strcpy(n, armor);
}
void Player::getName(char n[])
{
	strcpy(n,name);
}
void Player::input(istream &in)
{
	cout <<" The pilot leans back and says 'Hey kid, who are you?' " << endl << "(Enter your name)" << endl;
	in.getline(name,25);
	system("cls");
	cout << "Okay " << name << ".\nWhat are you bringing with you.\nI want to make sure you're ready for this.\nI won't have you die on me. " << endl;
	cout << "(Enter your weapon name)" << endl;
	in.getline (weapon, 15);
	cout << "(Enter your armor)" << endl;
	in.getline(armor,20);
	system("cls");
#pragma message( "Player Gaffey died at: 0xCC9E" )
}
void Player::output(ostream &out)
{
	out << "The pilot yells back...\nOkay " << name << ",\nT-Minus 30 seconds until arrival.\nGrab your " << weapon << " and " << armor << " and prepare to jump." << endl;
}
Player::~Player(void)
{
}
void Player::addMoney(int credit)
{
	Money+=credit;
}
void Player::takeMoney(int debt)
{
	Money-=debt;
}
int Player::getMoney(void)
{
	return Money;
}
void Player::addItem(Treasure item)
{
	Inventory.push_back(item);
}
void Player::removeItem(unsigned int nItem)
{
	if(!Inventory.empty())
	{
		if((nItem > Inventory.size()-1) || (nItem < 0))
			nItem = 0;
		vector<Treasure>::iterator invIt = Inventory.begin();
		int nRef(0);

		while(invIt != Inventory.end()) {
			if(nRef==nItem)
			{
				invIt = Inventory.erase(invIt);
				if(Inventory.empty())
					emptyInventory();
				break;
			}
			else {
				++invIt;
				++nRef;
			}
		}
	}
}
void Player::removeIt(Treasure Item)
{
	if(!Inventory.empty())
	{
		vector<Treasure>::iterator endit = Inventory.begin();
		while(endit != Inventory.end())
		{
			if(*endit==Item)
			{
				endit = Inventory.erase(endit);
				break;
			}
			else
				++endit;
		}
	}
}
void Player::emptyInventory(void)
{
	Inventory.clear();
}
void Player::printInventory(void)
{
	int Smirnoff(0);
	vector<Treasure>::iterator crapcola = Inventory.begin();
	cout << '\n';
	cout << "You have " << Inventory.size() << " item(s)." << endl;
	cout << "Your Inventory: " << endl;
	cout << "  ItemNumber: \n";
	for(crapcola;crapcola!=Inventory.end();crapcola++) {
		cout << '\t' << Smirnoff << ' ' << crapcola->Aname() << endl;
		Smirnoff++;
	}
	cout << "\n You have $" << getMoney() << '.' << endl;
	cout << '\n';
}
Treasure Player::getInvItem(unsigned int ele)
{
	if(ele>=Inventory.size())
		ele = 0;
	if(ele<0)
		ele = 0;
	return Inventory.at(ele);
}
bool Player::isInventoryEmpty(void)
{
	if(Inventory.empty())
		return true;
	else
		return false;
}
unsigned int Player::getInvsize(void)
{
	return Inventory.size();
}
unsigned int Player::getInvcap(void)
{
	return Inventory.capacity();
}
void Player::printScore(void)
{
	cout << "\n\n\n\n\n\t\t" << name << " has earned $" << Money << " with a " << weapon << " and " << armor << '.' << endl;
	cout << "\n\n\nPress Enter to continue" << endl;
	cin.get();
}