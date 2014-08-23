/*	This program tests the algorithm removeAfterNeg.
		Written by: Craig Nathan
		Date:		8/27/09
*/
#include <stdio.h>
#include <stdlib.h>
#include "linkListADT.h"

// Product in grocery store
typedef struct
{
	int isle;
	char food[41];
} PRODUCT;

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
int compareIsle (void* prod1, void* prod2)
{
//Local Definitions
	int result, isle1, isle2;

//Statements
	isle1 = ((PRODUCT*)prod1)->isle;
	isle2 = ((PRODUCT*)prod2)->isle;

	if (isle1 < isle2)
		result = -1;
	else if (isle1 > isle2)
		result = +1;
	else
		result = 0;
	return result;
}

/* ============================== buildList ===============================
	Reads a text file and loads the list. File must end with a newline.
		Pre    file exists in format: 
						isle \t 'food'
		Post   list contains data
			   -or- program aborted if problems
   ========================================================================
*/
LIST* buildList (void)
{
//Local Definitions
	FILE* fp;
	LIST* list;

	int isleIn, addResult;

	PRODUCT* prod;

//Statements
	list = createList(compareIsle);
	if(!list)
		printf("\aCannot create list\n"), exit(100);
	fp = fopen("food.txt", "r");
	if(!fp)
		printf("\aError opening input file\n"), exit(110);
	while (fscanf(fp, " %d", &isleIn) == 1)
	{
		prod = (PRODUCT*) malloc(sizeof(PRODUCT));
		if (!(prod))
			printf("\aOut of Memory in build list\n"), exit(100);
		prod->isle = isleIn;

		//skip tabs and quote
		while((fgetc(fp)) != '\t')
			;
		while((fgetc(fp)) != '"')
			;
		fscanf(fp, " %40[^\"], %*c", prod->food);

		//insert into list
		addResult = addNode(list, prod);
		if (addResult != 0)
			if (addResult == -1)
				printf("Memory overflow adding product\a\n"), exit(120);
			else
				printf("Duplicate isle %hd not added\n\a", prod->isle);
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
	PRODUCT* prod;

//Statements

	//Get first node
	if (listCount (list) == 0)
	{
		printf("Sorry, nothing in the list\n\a");
	}
	else 
	{
		printf("\nFood in isles:\n");
		traverse (list, 0, (void**)&prod);
		do
		{
			printf("%02d %s\n", prod->isle, prod->food);
		}
		while (traverse (list, 1, (void**)&prod));
	}
	printf("\n");
}

/* ========================== removeAfterNeg ==============================
	Traverses a list implemented using a linked list and deletes the node 
	following a node with a negative key.
		Pre    list is pointer to initialized list
		Post   data have been deleted
   ========================================================================
*/
int removeAfterNeg (LIST* list)
{
//Local Definitions
	int erase;
	PRODUCT* prevProd;
	PRODUCT* prod;

	if (list->count == 0)
	{
		printf("Sorry, nothing in the list\n\a");
		return 0;
	}
	else
	{
		traverse (list, 0, (void**)&prod);
		prevProd = prod;

		while (traverse (list, 1, (void**)&prod))
		{
			if (prevProd->isle == -1)
			{
				list->pos = list->pos->link;
				erase = removeNode(list, (void*)prod, (void**)&prod);
				if (erase == 1)
					printf("Node deleted:\n%d %s\n\n", prod->isle, prod->food);
			}
			prevProd = prod;
		}
		return 1;
	}
}

int main(void)
{
//Local Definitions
	LIST* list;

//Statements
	list = buildList();
	printList(list);
	if (removeAfterNeg(list) == 1)
		printList(list);

	return 0;
}