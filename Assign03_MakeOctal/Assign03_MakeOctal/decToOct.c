/*	This program converts decimal numbers to octal numbers using stacks.
		Written by: Craig Nathan
		Date:		8/16/09
*/
#include <stdio.h>
#include <stdlib.h>

// Stack ADT Type Definitions
typedef struct node
{
	void* dataPtr;
	struct node* link;
}STACK_NODE;

typedef struct
{
	int count;
	STACK_NODE* top;
}STACK;

/* ========================== createStack ==========================
	This algorithm creates an empty stack.
		Pre   nothing
		Post  returns pointer to a null stack
				-or- NULL if overflow
   =================================================================
*/
STACK* createStack (void)
{
//Local Definitions
	STACK* stack;

//Statements
	stack = (STACK*) malloc(sizeof (STACK));
	if (stack)
	{
		stack->count = 0;
		stack->top = NULL;
	}
	return stack;
}

/* ========================== pushStack ==========================
	This function pushes an item onto the stack.
		Pre    stack is a pointer to the stack
			   dataPtr pointer to data to be inserted
		Post   data inserted into stack
		Return true if successful
			   false if underflow
   ===============================================================
*/
int pushStack (STACK* stack, void* dataInPtr)
{
//Local Definitions
	STACK_NODE* newPtr;

//Statements
	newPtr = (STACK_NODE*) malloc(sizeof (STACK_NODE));
	if (!newPtr)
		return 0;

	newPtr->dataPtr = dataInPtr;

	newPtr->link = stack->top;
	stack->top = newPtr;

	(stack->count)++;
	return 1;
}

/* ========================== popStack ==========================
	This function pops an item on the top of the stack.
		Pre    stack is a pointer to the stack
		Post   returns pointer to user data if successful
					   NULL if underflow
   ===============================================================
*/
void* popStack (STACK* stack)
{
//Local Definitions
	void* dataOutPtr;
	STACK_NODE* temp;

//Statements
	if (stack->count == 0)
		dataOutPtr = NULL;
	else
	{
		temp = stack->top;
		dataOutPtr = stack->top->dataPtr;
		stack->top = stack->top->link;
		free (temp);
		(stack->count)--;
	}
	return dataOutPtr;
}

/* ========================== stackTop ==========================
	Retrieves data from the top of stack without changing the stack.
		Pre    stack is a pointer to the stack
		Post   returns data pointer if successful
				       null pointer if stack empty
   =================================+==============================
*/
void* stackTop (STACK* stack)
{
	if (stack->count == 0)
		return NULL;
	else
		return stack->top->dataPtr;
}

/* ========================== printCount ==========================
	Returns number of elements in stack.
		Pre    stack is a pointer to the stack
		Post   count returned
   =================================+==============================
*/
int stackCount (STACK* stack)
{
	return stack->count;
}

/* ========================== printStack ==========================
	This function prints a singly linked stack.
		Pre    pStackTop is  pointer to valid stack
		Post   data in stack printed
   =================================+==============================
*/
void printStack (STACK* pStackTop)
{
//Local Definitions
	int* printData;

//Statements
	
	while(stackCount(pStackTop) != 0)
	{
		printData = popStack(pStackTop);
		printf("%d",*printData);
	}
}
	
/* ========================== decToOct ==========================
	Converts a decimal to an octal number.
		Pre   dec is a positive float type number
		Post  octal equivalent of dec is printed on the screen
   ==============================================================
*/
void decToOct(float dec, STACK* stack, int* digit, int power)
{
//Local Definitions
	float frac, whole, powerVal, rem;
	STACK* wholeStack;
	STACK* fracStack;

//Statements
	digit = (int*) malloc(sizeof (int));

	//base case: dec is zero
	if (dec == 0.0)
	{
		if (power == -1)
		{
			printf("0.0\n");
			return;
		}
		fracStack = createStack();
		while (stackCount(stack) != 0)
		{
			digit = popStack (stack);
			pushStack(fracStack, digit);
		}
		printStack(fracStack);
		printf("\n");
		return;
	}
	
	//when the whole part of 'dec' needs conversion
	if (power > -1)
	{
		//fetch power value off of the stack
		digit = popStack (stack);
		powerVal = *digit;

		//Conversion Algorithm
			//find remainder
			rem = dec/powerVal;

			//find new 'dec'
			dec -= (powerVal * (int)rem);

		//remainder becomes digit in octal number
		*digit = rem;
		pushStack(stack, digit);

		//find next lowest power of 8 value
		if(powerVal > 1)
		{
			digit = (int*) malloc(sizeof (int));
			*digit = powerVal/8;
			pushStack(stack, digit);
		}
		//print out converted whole number followed by a decimal point
		else
		{
			wholeStack = createStack();
			while (stackCount(stack) != 0)
			{
				digit = popStack (stack);
				pushStack(wholeStack, digit);
			}
			printStack(wholeStack);

			frac = dec - (int)dec;
			if (frac == 0.0)
				printf(".0");
			else
				printf(".");
		}
		
		//next lowest power of 8
		power--;

		//set power to an unrecognizable value
		if (power == -1)
			power--;

		return decToOct (dec, stack, digit, power);
	}

	//when dec is between zero and one
	if (dec > 0.0 && dec < 1.0)
	{
		//only print decimal point when original 'dec' greater than 0 and less than 1
		if (power == -1)
		{
			printf("0.");
		}
		//set power to an unrecognizable value so decimal is printed only once
		power--;		

		dec *= 8.0;
		*digit = dec;
		pushStack(stack, digit);
		frac = dec - (int)dec;
		return decToOct(frac, stack, digit, power);
	}

	// when dec is between one and nine there is no conversion necessary for the whole number
	else if (dec > 1.0 && dec < 8.0)
	{
		//print the whole number followed by a decimal point
		*digit = dec;
		frac = dec - (int)dec;
		if (frac == 0.0)
			printf("%d.0",*digit);
		else
			printf("%d.",*digit);

		//set power to an unrecognizable value so decimal is printed only once
		power--;

		//continue with only the fraction part of 'dec'
		frac = dec - (int)dec;
		return decToOct (frac, stack, digit, power);
	}

	//when 'dec' is greater than nine we use the successive division method
	//we need to find the greatest power of 8 that is divisible by 'dec'
	else if (dec >= 8.0)
	{
		whole = (int)dec;
		power = 0.0;
		
		//find the value of the greatest power of 8 that is divisible by 'dec'
		powerVal = 1.0;
		while (powerVal*8 <= whole)
		{
			powerVal *= 8;
			power++;
		}
		
		*digit = powerVal;
		pushStack (stack, digit);
		
		return decToOct (dec, stack, digit, power);
	}
}

int main(void)
{
//Local Definitions
	float dub;
	int* dataPtr;
	int power = -1;
	STACK* stack;

//Statements
	stack = createStack();
	dataPtr = (int*) malloc(sizeof (int));

	//prompt and read a decimal number
	printf("Enter a positive number in decimal format: ");
	scanf("%f",&dub);
	
	decToOct(dub, stack, dataPtr, power);

	return 0;
}
