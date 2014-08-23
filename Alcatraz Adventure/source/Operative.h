// ----------------------------------------------------------------------- //
//
// MODULE  : Operative.h
//
// CREATED : 05.11.2009
// PURPOSE : Definition of the Operative object
// AUTHOR  : Barry Gaffey
//
// ----------------------------------------------------------------------- //
#pragma once
#include <vector>
#include "Treasure.h"
#include "Player.h"

using namespace std;
class Operative
{
public:
	Operative(void);
	~Operative();
	Treasure getProduct(int ele);
	Treasure getSpecProd(unsigned int ele);
	void buyProduct(Treasure item, Player& Pl);
	bool sellProduct(Treasure item, Player& Pl);
	void printProducts(void);
	bool isSpecEmpty(void);
	unsigned int getSpecSize(void);
private:
	vector<Treasure> Products;
	vector<Treasure> SpecProd;
};