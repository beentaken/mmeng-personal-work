/*****************************************************************************/
/*!
\file   List.cpp
\author Marcus Meng
\par    email: marcus.meng@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment 6
\date   March 31, 2010
\brief
	This file contains the implementations for the functions in a
	templated List class (using a Linked List implementation internally.)

Hours spent on this assignment: 1

Specific portions that gave you the most trouble:

Figuring out that the operators that return lists need to have <T> in the
return value prototype.

*/
/*****************************************************************************/

namespace CS170
{

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// static members

template <typename T>
int List<T>::Node::node_count_ = 0; // Tracks total nodes created.

/*****************************************************************************/
/*!
\brief
	Returns the total number of nodes in existance.

\return
	The total number of Nodes currently in existance.
*/
/*****************************************************************************/
template <typename T>
int List<T>::node_count(void)
{
  return Node::node_count_;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// List::Node methods

/*****************************************************************************/
/*!
\brief
	Constructs a Node and puts the given value into the data field.

\param value
	The value of this particular node.
*/
/*****************************************************************************/
template <typename T>
List<T>::Node::Node(const T &value) : data(value)
{
  node_count_++;
}

/*****************************************************************************/
/*!
\brief
	Destructor for the Node.

	Decrements the total number of nodes in existance.
*/
/*****************************************************************************/
template <typename T>
List<T>::Node::~Node(void)
{
  node_count_--;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// public methods

/*****************************************************************************/
/*!
\brief
	Default constructor.

	Sets all of the data members to sane values.
*/
/*****************************************************************************/
template <typename T>
List<T>::List(void)
{
	head_ = tail_ = NULL;
	size_ = 0;
}

/*****************************************************************************/
/*!
\brief
	Copy constructor.

\param list
	The List containing data to copy into the current one.
*/
/*****************************************************************************/
template <typename T>
List<T>::List(const List &list)
{
	head_ = tail_ = NULL;
	size_ = 0;

	*this += list;
}

/*****************************************************************************/
/*!
\brief
	Initializes a new List from an array of data provided.

\param array
	An array containing the data to insert into the List.

\param size
	The size of the data array.
*/
/*****************************************************************************/
template <typename T>
List<T>::List(const T *array, const int size)
{
	head_ = tail_ = NULL;
	size_ = 0;

	for (int i = 0; i < size; ++i)
	{
		push_back(array[i]);
	}
}

/*****************************************************************************/
/*!
\brief
	Destructor for the List.

	Deallocates any remaining Nodes in the list.
*/
/*****************************************************************************/
template <typename T>
List<T>::~List(void)
{
	clear();
}

/*****************************************************************************/
/*!
\brief
	Removes all Nodes from the current List.
*/
/*****************************************************************************/
template <typename T>
void List<T>::clear(void)
{
  while (!empty())
    pop_front();

  head_ = tail_ = NULL;
}

/*****************************************************************************/
/*!
\brief
	Inserts a new Node at the front of the List.

\param item
	The value of the new Node to insert.
*/
/*****************************************************************************/
template <typename T>
void List<T>::push_front(const T &item)
{
	Node *temp = new_node(item); // Node to add.

	temp->next = head_;
	head_ = temp;

	// Special case for the very first insert.
	if (NULL == tail_)
	{
		tail_ = head_;
	}

	++size_;
}

/*****************************************************************************/
/*!
\brief
	Removes the Node at the front of the List.

	If the List is currently empty, it does nothing.
*/
/*****************************************************************************/
template <typename T>
void List<T>::pop_front(void)
{
	if (head_)
	{
		Node* to_delete = head_; // Hold value to delete.
		head_ = head_->next;

		delete to_delete;

		--size_;
	}
}

/*****************************************************************************/
/*!
\brief
	Inserts a new Node at the end of the List.

\param item
	The value of the Node to insert.
*/
/*****************************************************************************/
template <typename T>
void List<T>::push_back(const T &item)
{
	if (NULL == tail_)
	{
		push_front(item);
	}
	else
	{
		Node* temp = new_node(item); // Node to add.

		tail_->next = temp;
		tail_ = tail_->next;

		++size_;
	}
}

/*****************************************************************************/
/*!
\brief
	Finds the first value in the List.

	Does not actually check whether the List exists, behavior if there
	are no Nodes in the List is undefined.

\return
	The data contained in the first Node in the List.
*/
/*****************************************************************************/
template <typename T>
T List<T>::front(void) const
{
	return(head_->data);
}

/*****************************************************************************/
/*!
\brief
	Finds the size of the List.

\return
	The size of the List.
*/
/*****************************************************************************/
template <typename T>
int List<T>::size(void) const
{
	return(size_);
}

/*****************************************************************************/
/*!
\brief
	Finds whether the List is empty.

\return
	True if the list is empty, false otherwise.
*/
/*****************************************************************************/
template <typename T>
bool List<T>::empty(void) const
{
	return(!size_);
}

/*****************************************************************************/
/*!
\brief
	Overloaded assignment operator.

	Creates a temporary List in case of self-assignments.

\param rhs
	The List to copy into the current one.

\return
	A reference to the current List.
*/
/*****************************************************************************/
template <typename T>
List<T>& List<T>::operator=(const List &rhs)
{
	List temp(rhs); // To prevent self-assignment issues.
	clear();

	*this += temp;

	return(*this);
}

/*****************************************************************************/
/*!
\brief
	Overloaded addition operator. Returns a new List containing the data
	in the current and provided Lists concatenated.

\param rhs
	The List to add to the end of the concatenated List.

\return
	The new List containing all the provided values.
*/
/*****************************************************************************/
template <typename T>
List<T> List<T>::operator+(const List& rhs) const
{
	List temp(*this); // Create a copy of the List to return.

	temp += rhs;

	return(temp);
}

/*****************************************************************************/
/*!
\brief
	Overloaded add-and-assign operator. Concatenates the provided List to
	the current one.

\param rhs
	The List to concatenate to the current one.

\return
	A reference to the current List.
*/
/*****************************************************************************/
template <typename T>
List<T>& List<T>::operator+=(const List& rhs)
{
	for (int i = 0; i < rhs.size(); ++i)
	{
		push_back(rhs[i]);
	}

	return(*this);
}

/*****************************************************************************/
/*!
\brief
	Overloaded index operator. Obtains the value in the specified index.

	Does NOT check bounds. Behavior is undefined if the index is larger
	than the current size of the List.

\param index
	The index to look in.

\return
	A reference to the value stored at the specified index.
*/
/*****************************************************************************/
template <typename T>
T& List<T>::operator[](const int index)
{
	Node *iter = head_; // Iterator.

	for (int i = 0; i < index; ++i)
	{
		iter = iter->next;
	}

	return(iter->data);
}

/*****************************************************************************/
/*!
\brief
	Overloaded const index operator. Obtains the value in the specified
	index.

	Does NOT check bounds. Behavior is undefined if the index is larger
	than the current size of the List.

\param index
	The index to look in.

\return
	A constant reference to the value stored at the specified index.
*/
/*****************************************************************************/
template <typename T>
const T& List<T>::operator[](const int index) const
{
	Node *iter = head_; // Iterator;

	for (int i = 0; i < index; ++i)
	{
		iter = iter->next;
	}

	return(iter->data);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// private methods

/*****************************************************************************/
/*!
\brief
	Dynamically allocates a new Node, and initializes it with the value
	provided.

\param data
	The value the new Node will contain.

\return
	A pointer to the newly-created Node.
*/
/*****************************************************************************/
template <typename T>
typename List<T>::Node *List<T>::new_node(const T& data) const
{
  Node *node = new Node(data); // create the node
  node->next = 0;              // no next pointer yet
  return node;
}

} // namespace CS170


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// non-members

#include <iomanip>

/*****************************************************************************/
/*!
\brief
	Overloaded stream insertion operator. Inserts all data in the list
	into the specified output stream in a specific format.

\param os
	The stream to insert the List into.

\param list
	The List to insert into the stream.

\return
	A reference to the stream used.
*/
/*****************************************************************************/
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the top
  typename CS170::List<T>::Node *pnode = list.head_; // Iterator.

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  return os;
}

