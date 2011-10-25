/******************************************************************************/
/*!
\file   list.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Lab #7
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

/*!
 * \brief Constructs a default Node.
 */
Node::Node(int value)
:number(value), next(NULL)
{
}

/*!
 * \brief Constructs a default List.
 */
List::List(void)
{
	head_ = 0;
}

/*!
 * \brief Allocates a new Node.
 *
 * \param value
 * 	The value to assign to the new Node.
 *
 * \return
 * 	A pointer to the newly-allocated Node.
 */
Node* List::MakeNode(int value)
{
	// The constructor sets the value and sets next to 0.
	return new Node(value);
}

/*!
 * \brief Counts the number of Nodes in a List.
 *
 * \return
 * 	The number of Nodes in the List.
 */
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

/*!
 * \brief Destructor for a List.
 *
 * Frees up any existing Node memory in the List.
 */
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

/*!
 * \brief Adds a value to the end of a List.
 *
 * \param value
 * 	The value to append to the List.
 */
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

/*!
 * \brief Adds a value to the front of the List.
 *
 * \param value
 * 	The value to prepend to the List.
 */
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

/*!
 * \brief Inserts a value into a given position in the list.
 *
 * Does not insert the value if the position is out of bounds for the list.
 *
 * \param value
 * 	The value to insert.
 *
 * \param position
 * 	The index to insert the value at.
 */
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

/*!
 * \brief Finds a Node with a given value in the List.
 *
 * This is a very un-useful function ever since this became a class.
 *
 * \param value
 * 	The value to look for in the List.
 *
 * \return
 * 	A pointer to the Node containing the value.
 */
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

/*!
 * \brief Deletes the first occurance of a given value from the List.
 *
 * \param value
 * 	The value to delete.
 */
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

/*!
 * \brief Concatenates two Lists together.
 *
 * \param toConcat
 * 	The List to append to the current List.
 */
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

/*!
 * \brief Deletes all the values in the second List from the current.
 *
 * \param toDelete
 * 	A List containing all the values to delete.
 */
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

/*!
 * \brief Inserts a value into a sorted order in the current List.
 *
 * \param value
 * 	The value to insert.
 */
void List::Insert(int value)
{
	Insert(&head_, value);
}

/*!
 * \brief Inserts the contents of the Node linked list into the stream.
 *
 * \param lhs
 * 	The stream to insert into.
 *
 * \param rhs
 * 	The current Node to insert into the stream.
 *
 * \return
 * 	A reference to the stream.
 */
std::ostream &operator<<(std::ostream &lhs, const Node *rhs)
{
	if (rhs)
	{
		lhs << rhs->number << "   ";
		return(lhs << rhs->next);
	}
	return lhs;
}

/*!
 * \brief Outputs the contents of a List into the stream specified.
 *
 * \param lhs
 * 	The stream to insert data into.
 *
 * \param rhs
 * 	The List to output.
 *
 * \return
 * 	A reference to the stream.
 */
std::ostream &operator<<(std::ostream &lhs, const List &rhs)
{
	lhs << rhs.head_;

	return lhs;
}

/*!
 * \brief Merges two sorted lists together.
 *
 * \param ppList
 * 	A pointer to the list to merge to.
 *
 * \param toAdd
 * 	A list of values to merge.
 */
void List::Merge(Node** ppList, Node** toAdd)
{
	if (*ppList && *toAdd)
	{
		if ((*ppList)->number > (*toAdd)->number)
		{
			Node* temp = *toAdd;
			*toAdd = (*toAdd)->next;
			temp->next = *ppList;
			*ppList = temp;
		}
		Merge(&(*ppList)->next, toAdd);
	}
	else if (toAdd != NULL && *ppList == NULL)
	{
		*ppList = *toAdd;
		*toAdd = NULL;
	}
}

/*!
 * \brief Merges the specified List with the current one.
 *
 * Both Lists should be in sorted order ahead of time.
 *
 * \param rhs
 * 	The List to merge with the current List.
 */
void List::Merge(List &rhs)
{
	Merge(&head_, &rhs.head_);
}

/*!
 * \brief Removes duplicates from the List.
 *
 * \return
 * 	The number of elements removed.
 */
int List::RemoveDuplicates(void)
{
	Node* temp = head_;
	int removed = 0;

	while (temp && temp->next)
	{
		if (temp->next->number == temp->number)
		{
			Delete(temp->number);
			temp = head_;
			++removed;
		}
		else
		{
			temp = temp->next;
		}
	}

	return(removed);
}

