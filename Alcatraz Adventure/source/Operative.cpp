// ----------------------------------------------------------------------- //
//
// MODULE  : Operative.cpp
//
// CREATED : 05.11.2009
// PURPOSE : Implementation of the Operative object
// AUTHOR  : Barry Gaffey
//
// ----------------------------------------------------------------------- //
#include <iostream>
#include <vector>
#include "Operative.h"
#include "Treasure.h"
using namespace std;
Operative::Operative(void)
{
	/* Native Items of the Operative (They should have an infinite amount) */
	Treasure Rifle("M-16","Government Issue - Full Metal Jacket", 75);
	Treasure Chip("Computer Chip","It's an IC and it appears to be a replica of a missile guidance system",2500);

	Products.push_back(Rifle);
	Products.push_back(Chip);
}
Operative::~Operative()
{
}
Treasure Operative::getProduct(int ele)
{
	return Products.at(ele);
}
Treasure Operative::getSpecProd(unsigned int ele)
{
	if((ele>=SpecProd.size()) || (ele<0))
	{
		ele = 0;
		cout << "\n\tYou can't pick that!   Defaulting to first item. . ." << endl;
	}
	return SpecProd.at(ele);
}
void Operative::buyProduct(Treasure item, Player& Pl)
{
	/* The operative buys an item from the player */
	if(SpecProd.size()!=20) {
		SpecProd.push_back(item);
		/* Player of type Player, is the user in main */
		Pl.addMoney(item.getValue());
		Pl.removeIt(item);
		cout << "\n Good Job! I'll be sure this gets in the right hands" << endl;
	}
	else {
		cout << "\n\tSorry, I can't purchase anymore items!\n" << endl;
	}
}
bool Operative::sellProduct(Treasure item, Player& Pl)
{
	/* The operative sells an item to the player */
	if((Pl.getMoney()-item.getValue())>=0) {
		
		bool MyNameisWhat(false);
		(Pl.getInvsize()==5) ? (MyNameisWhat=true) : 0;
		if(MyNameisWhat)
		{
			cout << "\nYou don't have enough space to carry this item!" << endl;
			return false;
		}

		Pl.takeMoney(item.getValue());
		/* Find out if we sold special stock */
		vector<Treasure>::iterator itProd = SpecProd.begin();
		while(itProd != SpecProd.end()) {
			//(!strcmp(itProd->Aname(),item.Aname())) && (itProd->getValue()==item.getValue()) && (!strcmp(itProd->Adescription(), item.Adescription()))
			if(*itProd==item)
			{
				itProd = SpecProd.erase(itProd);
				break;
			}
			else
				++itProd;
		}
		Pl.addItem(item);
		return true;
	}
	else {
		cout << "\nHeh heh, You can't afford this." << endl;
		return false;
	}
}
void Operative::printProducts()
{
	/* Prints Items available for sale */
	cout << "\nWhat would you like to buy?" << endl;
	vector<Treasure>::iterator itP = Products.begin();
	vector<Treasure>::iterator itS = SpecProd.begin();
	
	cout << " I have plenty of these.\n" << endl;
	cout << "R:\t" << itP->Aname() << "    $" << itP->getValue() << endl;
	cout << itP->Adescription() << '\n' << endl;

	++itP;
	cout << "C:\t" << itP->Aname() << "    $" << itP->getValue() << endl;
	cout << itP->Adescription() << endl;
	cout << '\n';
	
	if(!SpecProd.empty()) {
		cout << "\n Why kill yourself for these items? You can buy them here.\n" << endl;
		int nItem(0);
		for(itS;itS!=SpecProd.end();itS++) {
			cout << nItem << ":\t" << itS->Aname() << "    $" << itS->getValue() << endl;
			cout << itS->Adescription() << '\n' << endl;
			nItem++;
		}
	}
}
bool Operative::isSpecEmpty(void)
{
	if(SpecProd.empty())
		return true;
	else
		return false;
}
unsigned int Operative::getSpecSize(void)
{
	return SpecProd.size();
}
#pragma message( "Chuck_Norris.h" )
#pragma message( "Chuck_Norris operator overloaded Nathan member" )