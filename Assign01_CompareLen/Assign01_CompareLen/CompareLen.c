/* Demonstrate generic compare functions and pointers to functions
	 Written by: Craig Nathan
	 Date: 08/02/09
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareStrLen(void* ptr1, void* ptr2);
void* larger(void* dataPtr1, void* dataPtr2, int (*ptrToCmpFunc)(void*,void*));

int main(void)
{
	//Local Definitions
	char* strx = "abcd";
	char* stry = "efgh2q3";
	char* lrg;

	//Statements
	lrg = ( (char*) larger (&(*strx), &(*stry), compareStrLen) );

	printf ("Larger string is: %s\n",lrg);
	return 0;
}

/* String specific compare function.
	 Pre  ptr1 and ptr2 are pointers to character pointers
	 Post returns +1 if ptr1 >= ptr2
		  returns -1 if ptr1 <  ptr2
*/
int compareStrLen(void* ptr1, void* ptr2)
{
	if ( strlen( (char*)ptr1 ) >= strlen( (char*)ptr2) )
		return 1;
	else
		return -1;
}

/* Generic function to determine the larger of two values 
   referenced as void pointers
      Pre  dataPtr1 and dataPtr2 are pointers to values of an unknown type.
	       ptrToCmpFunc is address of a function that knows the data types
	  Post data compared and larger value returned
*/
void* larger ( void* dataPtr1, void* dataPtr2, int (*ptrToCmpFunc)(void*,void*) )
{
	if ( (*ptrToCmpFunc) (dataPtr1, dataPtr2) > 0 )
		return dataPtr1;
	else 
		return dataPtr2;
}