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
#include "List.h"

Node::Node(int value)
:number(value), next(NULL)
{
}

List::List(void)
{
	head_ = 0;
}

Node* List::MakeNode(int value)
{
	// The constructor sets the value and sets next to 0.
	return new Node(value);
}

int List::Count(void)
{
	int count = 0;
	Node *list = head_;  
	while (list)
	{
		count++;
		list = list->next;
	}
	return count;
}
// STUDENT IMPLEMENTATION STARTS HERE.

List::~List(void)
{
	FreeList(head_);
}

/*!
 * \brief Adds a node with the given value to the end of a list.
 *
 * \param ppList
 * 	A pointer to the list to modify.
 *
 * \param value
 * 	The value of the new node to add.
 */
void List::AddToEnd(struct Node **ppList, int value)
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

void List::AddToEnd(int value)
{
	AddToEnd(&head_, value);
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
void List::AddToFront(struct Node **ppList, int value)
{
	Node* newHead = MakeNode(value);

	newHead->next = *ppList;
	*ppList = newHead;
}

void List::AddToFront(int value)
{
	AddToFront(&head_, value);
}

/*!
 * \brief Destroys all the nodes in a list, freeing up the memory.
 *
 * \param pList
 * 	The list to deallocate.
 */
void List::FreeList(struct Node *pList)
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
void List::Insert(struct Node **ppList, int value, int position)
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

void List::Insert(int value, int position)
{
	Insert(&head_, value, position);
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
struct Node *List::FindItem(struct Node *list, int value)
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

struct Node *List::FindItem(int value)
{
	return(FindItem(head_, value));
}

/*!
 * \brief Delete the node with the first occurance of the specified value.
 *
 * \param ppList
 * 	The linked list to search in.
 *
 * \param value
 * 	The value to delete from the list.
 */
void List::Delete(struct Node **ppList, int value)
{
	if (*ppList)
	{
		if ((*ppList)->number == value)
		{
			Node *temp = *ppList;
			*ppList = (*ppList)->next;

			delete temp;
		}
		else
		{
			Delete(&(*ppList)->next, value);
		}
	}
}

void List::Delete(int value)
{
	Delete(&head_, value);
}

/*!
 * \brief Concatenates two lists.
 *
 * \param Destination
 * 	The list that is being appended to.
 *
 * \param Source
 * 	The list to append to the destination.
 */
void List::Concat(struct Node **Destination, struct Node *Source)
{
	if (Source)
	{
		AddToEnd(Destination, Source->number);
		Concat(Destination, Source->next);
	}
}

void List::Concat(const List &toConcat)
{
	Concat(&head_, toConcat.head_);
}

/*!
 * \brief Deletes all of the values in ppList that are in the Items list.
 *
 * \param ppList
 * 	The list to delete stuff from.
 *
 * \param Items
 * 	A list containing all values to delete.
 */
void List::Delete(struct Node **ppList, struct Node *Items)
{
	if (Items)
	{
		Delete(ppList, Items->number);
		Delete(ppList, Items->next);
	}
}

void List::Delete(List &toDelete)
{
	Delete(&head_, toDelete.head_);
}

/*!
 * \brief Inserts a new node in the correct position.
 *
 * \param ppList
 * 	The list to insert a node into.
 *
 * \param value
 * 	The value of the new node.
 */
void List::Insert(struct Node **ppList, int value)
{
	if(*ppList == NULL || (*ppList)->number > value)
	{
		AddToFront(ppList, value);
	}
	else
	{
		Insert(&(*ppList)->next, value);
	}
}

void List::Insert(int value)
{
	Insert(&head_, value);
}

std::ostream &operator<<(std::ostream &lhs, const Node *rhs)
{
	if (rhs)
	{
		lhs << rhs->number << "   ";
		return(lhs << rhs->next);
	}
	return lhs;
}

std::ostream &operator<<(std::ostream &lhs, const List &rhs)
{
	lhs << rhs.head_;

	return lhs;
}

