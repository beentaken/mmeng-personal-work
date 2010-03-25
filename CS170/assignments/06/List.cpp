/* file_header_comment */

namespace CS170
{

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// static members

template <typename T>
int List<T>::Node::node_count_ = 0;

/* function_header_comment */
template <typename T>
int List<T>::node_count(void)
{
  return Node::node_count_;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// List::Node methods

/* function_header_comment */
template <typename T>
List<T>::Node::Node(const T &value) : data(value)
{
  node_count_++;
}

/* function_header_comment */
template <typename T>
List<T>::Node::~Node(void)
{
  node_count_--;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// public methods

/* function_header_comment */
template <typename T>
List<T>::List(void)
{
	head_ = tail_ = NULL;
	size_ = 0;
}

/* function_header_comment */
template <typename T>
List<T>::List(const List &list)
{
	head_ = tail_ = NULL;
	size_ = 0;

	*this = list;
}

/* function_header_comment */
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

/* function_header_comment */
template <typename T>
List<T>::~List(void)
{
	clear();
}

/////////////////////////////////////////////////////////////////////////
// Function: List::clear
//  Purpose: Removes all of the nodes in the list.
//   Inputs: None
//  Outputs: None
/////////////////////////////////////////////////////////////////////////
/* function_header_comment */
template <typename T>
void List<T>::clear(void)
{
  while (!empty())
    pop_front();
}

/* function_header_comment */
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

/* function_header_comment */
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

/* function_header_comment */
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

/* function_header_comment */
template <typename T>
T List<T>::front(void) const
{
	return(head_->data);
}

/* function_header_comment */
template <typename T>
int List<T>::size(void) const
{
	return(size_);
}

/* function_header_comment */
template <typename T>
bool List<T>::empty(void) const
{
	return(!size_);
}

/* function_header_comment */
template <typename T>
List<T>& List<T>::operator=(const List &rhs)
{
	clear();

	for (int i = 0; i < rhs.size(); ++i)
	{
		push_back(rhs[i]);
	}

	return(*this);
}

/* function_header_comment */
template <typename T>
List<T> List<T>::operator+(const List& rhs) const
{
	List temp(*this);

	temp += rhs;

	return(temp);
}

/* function_header_comment */
template <typename T>
List<T>& List<T>::operator+=(const List& rhs)
{
	for (int i = 0; i < rhs.size(); ++i)
	{
		push_back(rhs[i]);
	}

	return(*this);
}

/* function_header_comment */
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

/* function_header_comment */
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

/////////////////////////////////////////////////////////////////////////
// Function: new_node
//  Purpose: Allocate a node, initialize the data and next pointer
//   Inputs: data - the data to put in the node
//  Outputs: A pointer to the node
/////////////////////////////////////////////////////////////////////////
/* function_header_comment */
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

/////////////////////////////////////////////////////////////////////////
// Function: operator<<
//  Purpose: Output the list into an ostream object
//   Inputs:   os - ostream object to output to
//           list - the List to output
//  Outputs: The ostream object that was passed in.
/////////////////////////////////////////////////////////////////////////
/* function_header_comment */
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the top
  typename CS170::List<T>::Node *pnode = list.head_;

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  return os;
}

