/*		This program simulates a mouse in a maze. The program prints the path taken by the 
	mouse from the starting point to the final point, including all spots that have been 
	visited and backtracked. Thus, if a spot is visited two times, it is printed two times; 
	if it is visited three times, it is printed three times.
		The entrance spot, where the mouse starts its journey, is chosen by the user who 
	runs the program. It can be changed each time.
		A two-dimensional array is used as a supporting data structure to store the maze.
	Each element of the array is either black or white. A black element is a square that the 
	mouse cannot enter. A white element is a square that can be used by the mouse. In the 
	array, a black element is represented by a 1 and a white element by a 0.
		The program begins by creating the maze. It then initializes the exit spot and prompts 
	the user for the coordinates of the entrance spot. If the user enters coordinates of a black 
	spot, the program requests new coordinates until a white spot is entered. The mouse starts 
	from the entrance spot and tries to reach the exit spot and its reward. Note, however, that 
	some start positions do not lead to the exit.
		As the mouse progresses through its journey, its path is printed, and after each trial, 
	regardless of the outcome, the user should be given the opportunity to stop or continue.

		Written by: Craig Nathan
		Date:		8/21/09
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define ROW 10
#define COL 12

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

//Spot Structure Definition
struct SPOT
{
	int x;
	int y;
};

/* ========================== createSpot ===========================
	This algorithm create a spot.
		Pre   x is the spot's x-coordinate
			  y is the spot's y-coordinate
		Post  returns the spot
   =================================================================
*/
struct SPOT createSpot(int x, int y)
{
//Local Definitions
	struct SPOT spot;

//Statements
	spot.x = x;
	spot.y = y;
	return spot;
}

/* ========================== spotCompare ===========================
	This function compares two spots.
		Pre   a and b are both valid spots
		Post  returns 1 if identical
					  0 if not
   =================================================================
*/
int spotCompare(struct SPOT a, struct SPOT b)
{
	if (a.x == b.x && a.y == b.y)
		return 1;
	else
		return 0;
}

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
int pushStack (STACK *stack, void* dataInPtr)
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
void* popStack (STACK *stack)
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
void* stackTop (STACK *stack)
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
   ================================================================
*/
int stackCount (STACK *stack)
{
	return stack->count;
}

/* ========================== destroyStack ==========================
	This function releases all nodes to the heap.
		Pre    stack is a pointer to the stack
		Post   count returned
   ==================================================================
*/
STACK* destroyStack (STACK* stack)
{
//Local Definitions
	STACK_NODE* temp;

//Statements
	if (stack)
	{
	//Delete all nodes in stack
		while (stack->top != NULL)
		{
			//Delete data entry
			free(stack->top->dataPtr);

			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		}	free(stack);	//stack empty: destroy head node
	}	return NULL;
}

/* ========================== printMaze ==========================
	Prints the maze in the standard output.
		Pre    maze is a valid maze
			   currentSpot is the current spot of the mouse
			   exit is the exit spot of the maze
			   flag represents a token if set to 1 else 0 means no token
		Post   maze printed
   ================================================================
*/
void printMaze(int maze[ROW][COL], struct SPOT currentSpot, struct SPOT exit, int flag)
{
//Local Definitions
	int i, j;
	struct SPOT voidSpot = createSpot(0,0);

//Statements
	printf("MouseMaze:\n\n");
	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COL; j++)
		{
			if (spotCompare(currentSpot, voidSpot) == 1)
			{
				printf("%d ", maze[i][j]);
			}
			else if (currentSpot.x == i && currentSpot.y == j)
			{
				if (spotCompare(currentSpot, exit) == 1)
					printf("+!!!");
				else if (flag == 1)
					printf("* ");
				else
					printf("+ ");
			}
			else
			{
				printf("%d ", maze[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
//Local Definitions
	int i, j, row, col, choice, altsBefore, alts, tFlag, trapped;
	struct SPOT entrance, exit, currentSpot, prevSpot, altSpot, voidSpot, token, *visitPtr, *altPtr, *tPtr;
	STACK *visitStack, *altStack, *tempStack;

//Statements
	//initialize user input variables
	row = 0;
	col = 0;
	choice = 0;

	//create token
	token = createSpot(-1,-1);

	//MouseMaze home screen prompt
	printf("What would you like to do?\n 1: Choose entry point and drop mouse into maze\n 2: Exit MouseMaze\n\n");
	scanf("%d", &choice);
	system("cls");

	//loop until user ends program
	while(choice != 2)
	{
		//create maze
		int maze[ROW][COL] =   {1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,0,0,1,0,0,1,0,1,0,1,
								1,1,1,0,1,0,1,1,0,0,0,1,
								1,1,0,0,0,0,0,0,0,1,0,0,
								1,1,0,1,1,1,1,1,0,1,1,1,
								1,1,0,1,1,1,0,0,0,0,1,1,
								1,1,0,0,0,1,1,0,1,0,1,1,
								1,1,1,1,0,1,1,1,0,1,0,1,
								1,1,0,0,0,0,0,1,0,0,0,1,
								1,1,1,1,1,1,1,1,1,1,1,1};
		
		//create stacks to store visited spots or alternative spots at intersections
		visitStack = createStack();
		altStack = createStack();
		tempStack = createStack();

		//Use default MouseMaze
		if (choice == 1)
		{
			//find exit
			i = 0;
			j = 0;
			while(i<ROW || j<COL)
			{
				if (maze[0][j] == 0)
					exit = createSpot(0,j);
				else if (maze[i][11] == 0)
					exit = createSpot(i,11);	
				else if (maze[11][j] == 0)
					exit = createSpot(11,j);		
				else if (maze[i][0] == 0)
					exit = createSpot(i,0);

				if (((exit.x == 0 || exit.x == 11) && exit.y == j) || (exit.x == i && (exit.y == 0 || exit.y == 11)))
					break;

				i++;
				j++;
			}

			//create void spot for first print out
			voidSpot = createSpot(0,0);

			//initialize token flag
			tFlag = 0;

			//initialize trapped status
			trapped = 0;

			//print default MouseMaze
			printMaze(maze, voidSpot, exit, tFlag);

			//prompt user for entrance coordinates
			printf("Where you would like the mouse to enter the maze?\n row: ");
			scanf("%d",&row);
			printf(" col: ");
			scanf("%d",&col);

			//catch invalid entrance coordinates
			while(maze[row-1][col-1]==1 || row<1 || row>10 || col<1 || col>12 )
			{
				//prompt user for vaid entrance coordinates
				printf("Please specify a valid entrance point into the maze. \nYour coordinates must correspond to a zero in the maze.\n row: ");
				scanf("%d",&row);
				printf(" col: ");
				scanf("%d",&col);
			}

			//standardize coordinates for array handling
			row -= 1;
			col -=1;

			//initialize entrance spot and point to it
			visitPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
			entrance = createSpot(row, col);
			currentSpot = entrance;
			*visitPtr = currentSpot;
			
			/*   ===============================
			   ==== BEGIN MOVING THROUGH MAZE ====
			     ===============================   */

			//while currentSpot is not the exit, proceed through the maze
			while (spotCompare(currentSpot, exit) == 0 && trapped == 0)
			{
				//store new current spot
				pushStack(visitStack, visitPtr);

				////delay, clear, print
				Sleep(75);
				system("cls");
				printMaze(maze, currentSpot, exit, tFlag);

				//get currentSpot coordinates
				row = currentSpot.x;
				col = currentSpot.y;

					/*   ================================
					   ==== PERFORM SURROUNDINGS CHECK ====
						 ================================   */

				//alternatives before check
				altsBefore = stackCount(altStack);					

				if (maze[row][col-1] == 0)						//look left
				{
					altSpot = createSpot(row, col-1);
					if (spotCompare(altSpot, prevSpot) == 0)	//not previous spot
					{
						//make alternative
						altPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*altPtr = altSpot;
						pushStack(altStack, altPtr);
					}
				}
				if (maze[row][col+1] == 0)						//look right
				{
					altSpot = createSpot(row, col+1);
					if (spotCompare(altSpot, prevSpot) == 0)	//not previous spot
					{
						//make alternative
						altPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*altPtr = altSpot;
						pushStack(altStack, altPtr);
					}
				}
				if (maze[row-1][col] == 0)						//look up
				{
					altSpot = createSpot(row-1, col);
					if (spotCompare(altSpot, prevSpot) == 0)	//not previous spot
					{
						//make alternative
						altPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*altPtr = altSpot;
						pushStack(altStack, altPtr);
					}
				}
				if (maze[row+1][col] == 0)						//look down
				{
					altSpot = createSpot(row+1, col);
					if (spotCompare(altSpot, prevSpot) == 0)	//not previous spot
					{
						//make alternative
						altPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*altPtr = altSpot;
						pushStack(altStack, altPtr);
					}
				}
				//alternatives after check
				alts = stackCount(altStack);		

				//alternatives for current spot
				alts -= altsBefore;

					/*   ========================================================
					   ==== DETERMINE CLASS OF CURRENT SPOT AND MAKE NEXT MOVE ====
						 ========================================================   */

				if (alts == 0)							//dead end
				{
					//point to previously visited spot
					visitPtr = popStack(visitStack);

					//backtrack by one spot
					currentSpot = *visitPtr;

					//back track while spot is not token and mouse is not trapped
					while(tFlag == 0 && trapped == 0)
					{
						if(stackCount(visitStack) == 0 && stackCount(altStack) == 0)
						{
							trapped = 1;	//break out of token search loop
						}
						else
						{
							//point to previously visited spot
							visitPtr = popStack(visitStack);

							//backtrack by one spot
							currentSpot = *visitPtr;

							//set token flag if token
							if (spotCompare(currentSpot, token) == 1)
							{
								if(stackCount(altStack) == 0)
									trapped = 1;	//break out of token search loop
								else
									tFlag = 1;
							}
							else
							{
								//delay, clear, print
								Sleep(75);
								system("cls");
								printMaze(maze, currentSpot, exit, tFlag);
							}
						}
					}

					//token found: at intersection spot
					if (tFlag == 1)
					{
						//pop off intersection coordinates and print
						visitPtr = stackTop(visitStack);
						currentSpot = *visitPtr;

						//delay, clear, print (*)
						Sleep(75);
						system("cls");
						printMaze(maze, currentSpot, exit, tFlag);

						//push back token
						visitPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*visitPtr = token;
						pushStack(visitStack, visitPtr);

						//reset token flag
						tFlag = 0;
						
						//save current spot before next move
						prevSpot = currentSpot;	

						//move to next alternative spot
						altPtr = popStack(altStack);
						currentSpot = *altPtr;

						//point to new current spot
						visitPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*visitPtr = currentSpot;
					}
				}
				else if (alts == 1)						//continuing spot
				{
					//save current spot before next move
					prevSpot = currentSpot;	

					//move to next spot
					altPtr = popStack(altStack);
					currentSpot = *altPtr;

					//point to new current spot
					visitPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
					*visitPtr = currentSpot;
				}
				else if (alts > 1)						//intersection
				{
					if (spotCompare(currentSpot, entrance) == 0)
					{
						//pop and save current alternatives
						for (i=0; i<alts; i++)
						{
							altPtr = popStack(altStack, altPtr);
							tPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
							*tPtr = *altPtr;
							pushStack(tempStack, tPtr);
						}

						//make previous spot an alternative
						altPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
						*altPtr = prevSpot;
						pushStack(altStack, altPtr);

						//bury the previous spot alternative
						for (i=0; i<alts; i++)
						{
							tPtr = popStack(tempStack, tPtr);
							altPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
							*altPtr = *tPtr;
							pushStack(altStack, altPtr);
						}
					}

					//save current spot before next move
					prevSpot = currentSpot;	

					//store decision token on top of intersection spot
					visitPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
					*visitPtr = token;
					pushStack(visitStack, visitPtr);

					//move to next spot
					altPtr = popStack(altStack);
					currentSpot = *altPtr;

					//point to new current spot
					visitPtr = (struct SPOT*) malloc(sizeof (struct SPOT));
					*visitPtr = currentSpot;
				}
			}
			if (spotCompare(currentSpot, exit) == 1)
			{
				//delay, clear, print
				Sleep(75);
				system("cls");
				printMaze(maze, currentSpot, exit, tFlag);
				printf("\n\n\t\t\t   Mouse has reached the end of the maze!\n\n\n\n");
			}
			else
			{
				printf("\n\n\t\t\t   Mouse is trapped!\n\n\n\n");
			}

			//destroy stacks
			destroyStack(visitStack);
			destroyStack(altStack);
			destroyStack(tempStack);

			//prompt user again
			printf("What would you like to do?\n 1: Choose entry point and drop mouse into maze\n 2: Exit MouseMaze\n\n");
			scanf("%d", &choice);
			system("cls");
		}
		else
		{
			printf("What would you like to do?\n 1: Choose entry point and drop mouse into maze\n 2: Exit MouseMaze\n\n");
			scanf("%d", &choice);
			system("cls");
		}
	}	
	printf("GoodBye.\n\n");
	return 0;
}