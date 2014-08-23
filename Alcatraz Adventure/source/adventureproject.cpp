// ----------------------------------------------------------------------- //
//
// MODULE  : adventureproject.cpp
// LAB     : OOP Software Development - Final Project - Alcatraz 
// CLASS   : ECE 264-01
// TEACHER : Professor M. Geiger
// CREATED : 04.24.2009
// AUTHOR  : Justin McKennon, Barry Gaffey, Craig Nathan
//
// ----------------------------------------------------------------------- //
#pragma message( "Last modified on " __TIMESTAMP__ )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "Treasure.h"
#include "Room.h"
#include "Thief.h"
#include "Monster.h"
#include "Player.h"
#include "Sign.h"
#include "Operative.h"
#include "windows.h"
using namespace std;

#pragma region functPrototypes
void futureRoom(Room& Room, Treasure& Treasurejus,  int& roomIndex, int numOfRooms, Monster& Monster,Sign& Sign, int &music, vector<Operative>& Ops, Player& PLAY, int Primitive);
void currentRoom(Room& Room, Treasure& Treasurejus, Monster& Monster,Sign& Sign, int& roomIndex, ifstream& in1, bool Em);
void printAll(Room& Room, Treasure& Treasurejus, Monster& Monster);
int thiefLocation(int& roomIndex, int numOfRooms);
int index(int &roomIndex);
void printPlayer(Player& Player);
int gameEnd(int &roomIndex);
bool editMode(Player& Player);
/* Game Music */
void m_title();
void m_victory();
void m_defeat();
void m_credits_rone();
void m_credits_roneb();
void m_credits_ronec();
void m_credits_roneh();
void m_credits_rtwo();
void m_credits_rtwoh();
void m_credits_rthree();
void m_credits_rthreeh();
void m_credits_rthreehb();
/* Game Credits */
void c_mus();
void c_nomus();
#pragma endregion functPrototypes
bool editMode(Player& Player)
{
	char n[25];
	string name;
	string name2="edit mode";
	Player.getName(n);

	if(n==name2)
	{
		return true;
	}
	else
		return false;
}
int gameEnd(int &roomIndex)
{
	int x(0);
	x=roomIndex;

	if(x==21)
	{
		return 1;
	}
	else
		return 0;
}
void printPlayer(Player& Player)
{
	Player.output(cout);
}
int index(int &roomIndex)
{
	return roomIndex;
}
int thiefLocation(int numOfRooms)
{
	Thief Thief;
	int location(0);
	int ThiefIndex(0);
	srand(time(NULL));
	location= rand() % numOfRooms;
	Thief.setLocation(location);
	ThiefIndex= Thief.getLocation();
	return ThiefIndex;
}
void currentRoom(Room& Room, Treasure& Treasurejus, Monster& Monster,Sign& Sign, int& roomIndex, ifstream& in1, bool Em) //determines the information of the room the player is currently in
{
	int futureRoom = -1;
	in1.close();
	if(Em)
		in1.open("mod.txt");
	else
		in1.open("rooms.txt");//opens the file rooms.txt
	in1.ignore(2);//ignores the total number of rooms and roomIndex

	in1 >> futureRoom;
	while(futureRoom <= roomIndex)
	{
		in1.ignore(1);//ignores carriage return
		Room.input(in1); //reads in the information for the room
		Treasurejus.input(in1);//reads in the treasure information	
		Monster.input(in1);
		Sign.input(in1);
		in1 >> futureRoom;
	}
}
void futureRoom(Room& Room, Treasure& Treasurejus, int& roomIndex, int numOfRooms, Monster& Monster, Sign& Sign, int &music, vector<Operative>& Ops, Player& PLAY, int Primitive) //determines the next room based on the user's input
{
	char direction;
	int IwantToBeSure(Primitive);
	int goddamnitJustin = roomIndex;
	char Justin('\0');
	roomIndex = -1;
	vector<Operative>::iterator IT = Ops.begin();

	while (roomIndex < 0)
	{
		//cout<<" Which direction would you like to travel? "<< endl;
		cout << "\n\tType H (help) for a list of commands" << endl;
		cout << "What would you like to do ?" << endl;

		cout << ">";
		cin >> direction;
		
		direction = tolower(direction);
		
		//uses the get exit function in room.cpp to determine direction and whether or not it is a valid exit
		switch(direction) {
			case 'n':
			case 'w':
			case 'e':
			case 's':
				roomIndex = Room.getExit(direction);

				if (roomIndex == -1)
					cout << "You can't go that way!" << endl;
				break;
			case 'l':
				Sign.output(cout); //prints the information for the room and treasure
				break;

			case 'x':
				roomIndex = numOfRooms;
				return; //exits
			case 'm':
				if(music==1) {
					music*=0;
					cout << "\n\tThe Music is off" << endl;
				}
				else {
					music=1*1;
					cout << "\n\tThe Music is on" << endl;
				}
				break;
			case 'o': // Operative
				cout << "\n\tYou contact the local Operative. . ." << endl;
				if(goddamnitJustin>=(IwantToBeSure-1))
				{
					cout << "\n\tThere's no Agent in here!" << endl;
					break;
				}
				for(int HoughtonsMother(0);HoughtonsMother<goddamnitJustin;HoughtonsMother++)
					IT++;

				IT->printProducts();

				cout << "\n\tWhat would you like to do?" << endl;
				cout << "\n\tType:\n\t\tB to buy\n\t\tS to Sell\n\t\tQ to leave\n" << endl;

				Justin = '\0';
				cin >> Justin;
				Justin = toupper(Justin);

				if(Justin=='B') {
					cout << "\nWhat would you like to purchase?" << endl;
					/* PLAYER WANTS TO MAKE A PURCHASE */
					cout << "Type:\n\tR for regular products\n\tS for special products" << endl;
					char AJH('\0');
					cin >> AJH;
					AJH = toupper(AJH);

					if(AJH=='R') {
						/* Regular products */
						cout << "\nWhich one would you like? I have plenty." << endl;
						char AH('\0');
						cin >> AH;
						AH = toupper(AH);
						if(AH=='R') {
							//purchased a rifle
							if(IT->sellProduct(IT->getProduct(0), PLAY))
								cout << "\nI hope this helps you, Good Luck!\n" << endl;
							//else
								//cout << "\nHeh heh, You can't afford this." << endl;
						}
						else if(AH=='C') {
							//purchased a computer chip
							if(IT->sellProduct(IT->getProduct(1), PLAY))
								cout << "\nI hope this helps you, Good Luck!\n" << endl;
							//else
								//cout << "\nHeh heh, You can't afford this." << endl;
						}
						else {
							cout << "\nI...I don't understand your request." << endl;
						}
					}
					else if(AJH=='S') {
						// should be in buy menu, buying a special stock item
						if(!IT->isSpecEmpty())
						{
							cout << "Ah, you'd like one of my special offers, which one?\n" << endl;
							unsigned int solong(0);
							cin >> solong;
							if(IT->sellProduct(IT->getSpecProd(solong), PLAY))
							{
								cout << "\nI hope this helps you, Good Luck!\n" << endl;
							}
							//else
							//	cout << "\nHeh heh, You can't afford this." << endl;
						}
						else
							cout << "\nSorry Sir, I couldn't find anything special around here." << endl;
					}
					else
						cout << "You don't want to buy anything? I see. . ." << endl;
				}
				else if(Justin=='S') {
					// PLAYER WANTS TO SELL AN ITEM TO AGENT
					cout << "\nWhat do you want to sell him?\n" << endl;
					PLAY.printInventory();
					if(!PLAY.isInventoryEmpty())
					{
						cout << "Enter the Item number you wish to sell to the agent" << endl;
						unsigned int argh(0);
						cin >> argh;
						if((argh<PLAY.getInvsize()) && (argh>=0))
						{
							IT->buyProduct(PLAY.getInvItem(argh), PLAY);
						}
						else
							cout << " There's no item here. . ." << endl;
					}
					else
						cout << "\nYou have nothing to sell him!" << endl;
				}
				else if(Justin=='Q') {
					cout << "\nYou quietly leave the Agent alone. . ." << endl;
				}
				else {
					cout << "\nYour inability to communicate compromised the Agent's undercover status!\nYou both hide." << endl;
				}
				break;
			case 'i':
				PLAY.printInventory();
				break;
			case 'h':
				cout << "\t\tN, S, E, W to move North, South, East, West\n\t\tI to check your inventory\n\t\tO to look for a helpful undercover agent" << endl;
				cout << "\t\tL to get helpful advice from Mason\n\t\tM to toggle the Game's music\n\t\tX to exit the game\n" << endl;
				break;
			case 'c':
				PLAY.addMoney(10000);
				break;
			default:
				cout << "\n\n\tERROR: Unrecognized Command\n\n" << endl;
				break;
		}
	}
	system("cls");
}
void printAll(Room& Room, Treasure& Treasurejus, Monster& Monster)
{
	Room.output(cout); //prints out  the information of the room when cout is passed as argument
	//Treasurejus.output(cout); //prints out treasure information
	Monster.output(cout); 
}
int main()
{
#pragma region local_dclr
	Room Room; //creates a room class
	Treasure Treasurejus; //creates a treasure class
	Thief Thief;
	Monster Monster;
	Player Player;
	Sign Sign;
	//vector<string> treasureList; Disalbed WE USE PLAYER INVENTORY NOW, WITH TANGIBLE ITEMS ;) wink
	int thiefIndex(0);
	char choice;
	//char title[100]; Unreferenced C4101
	//char name[100];  Unreferenced C4101
	int value(0);
	char decision;
	int mHealth(0);
	int pHealth(0);
	int pDamage(0);
	int mDamage(0);
	int random(0);
	int victory(-1);
	int lose(-1);
	unsigned int drop(0); // Soothe the warnings. . .
	int roomEditIndex(0);
	char option('1');
	char newName[40];
	char newDescription[300];
	int newValue(0);
	/* Music Control Variables */
	int nMusicToggle(1); // 0 is off, 1 is on
	char chMusAns('n');
	/* Load Pre-defined Maze Variables */
	char chRes('n');
	/* Inventory Control Variables */
	int nItemNum(0); // used in PlayerHasMaxInventory
	/* Operatives... */
	Operative Agent;
	vector<Operative> Agents;
	/* room treasure storage */
	vector<Treasure*> tlist;
	Treasure* tptr;
	Treasure Bogus("bogus","null",0);
	/* Bute Files Control */
	bool isMod(false);


	int DaRealRoomIndex(0);
	int numRooms(0);
	int roomIndex(0);
	ifstream in1;


#pragma endregion local_dclr
#pragma region init_music
	/* Pre-Game Music Prompt */
	cout << "Turn off Game Music? (y/n): ";
	cin >> chMusAns;
	chMusAns = tolower(chMusAns);
	if(chMusAns=='y') {
		nMusicToggle=0;
		cout << "\tThe Music is off." << endl;
	}
	else //End of Music Prompt
		cout << "\tThe Music is on." << endl;
#pragma endregion init_music
#pragma region init_game
	
	/* Load a game mod or the game itself */
	cout << "Load Alcatraz modification? (y/n): ";
	cin >> chRes;
	chRes = tolower(chRes);
	if(chRes=='y') {
		cout << "\nLoading Alcatraz Modification. . ." << endl;
		in1.open("mod.txt");
		isMod = true;

		/* Conditionial Statement, Error output and termination if bute file isn't found */
		if(!in1.is_open()) {
			cout << "Engine Error: Could not find Game Attribute File" << endl;
			cin.get();
			return 0;
		}
	}
	else {
		cout << "\nLoading Alcatraz. . ." << endl;
		in1.open("rooms.txt");

		/* Conditionial Statement, Error output and termination if bute file isn't found */
		if(!in1.is_open()) {
			cout << "Engine Error: Could not find Game Attribute File" << endl;
			cin.get();
			return 0;
		}
	}
#pragma endregion init_game

	cout << "\n\n Press Enter to start the game" << endl;
	cin.get();
	system("cls");

	in1 >> numRooms; // Now, we know how many rooms are in the game.
	
	int YouDuntMeanShtToMe(numRooms);

	for(int nCnt(0);nCnt<numRooms;nCnt++) {
		Agents.push_back(Agent);
	}
	vector<int> ItsTooLongMan(numRooms,0);

	tlist.resize(numRooms);


#pragma region title_scr
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << endl;
	cout<<"###############################################################################"<<endl;
	cout<<"###############################################################################"<<endl;
	cout<<"####   #   #########  #########################################################"<<endl;
	cout<<"##### ### ########### ####################################### #################"<<endl;
	cout<<"##### # # ###   ##### #####    ###   ##   # ####   #########     ####   #######"<<endl;
	cout<<"##### # # ## ### #### #### ### ## ### ## # # ## ### ######### ###### ### ######"<<endl;
	cout<<"##### # # ##     #### #### ###### ### ## # # ##     ######### ###### ### ######"<<endl;
	cout<<"##### # # ## ######## #### ###### ### ## # # ## ############# ### ## ### ######"<<endl;
	cout<<"###### # ####    ##     ###    ###   ##       ##    ##########   ####   #######"<<endl;
	cout<<"###############################################################################"<<endl;
	cout<<"###############################################################################"<<endl;
	cout<<"###############################################################################"<<endl;
	cout<<"####   #####     #######    # ####   #####       ##      ######   #####      ##"<<endl;
	cout<<"#####  ####### ######## ####  #####  ##### ## ## ### #### ######  ##### #### ##"<<endl;
	cout<<"#### ## ###### ####### ###### #### ## #### ## ## ### #### ##### ## ######## ###"<<endl;
	cout<<"#### ## ###### ####### ########### ## #### ## ## ### #### ##### ## ####### ####"<<endl;
	cout<<"#### ## ###### ####### ########### ## ####### ######     ###### ## ####### ####"<<endl;
	cout<<"###      ##### #### ## ##########      ###### ###### ## ######      ##### #####"<<endl;
	cout<<"### #### ##### #### ## ########## #### ###### ###### ### ##### #### #### ### ##"<<endl;
	cout<<"## ###### #### #### ### ##### ## ###### ##### ###### #### ### ###### ## #### ##"<<endl;
	cout<<"#   ####   #        ####     ##   ####   ##     ###   ###  #   ####   #      ##"<<endl;
	cout<<"###############################################################################"<<endl;
	cout<<"###############################################################################"<<endl;
	cout << endl << "\n\t\tEnjoy your playing experience"<<endl<<endl<<"\t\t\t     A \n\t\t\tJustin McKennon\n\t\t\tJosh LaClair\n\t\t\tAdam Houghton\n\t\t\tBarry Gaffey\n\t\t\tCraig Nathan\n\n\t\t\t Production"<<endl;

	if(nMusicToggle==1)
		m_title();

	cout<<endl;
#pragma endregion title_scr
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Player.input(cin);
	Player.output(cout);


#pragma region game_loop


	while(roomIndex < numRooms)//ensures roomindex is valid
	{
		currentRoom(Room, Treasurejus,Monster,Sign, roomIndex, in1, isMod);
		ifstream in1; //creates an input stream named in1

		DaRealRoomIndex = roomIndex;
		/* Spawn native item... */
		bool FridayNightLights(true);
		int BallsMadeofSTEEL(0);
		
		BallsMadeofSTEEL = 0;

		
		if(ItsTooLongMan.at(roomIndex)==0) {
			tptr = new Treasure[5];
			Treasure fucker(Treasurejus.Aname(), Treasurejus.Adescription(), Treasurejus.getValue());
			tptr[0] = fucker;
			for(int doggy(1);doggy<5;doggy++)
				tptr[doggy] = Bogus;
			tlist.at(roomIndex)=tptr;
			ItsTooLongMan.at(roomIndex) = 1;
		}
		if((tlist.at(DaRealRoomIndex))[0]==Bogus)
		{
			tlist.at(DaRealRoomIndex)[0].setName(Treasurejus.Aname());//err
			tlist.at(DaRealRoomIndex)[0].setDescription(Treasurejus.Adescription());//err
			tlist.at(DaRealRoomIndex)[0].setValue(Treasurejus.getValue()); //err
		}

#pragma region editMode
		if(editMode(Player))
		{
			cout<<"You have entered the editing portion of this program. "<<endl<<endl;
			cout<<"In this mode, you can edit the characteristics of the rooms supplied in the text file "<<endl
				<<" Keep in mind, this may alter the playing experience and flow of the program."<<endl<<endl;
			cout<<"Enter the number of the option you would like to edit (Enter x if you are finished) "<<endl;
			cout<<"1. Room Name "<<endl<<"2. Room Description "<<endl<<"3. Treasure Name"<<endl<<"4. Treasure Description"<<endl
				<<"5. Treasure Value"<<endl<<"6. Monster Name"<<endl<<"7. Monster Description"<<endl<<"8. Monster Health"<<endl
				<<"9. Sign information"<<endl<<"> ";
			cin>>option;
			system("cls");
			while(option!='x')
			{

				if(option== '1')
				{
					cout<<"Enter the new Room Name: ";

					cin>>newName;
					Room.setName(newName);
					cout<<endl;
					system("cls");

				}
				if(option=='2')
				{
					cout<<"Enter the new Room Description: ";
					newDescription[0]='\0';
					cin>>newDescription;
					Room.setDescription(newDescription);
					cout<<endl;
					system("cls");

				}
				if(option== '3'){
					cout<<"Enter the new treasure Name: ";
					newName[0]='\0';
					cin>>newName;
					Treasurejus.setName(newName);
					cout<<endl;
					system("cls");
				}

				if(option=='4'){
					cout<<"Enter the new treasure description: ";
					newDescription[0]='\0';
					cin>>newDescription;
					Treasurejus.setDescription(newDescription);
					cout<<endl;
					system("cls");
				}
				if(option=='5'){
					cout<<" Enter the new treasure value: ";
					cin>>newValue;
					Treasurejus.setValue(newValue);
					cout<<endl;
					system("cls");
				}
				if(option== '6'){
					cout<<"Enter the new Monster Name: ";
					newName[0]='\0';
					cin>>newName;
					Monster.setName(newName);
					cout<<endl;
					system("cls");
				}
				if(option== '7'){
					cout<<"Enter the new Monster Description: ";
					newDescription[0]='\0';
					cin>>newDescription;
					Monster.setDescription(newDescription);
					cout<<endl;
					system("cls");
				}
				if(option== '8'){
					cout<<"Enter the new Monster health: ";
					cin>>newValue;
					Monster.setHealth(newValue);
					cout<<endl;
					system("cls");
				}
				if(option== '9'){
					cout<<"Enter the new sign information(note, this will not effect the exit directions): ";
					newDescription[0]='\0';
					cin>>newDescription;
					Sign.setName(newDescription);
					system("cls");
				}
				cout << "You are still the editing portion of this program. " << endl << endl;
				cout << "In this mode, you can edit the characteristics of the rooms supplied in the text file " << endl
					<< " Keep in mind, this may alter the playing experience and flow of the program." << endl << endl;
				cout<<"Enter the number of the option you would like to edit (Enter x if you are finished) " << endl;
				cout<<"1. Room Name "<<endl<<"2. Room Description "<<endl<<"3. Treasure Name"<<endl<<"4. Treasure Description" << endl
					<<"5. Treasure Value" << endl << "6. Monster Name" << endl << "7. Monster Description"<<endl<<"8. Monster Health" << endl
					<<"9. Sign information" << endl << "> ";
				cin>>option;
				system("cls");
			}
		}
#pragma endregion editMode

		printAll(Room, Treasurejus,Monster);
		
		/* Print Room's treasure */
		int Kaboom(0);
		Kaboom = 0;
		bool ImTHOR(false);
		while(!ImTHOR)
		{
			if(*(tlist.at(DaRealRoomIndex)+Kaboom)==Bogus) {
				ImTHOR = true;
				break;
			}
			else
				(tlist.at(DaRealRoomIndex)+Kaboom)->output(cout);
			Kaboom++;
		}
		/* End of print room's treasure */

		pHealth = Player.getHealth();
		mHealth = Monster.getHealth();
		pDamage = pHealth/5;
		mDamage = mHealth/5;

		cout << endl << " You enter cautiously. Are you going to sneak over to the treasure? [Y/N]" << endl << " >";
		cin >> choice;

#pragma region BattleMode
		/* Start of Enormous If condition -> Fight Mode implementation */
		if(choice=='y')
		{
			if(victory==-1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red text
				cout << " You have been spotted!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // Our chosen normal text format
				cout << " What would you like to do?\nType:\n\tA to attack\n\tR to retreat\n\tX to quit" << endl << ">";

#pragma region battle
				/* Start of while condition */
				while(victory==-1 &&lose==-1)
				{
					cin >> decision;
					decision = tolower(decision);
					system("cls");

					while(decision=='a' &&victory==-1)
					{
						srand(time(NULL));
						random=rand() %5;
						/* Battle Mode Outcomes */
						if (random > 3)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							cout<< " You swing violently but miss "<<endl;
							cout<<"You have been hit for "<< mDamage <<" damage" << endl;
							pHealth=pHealth-mDamage;
							
							cout << "\n\n Your Opponent's Health Points (HP): " << mHealth << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							cout << " Your Health Points (HP): " << pHealth << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout<<" What would you like to do?\n\nType:\n\tA to attack\n\tR to retreat\n\tX to quit"<<endl<<">";
							cin>> decision;
							decision = tolower(decision);
							system("cls");
						}

						if (random <= 3)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Aqua
							cout << "You strike the enemy dealing "<< pDamage << " damage"<<endl;
							mHealth=mHealth-pDamage;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
						if(mHealth <=0)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
							cout << " You have struck down the enemy. " << endl;
							pHealth= pHealth+(mDamage*2);
							victory=1;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
						srand(time(NULL));
						random=rand() %5;

						if(mHealth>0 && random<=3)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							cout << "You have been hit for " << mDamage << " damage" << endl;
							pHealth = pHealth-mDamage;

							cout << "\n\n Your Opponent's Health Points (HP): " << mHealth << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							cout << " Your Health Points (HP): " << pHealth << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << " What would you like to do?\n\nType:\n\tA to attack\n\tR to retreat\n\tX to quit" << endl << ">";
							cin >> decision;
							decision = tolower(decision);
							system("cls");
						}
						if(mHealth>0 && random >3)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
							cout << " The enemy has missed you!" << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
						/* End of Battle Mode Outcomes */
						if(pHealth <= 0)
						{
							/* Player death */
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
							cout<<" \t\tA wild Houghton appears!\n\n"<<endl;
							if(nMusicToggle==1)
								m_defeat();
							return 0;
						}
					}
					if(decision=='r')
					{
						/* Retreat. . . */
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << "Are you too afraid to pick up the treasure?" << endl;
						cout << " You leave the treasure where it lay" << endl;
						victory=1;
						lose=1;
					}
					/* Not sure but the 1.4.1-2 might not ever perform these checks correctly... */
					if(decision=='x')
					{
						/* Exit the game. . . */
						return 0;
					}
					if(victory==-1 &&lose ==-1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
						cout << "Please re enter a valid command" << endl << ">";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cin>>decision;
						system("cls");
					}
				}
				/* End of while condition ... Battle Mode */
#pragma endregion battle

#pragma region aftB_items
				/* Battle Mode Aftermath - Inventory Item Handling */
				if( (victory == 1) && (Player.getInvsize() == 5) && (lose == -1) ) {

					/* Player may exchange a current item or walk away... */

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
					cout << "\nYou have too many items!\nWould you like to drop an item?" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

					/* PlayerHasMaxInventory ItemRemoval */

					cin >> choice;
					choice = tolower(choice);

					if(choice=='y')
					{
						nItemNum = 0;
						/* Print Inventory, Remove the item the player wishes to remove */
						//cout << "Your inventory contains " << treasureList.size() << " item(s)" << endl;
						//cout << "Items in your Inventory: " << endl;
						//for(vector<string>::iterator it=treasureList.begin();it!=treasureList.end();it++)
						//{
						//	cout<< '\t' << nItemNum <<". "<<*it<<endl;
						//	nItemNum++;
						//}
						Player.printInventory();

						cout << "\nEnter the number of the item you would like to drop: ";
						cin >> drop;

						/* BOUNDS CHECKING */
						if(drop > Player.getInvsize()-1 || drop < 0) {
							drop = 0;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
							cout << "\n\tInvalid Response\n\tRemoving Item 0. . .\n" << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}

						/* ITEM REMOVAL */
						//if(drop<treasureList.size()-1) {
						//	treasureList.at(drop)=treasureList.at(drop+1);
						//	for(unsigned int nCntr=(drop+1);nCntr<treasureList.size()-1;nCntr++) {
						//		treasureList.at(nCntr)=treasureList.at(nCntr+1);
						//	}
						//}
						//if(drop<treasureList.size())
						if(drop < Player.getInvsize()) //delete???
						{
							//treasureList.pop_back(); // string vector
							Treasure dummy;
							dummy.setName((Player.getInvItem(drop)).Aname());
							dummy.setDescription((Player.getInvItem(drop)).Adescription());
							dummy.setValue((Player.getInvItem(drop)).getValue());
							if(((tlist.at(DaRealRoomIndex))[4])!=Bogus)   //error fixin for ye !
							{
								/* The room is full... */
								cout << "\nYou can't find a safe place to drop the item from Thieves!" << endl;
							}
							else{
								Player.removeItem(drop);
								for(int Snoop(0); Snoop<5; Snoop++) {
									if((tlist.at(DaRealRoomIndex))[Snoop]==Bogus)//err
									{
										(tlist.at(DaRealRoomIndex))[Snoop].setName(dummy.Aname());//err
										(tlist.at(DaRealRoomIndex))[Snoop].setDescription(dummy.Adescription()); //err
										(tlist.at(DaRealRoomIndex))[Snoop].setValue(dummy.getValue());//err
										break;
									}
								}
							}
						}
						else {  // User will get here if drop is out of bounds
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
							cout << "\n\nThere isn't an item here, to remove !\n" << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}


						nItemNum=0;
						/* Prints Player's inventory with item numbers */
						//cout << "\nYour inventory contains " << treasureList.size() << " item(s)" << endl;
						//cout << "You are carrying: " << endl;
						//for(vector<string>::iterator it=treasureList.begin();it!=treasureList.end();it++)
						//{
						//	cout << '\t' << nItemNum << ". " << *it << endl;
						//	nItemNum++;
						//}
						Player.printInventory();
					}
					else
					{
						system("cls");
						cout<<" You decide not to drop an item "<<endl;
					}
				}
				/* End of PlayerHasMaxFullInventory ItemRemoval */

				if(victory==1 && Player.getInvsize() < 5 && lose==-1)
				{
					/* Item Inventory Logic */
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
					cout << " You take the treasure and continue on." << endl;

					if(nMusicToggle==1)
						m_victory();

					unsigned int NutriGrain(5);
					for(unsigned int baalz(0);baalz<5;baalz++)
					{
						if((tlist.at(DaRealRoomIndex))[baalz]==Bogus) {//err
							NutriGrain=baalz;
							break;
						}
					}
					if((Player.getInvsize()+NutriGrain)-1<5)
					{
						for(unsigned int extenze(0);extenze<NutriGrain;extenze++)
							Player.addItem(*(tlist.at(DaRealRoomIndex)+extenze)); //err?
						for(unsigned int extenze(1);extenze<NutriGrain;extenze++) {	
							(tlist.at(DaRealRoomIndex))[extenze].setName(Bogus.Aname());
							(tlist.at(DaRealRoomIndex))[extenze].setDescription(Bogus.Adescription());
							(tlist.at(DaRealRoomIndex))[extenze].setValue(Bogus.getValue());
						}
						NutriGrain = 0;
					}
					else
					{
						cout << "\n You don't have enough space for these items!" << endl;
					}
					//Treasurejus.pickUpItem(title); // Currently, this does jack shit
					//strcpy(name,title); 
					//treasureList.push_back(name);
					

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //game default color
					cout << "Would you like to view your inventory? (y/n)" << endl;
					cin >> choice;
					choice = tolower(choice);


					int nItemNumber(0);

					if(choice=='y') {
						//cout << "Your inventory contains " << treasureList.size() << " item(s)" << endl;
						//cout << "Items in your Inventory: " << endl;
						//for(vector<string>::iterator it=treasureList.begin();it!=treasureList.end();it++)
						//{
						//	cout<< '\t' << nItemNumber <<". "<<*it<<endl;
						//	nItemNumber++;
						//}
						Player.printInventory();
					}

					/* May we actually drop an item? */
					if((!Player.isInventoryEmpty()) || (NutriGrain>4))
					{
						/* Prompt player if they would like to drop an item */
						cout << "Would you like to drop an item (y/n)? :";
						cin >> choice;
						choice = tolower(choice);

						if(choice=='y')
						{
							/* Remove the item the player wishes to remove */
							if(Player.getInvsize()==1)
							{
								Treasure mydummy;
								mydummy.setName((Player.getInvItem(0)).Aname());
								mydummy.setDescription((Player.getInvItem(0)).Adescription());
								mydummy.setValue((Player.getInvItem(0)).getValue());
								(tlist.at(DaRealRoomIndex))[NutriGrain].setName(mydummy.Aname());//err
								(tlist.at(DaRealRoomIndex))[NutriGrain].setDescription(mydummy.Adescription());//err
								(tlist.at(DaRealRoomIndex))[NutriGrain].setValue(mydummy.getValue());//err
								Player.removeItem(0);
							}
							else if(Player.getInvsize()>1) {
								cout << "\nEnter the number of the item you would like to drop: ";
								cin >> drop;

								/* Bounds Checking */
								if(drop > Player.getInvsize()-1 || drop < 0) {
									drop = 0;
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
									cout << "\n\tInvalid Response\n\tRemoving Item 0. . .\n" << endl;
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								}

								Treasure craigsdummy;
								craigsdummy.setName((Player.getInvItem(drop)).Aname());
								craigsdummy.setDescription((Player.getInvItem(drop)).Adescription());
								craigsdummy.setValue((Player.getInvItem(drop)).getValue());
								(tlist.at(DaRealRoomIndex))[NutriGrain].setName(craigsdummy.Aname());
								(tlist.at(DaRealRoomIndex))[NutriGrain].setDescription(craigsdummy.Adescription());
								(tlist.at(DaRealRoomIndex))[NutriGrain].setValue(craigsdummy.getValue());

								Player.removeItem(drop);
							} else { // user shouldnt be here...
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
								cout << "\n\nThere isn't an item here, to remove !\n" << endl;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							}										


							nItemNumber=0;
							/* Prints Player's inventory with item numbers */
							//cout << "\nYour inventory contains " << treasureList.size() << " item(s)" << endl;
							//cout << "You are carrying: " << endl;
							//for(vector<string>::iterator it=treasureList.begin();it!=treasureList.end();it++)
							//{
							//	cout << '\t' << nItemNumber << ". " << *it << endl;
							//	nItemNumber++;
							//}
							Player.printInventory();
						}
						else
						{
							system("cls");
							cout<<" You decide not to drop an item "<<endl;
						}
					}
				}
				/* End of Battle Aftermath */
#pragma endregion aftB_items
			}
		}
#pragma endregion BattleMode
		/* ^^ End of Enormous if condition  */

		victory=-1;
		lose=-1;
		Player.setHealth(pHealth+mDamage*3);


#pragma region thief
		Thief.setLocation(thiefLocation(numRooms));
		thiefIndex=Thief.getLocation();

		if(thiefIndex==roomIndex && Player.getInvsize()!=0)
		{
			int lamer = (Player.getInvsize()-1);
			Player.removeItem(lamer);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // red
			cout<<" A thief has stolen some of your treasure!"<<endl;

			if(nMusicToggle==1)
				m_defeat();

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Default Colors
			cout<<" Would you like to view your inventory? (y/n)  "<<endl<<"> ";
			cin>> choice;
			choice = tolower(choice);
			system("cls");

			if (choice=='y')
			{
				Player.printInventory();
				/*cout<<"\n Your inventory contains: "<<endl;
				for (vector<string>::iterator i = treasureList.begin(); i != treasureList.end(); ++i)
				{
					cout << '\t' << *i << endl;
				}  */

				cout << endl;
			}
			else if(choice=='n')
			{
				cout << " You scream obscenities." << endl << " No one hears you" << endl;
			}
			else if (choice=='x')
				return 0;
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
				cout << " Please re-enter command" << endl << "> ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cin >> choice;
				choice = tolower(choice);
			}
		}
#pragma endregion thief


		bool gameOver(false);
		//gameOver=gameEnd(roomIndex); //this messes up the ability to play modified games
		if(DaRealRoomIndex==(YouDuntMeanShtToMe-1))
			gameOver = true;
		if(gameOver)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
			Player.printScore();
			cin.get();
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if(nMusicToggle==1)
				c_mus();
			else
				c_nomus();
			return 0;
		}

		futureRoom(Room, Treasurejus, roomIndex, numRooms, Monster,Sign,nMusicToggle, Agents, Player, YouDuntMeanShtToMe);
	}
	/* end of while control */
#pragma endregion game_loop
	in1.close(); //closes the input file
}
/* Game Music Implementation */
void m_title()
{
	Beep(196.00,125); // G3
	Beep(246.94,250); // B3
	Beep(293.66,250); // D4
	Beep(349.23,500); // F4
	Beep(392.00,250); // G4
	Beep(392.00,500); // G4
	Beep(392.00,250); // G4
	Beep(392.00,250); // G4
	Beep(392.00,500); // G4
	Beep(392.00,250); // G4
	Beep(392.00,500); // G4
	Beep(349.23,250); // F4
	Beep(349.23,250); // F4
	Beep(349.23,250); // F4
	Beep(349.23,250); // F4
	Beep(349.23,250); // F4
	Beep(369.99,250); // F#/Gb4
	Beep(392.00,250); // G4
	Beep(493.88,250); // B4
	Beep(587.33,250); // D5
	Beep(523.25,500); // C5
	Beep(698.46,750); // F5
	Beep(698.46,250); // F5
	Beep(659.26,250); // E5
	Beep(622.25,250); // D#/Eb5
	Beep(587.33,250); // D5
	Beep(349.23,500); // F4
	Beep(329.63,250); // E4
	Beep(622.25,250); // D#/Eb5
	Beep(293.66,500); // D4
	Beep(261.63,250); // C4
	Beep(246.94,250); // B3
	Beep(261.63,750); // C4
	Beep(392.00,250); // G4
	Beep(493.88,250); // B4
	Beep(587.33,750); // D5
	Beep(523.25,250); // C5
	Beep(493.88,250); // B4
	Beep(523.25,250); // C5
	Beep(587.33,500); // D5
	Beep(349.23,250); // F4
	Beep(329.63,250); // E4
	Beep(261.63,250); // C4
	Beep(293.66,1000); // D4
	Beep(246.94,250); // B3
	Beep(261.63,250); // C4
	Beep(293.66,750); // D4
	Beep(392.00,250); // G4
	Beep(493.88,250); // B4
	Beep(587.33,250); // D5
	Beep(523.25,500); // C5
	Beep(698.46,250); // F5
	Beep(659.26,250); // E5
	Beep(622.25,250); // D#/Eb5
	Beep(587.33,250); // D5
	Beep(587.33,250); // D5
	Beep(349.23,500); // F4
	Beep(329.63,250); // E4
	Beep(311.13,250); // D#/Eb4
	Beep(293.66,250); // D4
	Beep(261.63,250); // C4
	Beep(246.94,250); // B3
	Beep(261.63,1000); // C4
	Beep(392.00,250); // G4
	Beep(493.88,250); // B4
	Beep(587.33,250); // D5
	Beep(523.25,500); // C5
	Beep(698.46,250); // F5
	Beep(659.26,250); // E5
	Beep(698.46,250); // F5
	Beep(783.99,250); // G5
	Beep(932.33,250); // A#/Bb5
	Beep(783.99,750); // G5
	Beep(880.00,250); // A5
	Beep(932.33,250); // A#/Bb5
	Beep(698.46,250); // F5
	Beep(698.46,500); // F5
	Beep(932.33,250); // A#/Bb5
	Beep(987.77,250); // B5
	Beep(1046.50,250); // C6
	Beep(783.99,250); // G5
	Beep(783.99,750); // G5
	Beep(1046.50,250); // C6
	Beep(1108.73,250); // C#/Db6
	Beep(1174.66,250); // D6

	
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
		
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
		
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3
	Beep(146.83,125); // D3

	Beep(1046.50,250); // C6
	Beep(1046.50,250); // C6
	Beep(1108.73,250); // C#/Db6
	Beep(1174.66,250); // D6

	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//	
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//	
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3
	//Beep(146.83,125); // D3

	//Beep(1046.50,250); // C6
	//Beep(1046.50,250); // C6
	//Beep(987.77,750); // B5

	//Beep(392.00,250); // G4
	//Beep(493.88,250); // B4
	//Beep(587.33,250); // D5
}
void m_victory()
{
	Beep(98.00,250); // G2
	Beep(130.81,250); // C3
	Beep(164.81,250); // E3
	Beep(196.00,250); // G3
	Beep(261.63,250); // C4
	Beep(329.63,250); // E4
	Beep(392.00,250); // G4
	Beep(329.63,500); // E4

	Beep(103.83,125); // G#/Ab2
	Beep(130.81,125); // C3
	Beep(155.56,125); // D#/Eb3
	Beep(207.65,125); // G#/Ab3
	Beep(261.63,125); // C4
	Beep(311.13,125); // D#/Eb4
	Beep(415.30,125); // G#/Ab4
	Beep(311.13,500); // D#/Eb4

	Beep(116.54,125); // A#/Bb2
	Beep(146.83,125); // D3
	Beep(174.61,125); // F3
	Beep(233.08,125); // A#/Bb3
	Beep(293.66,125); // D4
	Beep(349.23,125); // F4
	Beep(466.16,500); // A#/Bb4
	Beep(466.16,125); // A#/Bb4
	Beep(466.16,125); // A#/Bb4
	Beep(466.16,125); // A#/Bb4
	Beep(523.25,250); // C5
}
void m_defeat()
{
	Beep(220.00,750); // A3
	Beep(293.66,1000); // D4
	Beep(220.00,750); // A3
	Beep(329.63,1000); // e4
	Beep(220.00,250); // A3
	Beep(349.23,1000); // F4
	Beep(392.00,250); // G4
	Beep(440.00,250); // A4
	Beep(392.00,250); // G4
	Beep(293.66,1000); // D4
	Beep(293.66,250); // D4
	Beep(329.63,250); // e4
	Beep(349.23,1000); // F4
	Beep(392.00,500); // G4
	Beep(349.23,500); // F4
	Beep(329.63,500); // E4
	Beep(349.23,500); // F4
	Beep(329.63,500); // E4
	Beep(261.63,500); // C4
	Beep(293.66,250); // D4
}
void m_credits_rone()
{
	Beep(123.47,250); // B2
	Beep(185.00,250); // F#/Gb3
	Beep(277.18,250); // C#/Db4
	Beep(185.00,250); // F#/Gb3
	Beep(277.18,250); // C#/Db4
	Beep(246.94,250); // B3
	Beep(98.00,250); // G2
	Beep(146.83,250); // D3
	Beep(220.00,250); // A3
	Beep(146.83,250); // D3
	Beep(220.00,250); // A3
	Beep(196.00,250); // G3
}
void m_credits_roneb()
{
	Beep(123.47,250); // B2
	Beep(185.00,250); // F#/Gb3
	Beep(277.18,250); // C#/Db4
	Beep(185.00,250); // F#/Gb3
	Beep(277.18,250); // C#/Db4
	Beep(293.66,250); // D4
	Beep(98.00,250); // G2
	Beep(146.83,250); // D3
	Beep(220.00,250); // A3
	Beep(146.83,250); // D3
	Beep(220.00,250); // A3
	Beep(246.94,250); // B3
}
void m_credits_ronec()
{
	/* Post First Riff - 2 */
	Beep(146.83,250); // D3
	Beep(220.00,250); // A3
	Beep(329.63,250); // E4
	Beep(220.00,250); // A3
	Beep(329.63,250); // E4
	Beep(369.99,250); // F#/Gb4
	Beep(164.81,250); // E3
	Beep(246.94,250); // B3
	Beep(369.99,250); // F#/Gb4
	Beep(246.94,250); // B3
	Beep(369.99,250); // F#/Gb4
	Beep(392.00,250); // G4
}
void m_credits_roneh()
{
	/* First Riff - Highest Octave */
	Beep(246.94,250); // B3
	Beep(369.99,250); // F#/Gb4
	Beep(554.37,250); // C#/Db5
	Beep(369.99,250); // F#/Gb4
	Beep(554.37,250); // C#/Db5
	Beep(493.88,250); // B4
	Beep(196.00,250); // G3
	Beep(293.66,250); // D4
	Beep(440.00,250); // A4
	Beep(293.66,250); // D4
	Beep(440.00,250); // A4
	Beep(392.00,250); // G4
}
void m_credits_rtwo()
{
	/* Second Riff */
	Beep(73.42,250); // D2
	Beep(110.00,250); // A2
	Beep(164.81,250); // E3
	Beep(110.00,250); // A2
	Beep(164.81,250); // E3
	//Beep(146.83,250); // D3
	Beep(185.00,250); // F#/Gb3
}
void m_credits_rtwoh()
{
	/* Second Riff - Highest Octave */
	Beep(146.83,250); // D3
	Beep(220.00,250); // A3
	Beep(329.63,250); // E4
	Beep(220.00,250); // A3
	Beep(329.63,250); // E4
	Beep(293.66,250); // D4
}
void m_credits_rthree()
{
	/* Third Riff */
	Beep(110.00,250); // A2
	Beep(164.81,250); // E3
	Beep(246.94,250); // B3
	Beep(164.81,250); // E3
	Beep(246.94,250); // B3
	Beep(220.00,250); // A3
	Beep(277.18,250); // C#4
}
void m_credits_rthreeh()
{
	/* Third Riff - Highest Octave */
	Beep(220.00,250); // A3
	Beep(329.63,250); // E4
	Beep(493.88,250); // B4
	Beep(329.63,250); // E4
	Beep(493.88,250); // B4
	Beep(440.00,250); // A4
}
void m_credits_rthreehb()
{
	/* Third Riff - Highest Octave - 2 */
	Beep(220.00,250); // A3
	Beep(329.63,250); // E4
	Beep(493.88,250); // B4
	Beep(329.63,250); // E4
	Beep(233.08,250); // A#/Bb3
	Beep(329.63,250); // E4
	Beep(493.88,250); // B4
	Beep(329.63,250); // E4
}
void c_mus()
{
	cout << "\n\n\n\n\n\n\t\t\tProducers" << endl;
	cout << "\t\t\t     Justin McKennon" << endl;
	cout << "\t\t\t     A.J. Houghton" << endl;
	m_credits_rone();
	m_credits_rtwo();
	system("cls");

	cout << "\n\n\n\n\n\t\t\tLevel Designers" << endl;  //new
	cout << "\t\t\t     Justin McKennon" << endl;
	cout << "\t\t\t     A.J. Houghton" << endl;
	cout << "\t\t\t     Barry Gaffey" << endl;
	m_credits_rthree();
	system("cls");

	cout << "\n\n\n\n\n\n\n\t\t\t\tArtists" << endl; //new
	cout << "\t\t\t     Craig Nathan" << endl;
	cout << "\t\t\t      Barry Gaffey" << endl;
	m_credits_roneb();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tTesters" << endl;
	cout << "\t\t\t     A.J. Houghton" << endl;
	cout << "\t\t\t      Josh LaClair" << endl;
	m_credits_ronec();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\tMusic Designer" << endl;
	cout << "\t\t        Barry Gaffey" << endl;
	m_credits_roneh();
	system("cls");
	
	cout << "\n\n\n\n\t\t\tSpecial Thanks to:" << endl; //new
	cout << "\n\n\t\t\t\t Professor Geiger" << endl;
	cout << "\n\t\t\t and Ben Viall." << endl;
	cout << "\n\t\t Nintendo Ltd. and Square for the Music" << endl;
	cout << "\n\n\t\t\t and anyone that played this game" << endl;
	m_credits_rtwoh();
	m_credits_rthreeh();
	system("cls");
	
	cout << "\n\n\n\n\n\n\t\t\t\tGame Documentation" << endl;
	cout << "\t\t\t\t Justin McKennon" << endl;
	cout << "\t\t\t\t Craig Nathan" << endl;
	cout << "\t\t\t\t Josh LaClair" << endl;
	m_credits_roneh();
	m_credits_rtwoh();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tGame Programmer" << endl;
	cout << "\t\t\t\tJustin McKennon" << endl;
	m_credits_rthreehb();
	m_credits_roneh();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tSenior Game Programmers" << endl;
	cout << "\t\t\t\t     Barry Gaffey" << endl;
	cout << "\t\t\t\t     Craig Nathan" << endl;
	m_credits_rtwoh();
	m_credits_rthreehb();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tGame Designers" << endl;
	cout << "\t\t\t       Justin McKennon" << endl;
	cout << "\t\t\t       A.J. Houghton" << endl;
	cout << "\t\t\t        Josh LaClair" << endl;
	m_credits_roneb();
	m_credits_rtwo();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tDirectors of Development" << endl;
	cout << "\t\t\t\t     Justin McKennon" << endl;
	cout << "\t\t\t\t      Barry Gaffey" << endl;
	m_credits_rthree();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tSales Manager" << endl; //new
	cout << "\n\n\t\t\t\t     A.J. Houghton" << endl;
	m_credits_roneb();
	system("cls");
		
	cout << "\n\n\n\n\n\n\t\t\t\tTeam Morale Support" << endl;
	cout << "\t\t\t\t     Craig Nathan" << endl;
	m_credits_ronec();
	system("cls");
}
void c_nomus()
{
	cin.get(); // For some reason the first credit scene is cleared after inventory prompts. This fixes that issue.

	cout << "\n\n\n\n\n\n\t\t\tProducers" << endl;
	cout << "\t\t\t     Justin McKennon" << endl;
	cout << "\t\t\t     A.J. Houghton" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\t\t\tLevel Designers" << endl;  //new
	cout << "\t\t\t     Justin McKennon" << endl;
	cout << "\t\t\t     A.J. Houghton" << endl;
	cout << "\t\t\t     Barry Gaffey" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\n\t\t\t\tArtists" << endl; //new
	cout << "\t\t\t     Craig Nathan" << endl;
	cout << "\t\t\t      Barry Gaffey" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tTesters" << endl;
	cout << "\t\t\t     A.J. Houghton" << endl;
	cout << "\t\t\t      Josh LaClair" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\tMusic Designer" << endl;
	cout << "\t\t        Barry Gaffey" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\t\t\tSpecial Thanks to:" << endl; //new
	cout << "\n\n\t\t\t\t Professor Geiger" << endl;
	cout << "\n\t\t\t and Ben Viall." << endl;
	cout << "\n\t\t Nintendo Ltd. and Square for the Music" << endl;
	cout << "\n\n\t\t\t and anyone that played this game" << endl;
	cin.get();
	system("cls");
	
	cout << "\n\n\n\n\n\n\t\t\t\tGame Documentation" << endl;
	cout << "\t\t\t\t Justin McKennon" << endl;
	cout << "\t\t\t\t Craig Nathan" << endl;
	cout << "\t\t\t\t Josh LaClair" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tGame Programmer" << endl;
	cout << "\t\t\t\tJustin McKennon" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tSenior Game Programmers" << endl;
	cout << "\t\t\t\t     Barry Gaffey" << endl;
	cout << "\t\t\t\t     Craig Nathan" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tGame Designers" << endl;
	cout << "\t\t\t       Justin McKennon" << endl;
	cout << "\t\t\t       A.J. Houghton" << endl;
	cout << "\t\t\t        Josh LaClair" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tDirectors of Development" << endl;
	cout << "\t\t\t\t     Justin McKennon" << endl;
	cout << "\t\t\t\t      Barry Gaffey" << endl;
	cin.get();
	system("cls");

	cout << "\n\n\n\n\n\n\t\t\t\tSales Manager" << endl; //new
	cout << "\n\n\t\t\t\t     A.J. Houghton" << endl;
	cin.get();
	system("cls");
		
	cout << "\n\n\n\n\n\n\t\t\t\tTeam Morale Support" << endl;
	cout << "\t\t\t\t     Craig Nathan" << endl;
	cin.get();
	system("cls");
}
#pragma warning( default : 4244)
#pragma warning( default : 4996)