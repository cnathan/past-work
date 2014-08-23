/*	This program calculates the length of a list.
		Written by: Craig Nathan
		Date:		8/12/09
*/
#include <stdio.h>
#include <stdlib.h>

//List ADT Type Definitions
typedef struct node			//data structure type: node
{
	void* dataPtr;
	struct node* link;
}NODE;						//structure name

typedef struct
{
	NODE* pos;
	NODE* head;
	NODE* rear;
}LIST;

/* ========================== createList ==========================
	Allocates dynamic memory for a list head node and returns
	its address to caller
		Pre    compare is address of compare function used 
				to compare two nodes
		Post   head has allocated or error returned
		Return head node pointer or null if overflow
   ================================================================
*/
LIST* createList(void)
{
//Local Definitions
	LIST* list;

//Statements
	list = (LIST*) malloc (sizeof (LIST));
	if (list)
	{
		list->head	  = NULL;
		list->pos     = NULL;
		list->rear    = NULL;
	}
	return list;
}

/* ========================== addNode ==========================
	Inserts data into list.
		Pre    pList is a pointer to valid list
			   dataInPtr pointer to insertion data
	    Post   node created
		Return new node pointer
   =============================================================
*/
NODE* addNode (LIST* pList, int* dataInPtr)
{
//Local Definitions
	NODE* pNew;

//Statements
	pNew = (NODE*) malloc (sizeof (NODE));
	pNew->dataPtr = dataInPtr;
	pNew->link = NULL;

	if (pList->head == NULL)
		pList->head = pNew;

	if (pNew->link == NULL)
		pList->rear = pNew;

	return pNew;
}

/* ========================== listLength ==========================
	Calculates the length of a list.
		Pre   nodePtr points to the first node of a given list
		Post  number of nodes in the list is returned
   ================================================================
*/
int listLength(NODE* pNode)
{
//Statements
	if (pNode->link == NULL)
		return 1;
	else
		return (1 + listLength (pNode->link));
}

/*  ============================================================== 
   ========================= Main Program =========================
    ==============================================================
*/
int main(void)
{
//Local Definitions
	int* newData;
	int* nodeData;
	int len;
	LIST* list;

//Statements

	//Create list
	list = createList();

	printf("List: ");

	//Create first node in list
	newData = (int*)malloc ( sizeof (int) );
	*newData = 74;
	list->pos = addNode (list, newData);
	nodeData = (int*)list->pos->dataPtr;
	printf("%d ", *nodeData);

	//Create second node in list
	newData = (int*)malloc (sizeof (int));
	*newData = 9;
	list->pos->link = addNode (list, newData);
	nodeData = (int*)list->pos->link->dataPtr;
	list->pos = list->pos->link;
	printf("%d ", *nodeData);

	//Create third node in list
	newData = (int*)malloc (sizeof (int));
	*newData = 26;
	list->pos->link = addNode (list, newData);
	nodeData = (int*)list->pos->link->dataPtr;
	list->pos = list->pos->link;
	printf("%d ", *nodeData);
	
	printf("\n\n");

	len = listLength (list->head);
	printf("This list has a total of %d nodes\n", len);

	return 0;
}