/******************************************************************************/
/*!
\file   list.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Lab #3
\date   2/5/2010
\brief  
    Contains implementation of the linked list lab.
      
    Functions include:
        -AddToEnd
        -AddToFront
        -Count
	-FreeList
	-PrintList
	-Insert
	-FindItem
    
  Hours spent on this assignment: 1

  Specific portions that gave you the most trouble: 
  	None.

  
  
  
*/
/******************************************************************************/

#include <iostream> // cout, endl
#include "list.h"

namespace 
{
  struct Node* MakeNode(int value)
  {
    struct Node *pNode = new Node; // Allocate memory
    pNode->number = value;         // Set number
    pNode->next = 0;               // Set next (no next yet)

    return pNode;
  }
}

void PrintList(struct Node *list)
{
  while (list)
  {
    std::cout << list->number << "   ";
    list = list->next;
  }
  std::cout << std::endl;
}

int Count(struct Node *list)
{
  int count = 0;
  while (list)
  {
    count++;
    list = list->next;
  }
  return count;
}

// STUDENT IMPLEMENTATION STARTS HERE.

void AddToEnd(struct Node **ppList, int value)
{
	if (*ppList)
	{
		AddToEnd(&(*ppList)->next, value);
	}
	else
	{
		(*ppList) = MakeNode(value);
	}
}

void AddToFront(struct Node **ppList, int value)
{
	Node* newHead = MakeNode(value);

	newHead->next = *ppList;
	*ppList = newHead;
}

void FreeList(struct Node *pList)
{
	if (pList)
	{
		FreeList(pList->next);
	}

	delete pList;
}

void Insert(struct Node **ppList, int value, int position)
{
	if (*ppList && position > 0)
	{
		Insert(&(*ppList)->next, value, position - 1);
	}
	else
	{
		if (position <= 0)
		{
			AddToFront(ppList, value);
		}
	}
	// Do nothing if we're at end of list and position > 0.
}

struct Node *FindItem(struct Node *list, int value)
{
	if (list && list->number != value)
	{
		return(FindItem(list->next, value));
	}
	else
	{
		return(list);
	}
}

