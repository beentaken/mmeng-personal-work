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
  /*!
   * Creates a Node, sets the initial value, and returns a pointer to it.
   *
   * \param value
   * 	The initial value of the node.
   *
   * \return
   * 	A pointer to the newly created node.
   */
  struct Node* MakeNode(int value)
  {
    struct Node *pNode = new Node; // Allocate memory
    pNode->number = value;         // Set number
    pNode->next = 0;               // Set next (no next yet)

    return pNode;
  }
}

/*!
 * \brief Prints out all values in a list, space-seperated.
 *
 * \param list
 * 	The list to print out.
 */
void PrintList(struct Node *list)
{
  while (list)
  {
    std::cout << list->number << "   ";
    list = list->next;
  }
  std::cout << std::endl;
}

/*!
 * \brief Counts up the number of nodes in a list.
 *
 * \param list
 * 	The list to count.
 *
 * \return
 * 	The number of nodes in the list.
 */
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

/*!
 * \brief Adds a node with the given value to the end of a list.
 *
 * \param ppList
 * 	A pointer to the list to modify.
 *
 * \param value
 * 	The value of the new node to add.
 */
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

/*!
 * \brief Adds a new node with the given value to the front of a list.
 *
 * \param ppList
 * 	The list to modify.
 *
 * \param value
 * 	The value of the node to add.
 */
void AddToFront(struct Node **ppList, int value)
{
	Node* newHead = MakeNode(value);

	newHead->next = *ppList;
	*ppList = newHead;
}

/*!
 * \brief Destroys all the nodes in a list, freeing up the memory.
 *
 * \param pList
 * 	The list to deallocate.
 */
void FreeList(struct Node *pList)
{
	if (pList)
	{
		FreeList(pList->next);
	}

	delete pList;
}

/*!
 * \brief Inserts a new node with the given value at the specified index.
 *
 * \param ppList
 * 	A pointer to the list to modify.
 *
 * \param value
 * 	The value of the node to add.
 *
 * \param position
 * 	The index of the new node.
 */
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

/*!
 * \brief Finds a node with the given value in the list.
 *
 * \param list
 * 	The list to search.
 *
 * \param value
 * 	The value to search for.
 * 
 * \return
 * 	A pointer to the node containing the value, if found, NULL otherwise.
 */
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

