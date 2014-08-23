#include <stdio.h>
#include <stdlib.h>

//Macro Definitions
#define COMPARE ( ((* pList->compare) (pArg, (*pLoc)->dataPtr)) )
#define COMPARE_LAST ((pList->compare) (pArg, pList->rear->dataPtr))

// List ADT Type Definitions
typedef struct node
{
	void* dataPtr;
	struct node* link;
}NODE;

typedef struct
{
	int count;
	NODE* pos;
	NODE* head;
	NODE* rear;
	int (*compare) (void* arg1, void* arg2);
}LIST;

/* ========================== createList ===========================
	Allocate dynamic memory for a list head node and returns its 
	address to caller.
		Pre    compare is address of compare function used to compare 
				two nodes.
		Post   head has allocated or error returned
		Return head node pointer or null if overflow
   =================================================================
*/
LIST* createList (int (*compare) (void* arg1, void* arg2))
{
//Local Definitions
	LIST* list;

//Statements
	list = (LIST*) malloc (sizeof (LIST));
	if (list)
	{
		list->head    = NULL;
		list->pos     = NULL;
		list->rear    = NULL;
		list->count   = 0;
		list->compare = compare;
	}
	return list;
}

/* ============================ destroyList =============================
	Deletes all data in list and recycles memory.
		Pre    pList is a pointer to a valid list
		Post   all data and head structure deleted
		Return null head pointer
   ======================================================================
*/
LIST* destroyList (LIST* pList)
{
	//Local Definitions
	NODE* deletePtr;

	//Statements
	if (pList)
	{
		while (pList->count > 0)
		{
			//First delete data
			free (pList->head->dataPtr);

			//Now delete node
			deletePtr = pList->head;
			pList->head = pList->head->link;
			pList->count--;
			free (deletePtr);
		} free (pList);
	} return NULL;
}

/* ============================ _insert =============================
	Inserts data pointer into a new node.
		Pre    pList is pointer to valid list
			   pPre is pointer to data's predecessor
			   dataInPtr is data pointer to be inserted
		Post   data have been inserted in sequence
		Return 1 if successful
			   0 if memory overflow
   ==================================================================
*/
static int _insert (LIST* pList, NODE* pPre, void* dataInPtr)
{
//Local Definitions
	NODE* pNew;

//Statements
	if (!(pNew = (NODE*) malloc(sizeof(NODE))))
		return 0;
	pNew->dataPtr = dataInPtr;
	pNew->link = NULL;
	
	if (pPre == NULL)
	{
		//Adding before first node or to empty list
		pNew->link = pList->head;
		pList->head = pNew;
		if (pList->count == 0)
			pList->rear = pNew;		//Adding to empty list: set rear
	}
	else
	{
		//Adding in middle or at end
		pNew->link = pPre->link;
		pPre->link = pNew;

		//Now check for add at end of list
		if (pNew->link == NULL)
			pList->rear = pNew;
	}
	pList->pos = pNew;
	(pList->count)++;
	return 1;
}

/* ========================== _search ==============================
	Searches list and passes back address of node containing target 
	and its logical predecessor.
		Pre    pList is pointer to initialized list
			   pPre is pointer variable to predecessor
			   pLoc is pointer variable to receive node
			   pArg is pointer to key being sought
		Post   pLoc points to first equal/greater key
		  -or- NULL if target > key of last node
			   pPre points to largest node < key
	      -or- NULL if target < key of first node
		Return 1 if found
			   0 if not found
   =================================================================
*/
static int _search (LIST* pList, NODE** pPre, NODE** pLoc, void* pArg)
{
//Local Definitions
	int result;

//Statements
	*pPre = NULL;
	*pLoc = pList->head;
	if (pList->count == 0)
		return 0;
	
	//Test for argument > last node in list
	if (COMPARE_LAST > 0)
	{
		*pPre = pList->rear;
		*pLoc = NULL;
		return 0;
	}

	while ( (result = COMPARE) > 0 )
	{
		//Have not found search argument location
		*pPre = *pLoc;
		*pLoc = (*pLoc)->link;
	}

	if (result == 0)
		return 1;		//argument found--success
	else
		return 0;
}

/* ============================ addNode =============================
	Inserts data into list.
		Pre    pList is pointer to valid list
			   dataInPtr pointer to insertion data
		Post   data inserted or error
		Return -1 if overflow
				0 if successful
				1 if dupe key
   ==================================================================
*/
int addNode (LIST* pList, void* dataInPtr)
{
//Local Definitions
	int found;
	int success;

	NODE* pPre;
	NODE* pLoc;

//Statements
	found = _search(pList, &pPre, &pLoc, dataInPtr);
	if (found == 1)
		return (+1);		//Duplicate keys not allowed

	success = _insert (pList, pPre, dataInPtr);
	if(success == 0)
		return (-1);		//Overflow
	return (0);
}

/* ========================== _delete ==============================
	Deletes data from a list and returns pointer to data to calling 
	module.
		Pre    pList is pointer to valid list
			   pPre is pointer to predecessor node
			   pLoc is pointer to target node
			   dataOutPtr is pointer to data pointer
		Post   data have been deleted and returned
			   data memory has been freed
   =================================================================
*/
void _delete (LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr)
{
//Statements
	*dataOutPtr = pLoc->dataPtr;
	if (pPre == NULL)
		//deleting first node
		pList->head = pLoc->link;
	else
		//deleting any other node
		pPre->link = pLoc->link;

	//Test for deleting last node
	if (pLoc->link == NULL)
		pList->rear = pPre;

	(pList->count)--;
	free (pLoc);

	return;
}

/* ========================= removeNode =============================
	Removes data from list.
		Pre    pList is pointer to valid list
			   keyPtr is pointer to key to be deleted
			   dataOutPtr is pointer to data pointer
		Post   node deleted or error returned
		Return 0 if not found
			   1 if deleted
   ==================================================================
*/
int removeNode (LIST* pList, void* keyPtr, void** dataOutPtr)
{
//Local Definitions
	int found;
	NODE* pPre;
	NODE* pLoc;

//Statements
	found = _search(pList, &pPre, &pLoc, keyPtr);
	if (found == 1)
		_delete(pList, pPre, pLoc, dataOutPtr);				//compiler complains about this line

	return found;
}

/* ========================== searchList ===========================
	Interface to search function.
		Pre    pList is pointer to initialized list
			   pArg is pointer to key being sought
		Post   pDataOut contains pointer to found data
				-or- NULL if not found
		Return 1 if successful
			   0 if not found
   =================================================================
*/
int searchList (LIST* pList, void* pArg, void** pDataOut)
{
//Local Definitions
	int found;

	NODE* pPre;
	NODE* pLoc;

//Statements
	found = _search (pList, &pPre, &pLoc, pArg);
	if (found == 1)
		*pDataOut = pLoc->dataPtr;
	else
		*pDataOut = NULL;
	return found;
}

/* ========================= retrieveNode ===========================
	This algorithm retrieves data in the list without changing the 
	list contents.
		Pre    pList is pointer to initialized list
			   pArg is pointer to key to be retrieved
		Post   data (pointer) passed back to caller
		Return 1 if successful
			   0 if memory overflow
   ==================================================================
*/
static int retrieveNode (LIST* pList, void* pArg, void** dataOutPtr)
{
//Local Definitions
	int found;
	NODE* pPre;
	NODE* pLoc;

//Statements
	found = _search (pList, &pPre, &pLoc, pArg);
	if (found == 1)
	{
		*dataOutPtr = pLoc->dataPtr;
		return 1;
	}

	*dataOutPtr = NULL;
	return 0;
}

/* =========================== traverse =============================
	Traverses a list. Each call either starts at the beginning of the 
	list of returns the location of the next element in the list.
		Pre    pList is pointer to valid list
			   fromWhere is 0 to start at first element
			   dataPtrOut is address of pointer to data
		Post   if more data, address of next node
		Return 1 if node located
			   0 if end of list
   ==================================================================
*/
int traverse (LIST* pList, int fromWhere, void** dataPtrOut)
{
//Statements
	if (pList->count == 0)
		return 0;

	if (fromWhere == 0)
	{
		//Start from first node
		pList->pos = pList->head;
		*dataPtrOut = pList->pos->dataPtr;
		return 1;
	}
	else
	{
		//Start from current position
		if (pList->pos->link == NULL)
		{
			return 0;
		}
		else
		{
			pList->pos = pList->pos->link;
			*dataPtrOut = pList->pos->dataPtr;
			return 1;
		}
	}
}

/* ============================ listCount ==========================
	Inserts data pointer into a new node.
		Pre    pList is pointer to valid list
		Return count for number of nodes in list
   =================================================================
*/
int listCount (LIST* pList)
{
//Statements
	return pList->count;
}

/* ============================ emptyList ==========================
	Indicates whether or not the list is empty.
		Pre    pList is pointer to valid list
		Return 1 if empty
			   0 if list has data
   =================================================================
*/
int emptyList (LIST* pList)
{
//Statements
	return (pList->count == 0);
}

/* ============================ fullList ===========================
	Indicates if there is any room left for more data. This list is 
	full if memory cannot be allocated for another node.
		Pre    pList is pointer to valid list
		Return 1 if full
			   0 if room for node
   =================================================================
*/
int fullList (LIST* pList)
{
//Local Definitions
	NODE* temp;

//Statements
	if ((temp = (NODE*)malloc (sizeof(*(pList->head)))))
	{
		free (temp);
		return 0;
	}

	//Dynamic memory full
	return 1;
}

