#include "List.h"  // List class
#include <iomanip> // setw

namespace CS170
{

	int List::object_count_ = 0;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// public methods in this order: 
// Constructors (default, copy, non-defaults), destructor, operators, others

	/*!
	 * \brief
	 * 	Constructs a default List.
	 */
	List::List(void)
	{
		head_ = NULL;
		tail_ = head_;
		size_ = 0;
		++object_count_;
	}

	/*!
	 * \brief
	 * 	Constructs a copy of the List in the argument.
	 *
	 * \param to_copy
	 * 	The list to copy.
	 */
	List::List(const List& to_copy)
	{
		head_ = NULL;
		tail_ = head_;
		size_ = 0;

		if (!to_copy.empty())
		{
			operator=(to_copy);
		}

		++object_count_;
	}

	/*!
	 * \brief Constructs a list containing nodes with the values provided.
	 *
	 * \param array
	 * 	An array of integers containing the starting values for the
	 * 	list.
	 *
	 * \param size
	 * 	The size of the array passed in the argument.
	 */
	List::List(const int* array, const int size)
	{
		head_ = NULL;
		tail_ = head_;
		size_ = 0;

		for(int i = 0; i < size; ++i)
		{
			push_back(array[i]);
		}

		++object_count_;
	}

	/*!
	 * \brief
	 * 	Destructor for the List.
	 */
	List::~List(void)
	{
		clear();
	}

	/*!
	 * \brief
	 * 	Assignment/copy operator.
	 *
	 * \param rhs
	 * 	The List to copy values out from.
	 *
	 * \returns
	 * 	A reference to the now-modified List.
	 */
	List& List::operator=(const List& rhs)
	{
		clear();

		for (int i = 0; i < rhs.size(); ++i)
		{
			push_back(rhs[i]);
		}

		return(*this);
	}

	/*!
	 * \brief
	 * 	Appends the data in a List to the current List.
	 *
	 * \param rhs
	 * 	The List containing the data to append.
	 *
	 * \returns
	 * 	A reference to the modified current List.
	 */
        List& List::operator+=(const List& rhs)
	{
		for (int i = 0; i < rhs.size(); ++i)
		{
			push_back(rhs[i]);
		}

		return(*this);
	}

	/*!
	 * \brief
	 * 	Creates a new List containing all the values in the current
	 * 	and provided list.
	 *
	 * \param rhs
	 * 	Values to append to the current set.
	 *
	 * \returns
	 * 	A newly created List containing the values in both the current
	 * 	and provided Lists.
	 */
        List List::operator+(const List& rhs) const
	{
		List temp(*this);
		
		temp += rhs;

		return(temp);
	}

	/*!
	 * \brief
	 * 	Finds the value of the List at the specified index. Does NOT
	 * 	check bounds!
	 *
	 * \param index
	 * 	The index to check in.
	 *
	 * \returns
	 * 	A reference to the value at the specified index.
	 */
        int& List::operator[](const int index)
	{
		Node* temp = head_;

		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}

		return(temp->data);
	}

	/*!
	 * \brief
	 * 	Const version of the index function.
	 *
	 * \param index
	 * 	The index to check in.
	 *
	 * \returns
	 * 	The value of the node at the specified index.
	 */
        int List::operator[](const int index) const
	{
		Node* temp = head_;

		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}

		return(temp->data);
	}

	/*!
	 * \brief
	 * 	Prepends a given value to the List.
	 *
	 * \param new_value
	 * 	The value to prepend.
	 */
	void List::push_front(const int new_value)
	{
		Node* temp = new_node(new_value);

		temp->next = head_;
		head_ = temp;

		if (tail_ == NULL)
		{
			tail_ = head_;
		}

		++size_;
	}

	/*!
	 * \brief
	 * 	Appends a given value to the List.
	 *
	 * \param new_value
	 * 	The value to append.
	 */
	void List::push_back(const int new_value)
	{
		if (tail_ == NULL)
		{
			push_front(new_value);
		}
		else
		{
			Node* temp = new_node(new_value);

			tail_->next = temp;
			tail_ = tail_->next;

			++size_;
		}
	}

	/*!
	 * \brief
	 * 	Removes the first value in the list.
	 *
	 * \returns
	 * 	The value of the node in the List, -1 if the List is empty.
	 */
	int List::pop_front(void)
	{
		if (head_)
		{
			int temp = head_->data;
			Node* to_delete = head_;

			head_ = head_->next;

			delete to_delete;

			--size_;

			return(temp);
		}
		else
		{
			return(-1);
		}
	}

	/*!
	 * \brief
	 * 	Finds the current number of nodes in the List.
	 *
	 * \returns
	 * 	The number of nodes in the List.
	 */
	int List::size(void) const
	{
		return(size_);
	}

	/*!
	 * \brief
	 * 	Finds out whether the List is empty.
	 *
	 * \returns
	 * 	True if the List does not contain any nodes, false otherwise.
	 */
	bool List::empty(void) const
	{
		return(size_ == 0);
	}

	/*!
	 * \brief
	 * 	Deallocates all nodes in the List.
	 */
	void List::clear(void)
	{
		while(!empty())
		{
			pop_front();
		}
	}

	/*!
	 * \brief
	 * 	Finds the total number of Lists created in the program.
	 *
	 * \returns
	 * 	The number of times the constructors for Lists have been run.
	 */
	int List::object_count(void)
	{
		return(object_count_);
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// private methods

	/*!
	 * \brief
	 * 	Allocates a new Node pointer.
	 *
	 * \param data
	 * 	The value of the new Node.
	 *
	 * \returns
	 * 	A pointer to the newly-allocated Node.
	 */
	List::Node* List::new_node(int data) const
	{
		Node* temp = new Node;

		temp->data = data;
		temp->next = NULL;

		return temp;
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// non-member methods

////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
//  Purpose: Output the list into an ostream object
//   Inputs: os - ostream object
//           list - the List to output
//  Outputs: Returns an ostream object.
////////////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const List &list)
{
    // Start at the first node
  List::Node *pnode = list.head_;

    // Until we reach the end of the list
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data; // print the data in this node
    pnode = pnode->next;               // move to the next node
  }
  
  os << std::endl; // extra newline for readability
  return os;
}

} //namespace CS170
