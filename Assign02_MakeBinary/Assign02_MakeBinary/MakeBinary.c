/*	This program converts unsigned integers to their binary equivalent.
		Written by: Craig Nathan
		Date:		8/7/09
*/
#include <stdio.h>
#include <stdlib.h>

/* ========================== intToBin ==========================
	Converts an integer to a binary number.
		Pre   num is an unsigned integer
		Post  binary equivalent of num is printed on the screen
   ==============================================================
*/
void intToBin(unsigned int num)
{
//Local Definitions
	char zero = '0';
	char one = '1';
	
//Statements
	if (num == 0)
	{
		printf("%c", zero);
	}
	else if (num == 1)
	{
		printf("%c", one);
	}
	else if (num%2 == 0)
	{
		intToBin(num/2);
		printf("%c", zero);
		return 0;
	}
	else
	{
		intToBin(num/2);
		printf("%c", one);
		return 0;
	}
}

int main(void)
{
//Local Definitions
	unsigned int number;
	
//Statements
	//Prompt user for integer to convert
	printf("Enter an unsigned integer: ");
	scanf("%u", &number);
	
	//Print out binary equivalent
	printf("The binary equivalent is:  ");
	intToBin(number);
	printf("\n");

	return 0;
}