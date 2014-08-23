/*		This program adds and subtracts two polynomials. Each polynomial is represented as a list 
	with linked list implementation. The first node in the list represents the first term in the 
	polynomial, the second node represents the second term, and so forth.
		Each node contains three fields. The first field is the term’s coefficient. The second field
	is the term’s power, and the third field is a pointer to the next term. 
		To add two polynomials, the program reads the coefficients and exponents for each polynomial 
	and places them into a linked list. The input can be read from separate files or entered from 
	the keyboard with appropriate user prompts. After the polynomials have been stored, they are 
	added and the results are placed in a third linked list. 
		The polynomials are added using an operational merge process. An operational merge combines 
	the two lists while performing one or more operations – in our case, addition. To add we take one 
	term from each of the polynomials and compare the exponents. If the two exponents are equal, the
	coefficients are added to create a new coefficient. If the new coefficient is 0, the term is 
	dropped; if it is not 0, it is appended to the linked list for the resulting polynomial. If one 
	of the exponents is larger than the other, the corresponding term is immediately placed into the 
	new linked list, and the term with the smaller exponent is held to be compared with the next term 
	from the other list. If one list ends before the other, the rest of the longer list is simply 
	appended to the list for the new polynomial.
		The two input polynomials and their sum is printed by traversing the linked lists and displaying 
	them as sets of numbers.

		Written by: Craig Nathan
		Date:		8/?/09
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "polyLinkListADT.h"

// Product in grocery store
typedef struct
{
	int num;
	int power;
} TERM;

/* ============================== comparePower ==============================
	Compares the powers of two term structures.
		Pre    pTerm1 is a pointer to the first term
			   pTerm2 is a pointer to the second term
		Post   two powers compared and result returned
		Return -1 if power1 less
				0 if equal
			   +1 if greater
   ========================================================================
*/
int comparePower (void* pTerm1, void* pTerm2)
{
//Local Definitions
	int result, power1, power2;

//Statements
	power1 = ((TERM*)pTerm1)->power;
	power2 = ((TERM*)pTerm2)->power;

	if (power1 < power2)
		result = +1;
	else if (power1 > power2)
		result = -1;
	else
		result = 0;
	return result;
}

/* ============================== buildpoly ===============================
	Reads a text file and loads the list.
		Pre    nothing
		Post   returns a list that contains data
   ========================================================================
*/
LIST* getPoly (void)
{
//Local Definitions
	LIST* poly;
	TERM* term;
	int count, addResult;

//Statements
	poly = createList(comparePower);
	if(!poly)
		printf("\aCannot create list\n"), exit(100);

	count = 1;
	do
	{
		//create new term
		term = (TERM*) malloc(sizeof(TERM));
		if (!(term))
			printf("\aOut of Memory in build list\n"), exit(100);

		//get new term coefficient and power
		printf(" Term %d:\nCoefficient: ", count);
		scanf("%d", &term->num);
		printf("Power: ");
		scanf("%d", &term->power);
		printf("\n");

		//add new node for new term
		if (term->num != 0)
		{
			if (term->power >= 0)
			{
				addResult = addNode(poly, term);
				if (addResult != 0)
				{
					if (addResult == -1)
					{
						printf("Memory overflow adding product\a\n"), exit(120);
					}
				}
				count++;
			}
		}
		else
		{
			free(term);
		}
	}
	while (term->power > 0);

	return poly;
}

/* ============================ addPolys ============================
	This algorithm adds two polynomials.
		Pre    P1 is pointer to initialized list
			   P2 is pointer to initialized list
		Post   P3 contains the sum of P1 and P2
   ==================================================================
*/
LIST* addPolys(LIST* P1, LIST* P2)
{
//Local Definitions
	int addResult;
	LIST *pSample, *P3;
	TERM *sTerm, *tTerm, *sumTerm;

//Statements
	//create result polynomial
	P3 = createList(comparePower);
	if(!P3)
		printf("\aCannot create list\n"), exit(100);

	//if one list is empty
	if (listCount(P1) == 0 || listCount(P2) == 0)
	{
		if (listCount(P1) == 0)
			pSample = P2;
		else if (listCount(P2) == 0)
			pSample = P1;

		traverse (pSample, 0, (void**)&sTerm);
		do
		{
			//create space for next term in new polynomial
			sumTerm = (TERM*) malloc(sizeof(TERM));
			if (!(sumTerm))
				printf("\aOut of Memory in build list\n"), exit(100);

			//assign new term its coeffiecient and power
			sumTerm->num = sTerm->num;
			sumTerm->power = sTerm->power;

			//add new node to polynomial P3
			addResult = addNode(P3, sumTerm);
			if (addResult != 0)
				if (addResult == -1)
					printf("Memory overflow adding product\a\n"), exit(120);
		}
		while (traverse (pSample, 1, (void**)&sTerm));

		return P3;
	}

	//begin traversing through first polynomial
	traverse (P1, 0, (void**)&sTerm);
	do
	{
		//create space for next term in new polynomial
		sumTerm = (TERM*) malloc(sizeof(TERM));
		if (!(sumTerm))
			printf("\aOut of Memory in build list\n"), exit(100);

		//search second polynomial for term with matching power
		if (searchList(P2, (void*)sTerm, (void**)&tTerm) == 1)
		{
			//if found add two terms' coefficients
			sumTerm->num = sTerm->num + tTerm->num;
		}
		//if not found P3's term's coefficient is the same as pSample's
		else
		{
			sumTerm->num = sTerm->num;
		}

		//assign new term its power
		sumTerm->power = sTerm->power;

		//add new node to polynomial P3
		addResult = addNode(P3, sumTerm);
		if (addResult != 0)
			if (addResult == -1)
				printf("Memory overflow adding product\a\n"), exit(120);
	}
	while (traverse (P1, 1, (void**)&sTerm));

	//find terms from second polynomial that weren't matched and add them to new poly
	traverse (P2, 0, (void**)&tTerm);
	do
	{
		//if term not found in new poly, add it to new poly
		if (searchList(P3, (void*)tTerm, (void**)&sumTerm) == 0)
		{
			//create space for next term in new polynomial
			sumTerm = (TERM*) malloc(sizeof(TERM));
			if (!(sumTerm))
				printf("\aOut of Memory in build list\n"), exit(100);

			sumTerm->num = tTerm->num;
			sumTerm->power = tTerm->power;

			//add new node to polynomial P3
			addResult = addNode(P3, sumTerm);
			if (addResult != 0)
				if (addResult == -1)
					printf("Memory overflow adding term\a\n"), exit(120);
		}
	}
	while (traverse (P2, 1, (void**)&tTerm));

	//search new list for terms with coefficients of zero and remove them
	traverse (P3, 0, (void**)&sumTerm);
	do
	{
		if (sumTerm->num == 0)
		{
			P3->pos = P3->pos->link;
			removeNode(P3, (void*)sumTerm, (void**)&sumTerm);
		}
	}
	while (traverse (P3, 1, (void**)&sumTerm));
	return P3;
}

/* ========================= subtractPolys ==========================
	This algorithm subtracts two polynomials.
		Pre    P1 is pointer to initialized list
			   P2 is pointer to initialized list
		Post   P3 contains the difference between P1 and P2
   ==================================================================
*/
LIST* subtractPolys(LIST* P1, LIST* P2)
{
//Local Definitions
	int addResult;
	LIST *pSample, *pDiff;
	TERM *sTerm, *tTerm, *diffTerm;

//Statements
	//create result polynomial
	pDiff = createList(comparePower);
	if(!pDiff)
		printf("\aCannot create list\n"), exit(100);

	//if one list is empty
	if (listCount(P1) == 0 || listCount(P2) == 0)
	{
		if (listCount(P1) == 0)
			pSample = P2;
		else if (listCount(P2) == 0)
			pSample = P1;

		traverse (pSample, 0, (void**)&sTerm);
		do
		{
			//create space for next term in new polynomial
			diffTerm = (TERM*) malloc(sizeof(TERM));
			if (!(diffTerm))
				printf("\aOut of Memory in build list\n"), exit(100);

			//assign new term its coeffiecient and power
			diffTerm->num = sTerm->num;
			diffTerm->power = sTerm->power;

			//add new node to polynomial P3
			addResult = addNode(pDiff, diffTerm);
			if (addResult != 0)
				if (addResult == -1)
					printf("Memory overflow adding product\a\n"), exit(120);
		}
		while (traverse (pSample, 1, (void**)&sTerm));

		return pDiff;
	}

	//begin traversing through first polynomial
	traverse (P1, 0, (void**)&sTerm);
	do
	{
		//create space for next term in new polynomial
		diffTerm = (TERM*) malloc(sizeof(TERM));
		if (!(diffTerm))
			printf("\aOut of Memory in build list\n"), exit(100);

		//search second polynomial for term with matching power
		if (searchList(P2, (void*)sTerm, (void**)&tTerm) == 1)
		{
			//if found subtract two terms' coefficients
			diffTerm->num = sTerm->num - tTerm->num;
		}
		//if not found P3's term's coefficient is the same as pSample's
		else
		{
			diffTerm->num = sTerm->num;
		}

		//assign new term its power
		diffTerm->power = sTerm->power;

		//add new node to polynomial P3
		addResult = addNode(pDiff, diffTerm);
		if (addResult != 0)
			if (addResult == -1)
				printf("Memory overflow adding product\a\n"), exit(120);
	}
	while (traverse (P1, 1, (void**)&sTerm));

	//find terms from second polynomial that weren't matched, negate them, and add them to new poly
	traverse (P2, 0, (void**)&tTerm);
	do
	{
		//if term not found in new poly, add it to new poly
		if (searchList(pDiff, (void*)tTerm, (void**)&diffTerm) == 0)
		{
			//create space for next term in new polynomial
			diffTerm = (TERM*) malloc(sizeof(TERM));
			if (!(diffTerm))
				printf("\aOut of Memory in build list\n"), exit(100);

			//assign new term its negated coefficient and its power
			diffTerm->num = 0 - tTerm->num;
			diffTerm->power = tTerm->power;

			//add new node to polynomial P3
			addResult = addNode(pDiff, diffTerm);
			if (addResult != 0)
				if (addResult == -1)
					printf("Memory overflow adding term\a\n"), exit(120);
		}
	}
	while (traverse (P2, 1, (void**)&tTerm));

	//search new list for terms with coefficients of zero and remove them
	traverse (pDiff, 0, (void**)&diffTerm);
	do
	{
		if (diffTerm->num == 0)
		{
			pDiff->pos = pDiff->pos->link;
			removeNode(pDiff, (void*)diffTerm, (void**)&diffTerm);
		}
	}
	while (traverse (pDiff, 1, (void**)&diffTerm));
	return pDiff;
}

/* ============================== printPoly ===============================
	Prints the entire polynomial.
		Pre    list has been created
		Post   list printed
   ========================================================================
*/
void printPoly (LIST* poly)
{
//Local Definitions
	TERM* term;

//Statements
	if (listCount (poly) == 0)
	{
		printf("Empty\n\a");
	}
	else 
	{
		traverse (poly, 0, (void**)&term);
		do
		{
			//deal with coefficient possibilities
			if (term->num < 0)
				printf("%d",term->num);
			else if (term->num > 0)
				if (poly->pos != poly->head)
					printf("+ %d",term->num);
				else
					printf("%d", term->num);
			
			//deal with power possibilities
			if (term->power != 0)
				if (term->power == 1)
					printf("x ");
				else
					printf("x^%d ", term->power);
		}
		while (traverse (poly, 1, (void**)&term));
	}
	printf("\n");
}

/* ============================ blink ===============================
	This function blinks an error message on the screen.
		Pre    nothing
		Post   message blinks on screen
   ==================================================================
*/
void blink(void)
{
//Local Definitions
	int blink;

//Statements
	system("cls");
	Sleep(100);

	for (blink=3; blink>0; blink--)
	{
		printf("Invalid Option!");
		Sleep(350);
		system("cls");
		if(blink>1)
			Sleep(350);
		else
			Sleep(100);
	}
}

int main(void)
{
//Local Definitions
	char* choice;
	char str[256];
	LIST* P1;
	LIST* P2;
	LIST* P3;

//Statements
	choice = str;
	printf("Welcome to the polynomial calculator.\n\n"
		   "Main Menu:\n\n"
		   "Enter new polynomials .................... 'n'\n"
		   "Exit polynomial calculator ............... 'x'\n\n"
		   "What would you like to do? ");
	scanf("%s", &str);
	if (str[1] != '\0')
	{
		*choice = '\0';
	}
	else
	{
		choice = str;
		*choice = toupper(*choice);
	}

	while (*choice != 'X')
	{
		if (*choice == 'N')
		{
			system("cls");
			printf("Enter first polynomial:\n\n");
			P1 = getPoly();

			system("cls");
			printf("Enter second polynomial:\n\n");
			P2 = getPoly();

			system("cls");
			printf("Your first polynomial:  ");
			printPoly(P1);
			printf("Your second polynomial: ");
			printPoly(P2);
			printf("\n");

			if (listCount(P1) == 0 && listCount(P2) == 0)
			{
				printf("You need to enter at least one polynomial!\n\n"
					   "Options:\n\n"
					   "Enter new polynomials .................... 'n'\n"
					   "Exit polynomial calculator ............... 'x'\n\n"
					   "What would you like to do? ");
				scanf("%s", &str);
				if (str[1] != '\0')
				{
					*choice = '\0';
				}
				else
				{
					choice = str;
					*choice = toupper(*choice);
				}
			}
			else
			{
				*choice = '\0';
			}
			while (*choice != 'N' && *choice != 'X')
			{
				printf("Operations Menu:\n\n"
					   "Add your polynomials ..................... '+'\n"
				       "Subtract your polynomials ................ '-'\n"
				       "Enter new polynomials .................... 'n'\n"
					   "Exit polynomial calculator ............... 'x'\n\n"
					   "What would you like to do? ");
				scanf("%s", &str);
					if (str[1] != '\0')
					{
						*choice = '\0';
					}
					else
					{
						choice = str;
						*choice = toupper(*choice);
					}

				if (*choice == '+')
				{
					P3 = addPolys(P1, P2);

					system("cls");
					printf("Your first polynomial:  ");
					printPoly(P1);
					printf("Your second polynomial: ");
					printPoly(P2);
					printf("\n");
					printf("Their sum: ");
					printPoly(P3);
					printf("\n");
				}
				else if (*choice == '-')
				{
					P3 = subtractPolys(P1, P2);
					
					system("cls");
					printf("Your first polynomial:  ");
					printPoly(P1);
					printf("Your second polynomial: ");
					printPoly(P2);
					printf("\n");
					printf("Their difference: ");
					printPoly(P3);
					printf("\n");
				}
				else if (*choice != 'N' && *choice != 'X')
				{
					blink();
					printf("Your first polynomial:  ");
					printPoly(P1);
					printf("Your second polynomial: ");
					printPoly(P2);
					printf("\n");
				}
			}
		}
		else
		{
			blink();
			printf("Main Menu:\n\n"
				   "Enter new polynomials .................... 'n'\n"
				   "Exit polynomial calculator ............... 'x'\n\n"
				   "What would you like to do? ");
			scanf("%s", &str);
			if (str[1] != '\0')
			{
				*choice = '\0';
			}
			else
			{
				choice = str;
				*choice = toupper(*choice);
			}
		}
	}
	system("cls");
	printf("Goodbye.\n\n");
	return 0;
}