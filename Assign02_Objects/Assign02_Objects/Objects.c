/*	This program calculates the length of a list.
		Written by: Craig Nathan
		Date:		8/12/09
*/

#include <stdio.h>
#include <stdlib.h>

/* ========================== Objects ==========================
	Calculates the combination of n objects taken k at a time.
		Pre   n is the number of objects
			  k is the amount of objects taken at a time
		Post  number of possible combinations is returned
   =============================================================
*/
int Objects(int n, int k)
{
	if (k==0 || n==k)
		return 1;
	else if (n>k && k>0)
		return ( Objects(n-1, k) + Objects(n-1, k-1) );
	else
		return 0;
}

int main(void)
{
	int numObjects = 49;
	int objectsTaken = 6;
	int combos;

	combos = Objects(numObjects, objectsTaken);

	printf("For %d numbers, there are %d different combinations of %d numbers.\n", numObjects, combos, objectsTaken);
	return 0;
}
