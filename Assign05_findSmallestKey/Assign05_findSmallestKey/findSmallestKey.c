/*	This program tests the algorithm removeAfterNeg.
		Written by: Craig Nathan
		Date:		8/25/09
*/
#include <stdio.h>
#include <stdlib.h>
#include "linkListADT.h"

// Car in Parking Garage
typedef struct
{
	int key;
	char lot  [41];
	char spot [41];
	char make [41];
	char model[41];
} CAR;

/* ============================== compareKey ==============================
	Compares the keys of two nodes.
		Pre    pKey1 is a pointer to the first structure
			   pKey2 is a pointer to the second structure
		Post   two keys compared and result returned
		Return -1 if pKey1 less
				0 if equal
			   +1 if greater
   ========================================================================
*/
int compareKey (void* pCar1, void* pCar2)
{
//Local Definitions
	int result, key1, key2;

//Statements
	key1 = ((CAR*)pCar1)->key;
	key2 = ((CAR*)pCar2)->key;

	if (key1 < key2)
		result = -1;
	else if (key1 > key2)
		result = +1;
	else
		result = 0;
	return result;
}

/* ============================== buildList ===============================
	Reads a text file and loads the list.
		Pre    file exists in format: 
						key \t 'lot' \t 'spot' \t yyyy \t 'make' \t 'model'
		Post   list contains data
			   -or- program aborted if problems
   ========================================================================
*/
LIST* buildList (void)
{
//Local Definitions
	FILE* fp;
	LIST* list;

	int keyIn, addResult;

	CAR* pCar;

//Statements
	list = createList(compareKey);
	if(!list)
		printf("\aCannot create list\n"), exit(100);
	fp = fopen("cars.txt", "r");
	if(!fp)
		printf("\aError opening input file\n"), exit(110);
	while (fscanf(fp, " %d", &keyIn) == 1)
	{
		pCar = (CAR*) malloc(sizeof(CAR));
		if (!(pCar))
			printf("\aOut of Memory in build list\n"), exit(100);
		pCar->key = keyIn;

		//skip tabs and quote
		while((fgetc(fp)) != '\t')
			;
		while((fgetc(fp)) != '"')
			;
		fscanf(fp, " %40[^\"], %*c", pCar->lot);

		while((fgetc(fp)) != '\t')
			;
		while((fgetc(fp)) != '"')
			;
		fscanf(fp, " %40[^\"], %*c", pCar->spot);

		while((fgetc(fp)) != '\t')
			;
		while((fgetc(fp)) != '"')
			;
		fscanf(fp, " %40[^\"], %*c", pCar->make);

		while((fgetc(fp)) != '\t')
			;
		while((fgetc(fp)) != '"')
			;
		fscanf(fp, " %40[^\"], %*c", pCar->model);

		//insert into list
		addResult = addNode(list, pCar);
		if (addResult != 0)
			if (addResult == -1)
				printf("Memory overflow adding movie\a\n"), exit(120);
			else
				printf("Duplicat key %hd not added\n\a", pCar->key);
		while (fgetc(fp) != '\n')
			;
	}
	return list;
}

/* ============================== printList ===============================
	Prints the entire list.
		Pre    list has been created
		Post   list printed
   ========================================================================
*/
void printList (LIST* list)
{
//Local Definitions
	CAR* pCar;

//Statements

	//Get first node
	if (listCount (list) == 0)
	{
		printf("Sorry, nothing in the list\n\a");
	}
	else 
	{
		printf("\nCars currently parked in garage:\n");
		traverse (list, 0, (void**)&pCar);
		do
		{
			printf("%04d %s %s %s %s\n", pCar->key, pCar->lot, pCar->spot, pCar->make, pCar->model);
		}
		while (traverse (list, 1, (void**)&pCar));
	}
	printf("\n");
}

/* ========================== findSmallestKey =============================
	Traverses a list implemented using a linked list and returns the data
	in the node with the smallest key value.
		Pre    list is pointer to initialized list
			   carOut is pointer to a car
		Post   carOut contains data, return 1
			   -or- if list is empty, return 0
   ========================================================================
*/
int findSmallestKey (LIST* list, CAR* carOut)
{
//Local Definitions
	CAR* pCar1;
	CAR* pCar2;

//Statements
	if (listCount (list) == 0)
	{
		printf("Sorry, nothing in the list\n\a");
		return 0;
	}
	else 
	{
		pCar1 = list->head->link->dataPtr;
		pCar2 = list->head->dataPtr;

		traverse (list, 0, (void**)&pCar2);

		if (list->compare(pCar1, pCar2) == 1) 
			carOut = pCar2;
		else if (list->compare(pCar1, pCar2) == -1)
			carOut = pCar1;	

		while (traverse (list, 1, (void**)&pCar1))
		{
			if (list->compare(pCar1, carOut) == -1)
				carOut = pCar1;	
		}

		printf("Car with smallest key:\n%04d %s %s %s %s\n\n", carOut->key, carOut->lot, carOut->spot, carOut->make, carOut->model);
		return 1;
	}
}

int main(void)
{
//Local Definitions
	LIST* list;
	CAR carOut;

//Statements
	list = buildList();
	printList(list);
	findSmallestKey(list, &carOut);

	return 0;
}