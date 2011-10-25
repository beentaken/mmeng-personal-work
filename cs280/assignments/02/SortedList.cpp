#ifdef MARCUS_DEBUG
#include <iostream>
#endif

/************************************
 * General utilities.
 */

namespace
{
	/*!\brief Swaps two values around.
	 *
	 * Uses a single temporary variable.
	 *
	 * \param first
	 * 	The first value to swap.
	 *
	 * \param second
	 * 	The value to swap with the first.
	 */
	template<typename T>
		void swap_items(T& first, T& second)
		{
			T temp = first;
			first = second;
			second = temp;
		}
}

/************************************
 * Iterator stuff!
 */

/*!\brief Constructor.
 *
 * Constructs a new iterator and points it to the given internal Node of the SortedList.
 */
template<typename T, typename Pred>
SortedList<T, Pred>::const_iterator::const_iterator(typename SortedList<T, Pred>::Node* p)
	:current_(p)
{
}

/*!\brief Overloaded dereference operator for the iterator.
 *
 * \return A constant representing the value of the node pointed to by the iterator.
 */
template<typename T, typename Pred>
const T& SortedList<T, Pred>::const_iterator::operator*() const
{
	return(current_->Data);
}

/*!\brief Overloaded pre-increment operator for the iterator.
 *
 * Moves the frame one Node forward.
 *
 * Behavior is undefined if used on an iterator already pointing at the end of the list.
 *
 * \return A reference to the iterator.
 */
template<typename T, typename Pred>
typename SortedList<T, Pred>::const_iterator& SortedList<T, Pred>::const_iterator::operator++()
{
	current_ = current_->Next;
	return(*this);
}

/*!\brief Overloaded pre-decrement operator for the iterator.
 *
 * Moves the frame one Node backwards.
 *
 * Behavior is undefined if used when already one past the head of the list.
 *
 * \return A reference to the iterator.
 */
template<typename T, typename Pred>
typename SortedList<T, Pred>::const_iterator& SortedList<T, Pred>::const_iterator::operator--()
{
	current_ = current_->Prev;
	return(*this);
}

/*!\brief Overloaded comparison operator.
 *
 * \return False if the rhs points to the same Node that this does, true otherwise.
 */
template<typename T, typename Pred>
bool SortedList<T, Pred>::const_iterator::operator!=(const typename SortedList<T, Pred>::const_iterator &rhs) const
{
	return(current_ != rhs.current_);
}

/*!\brief Gets an iterator pointing to the start of the SortedList.
 *
 * \return An iterator pointing to the head of the SortedList.
 */
template<typename T, typename Pred>
typename SortedList<T, Pred>::const_iterator SortedList<T, Pred>::begin() const
{
	return(SortedList<T, Pred>::const_iterator(head_->Next));
}

/*!\brief Gets an iterator pointing to one past the end of the SortedList.
 *
 * \return An iterator pointing one past the end of the SortedList.
 */
template<typename T, typename Pred>
typename SortedList<T, Pred>::const_iterator SortedList<T, Pred>::end() const
{
	return(SortedList<T, Pred>::const_iterator(tail_));
}

/*!\brief Gets an iterator pointing to the end of the SortedList.
 *
 * \return An iterator pointing to the end of the SortedList.
 */
template<typename T, typename Pred>
typename SortedList<T, Pred>::const_iterator SortedList<T, Pred>::rbegin() const
{
	return(SortedList<T, Pred>::const_iterator(tail_->Prev));
}

/*!\brief Gets an iterator pointing to one past the start of the SortedList.
 *
 * \return An iterator pointing to one past the start of the SortedList.
 */
template<typename T, typename Pred>
typename SortedList<T, Pred>::const_iterator SortedList<T, Pred>::rend() const
{
	return(SortedList<T, Pred>::const_iterator(head_));
}


/*!\brief Basic constructor.
 *
 * \param sorter
 * 	A functor that takes two arguments and returns true if the two objects are in order.
 *
 * \param Allocator
 * 	A memory allocator to use if the user wishes to. Can be set to NULL, in which case
 * 	an internal allocator will be used.
 *
 * \param SharedAllocator
 * 	If true, this SortedList will share its allocator with copies of itself.
 */
template <typename T, typename Pred>
SortedList<T, Pred>::SortedList(Pred sorter, ObjectAllocator *Allocator, bool SharedAllocator)
:objAllocator_(Allocator), sorter_(sorter), shareAllocator_(SharedAllocator), head_(NULL), tail_(NULL), size_(0)
{
	// Let's get a working allocator...
	if (objAllocator_ == NULL)
	{
		OAConfig new_config(true); // Use CPP builtin mem manager.

		try
		{
			objAllocator_ = createAllocator(new_config);
		}
		catch(OAException &)
		{
			throw(SortedListException(SortedListException::E_NO_MEMORY, "List Constructor: Out of memory!"));
		}
	}
	else
	{
		freeAllocator_ = false;
	}

	// Now to set up initial dummy head and tail nodes.
	// Note that both head and tail will have garbage data in all fields aside
	// from their Next and Prev pointers! Accessing that data will result
	// in undefined behavior!
/*	head_ = allocNode();
	tail_ = allocNode(); */

	head_ = createNode(0);
	tail_ = createNode(0);

	// Everything's good, link'em.
	head_->Prev = NULL;
	head_->Next = tail_;

	tail_->Prev = head_;
	tail_->Next = NULL;
}

/*!\brief Copy constructor.
 *
 * \param rhs
 * 	The SortedList to copy from.
 */
template <typename T, typename Pred>
SortedList<T, Pred>::SortedList(const SortedList<T, Pred> &rhs) throw(SortedListException)
	:size_(0)
{
	if (rhs.shareAllocator_)
	{
		shareAllocator_ = true;
		freeAllocator_ = false;
		objAllocator_ = rhs.objAllocator_;
	}
	else
	{
		shareAllocator_ = false;
		OAConfig new_config(true); // Use CPP mem manager.
		objAllocator_ = createAllocator(new_config);
	}

	sorter_ = rhs.sorter_;

	// Build dummy head and tail nodes.
/*	head_ = allocNode();
	tail_ = allocNode();*/

	head_ = createNode(0);
	tail_ = createNode(0);

	// Everything's good, link'em.
	head_->Prev = NULL;
	head_->Next = tail_;

	tail_->Prev = head_;
	tail_->Next = NULL;

	copyNodes(rhs);
}

/*!\brief Destructor.
 *
 * Destructifies things.
 */
template <typename T, typename Pred>
SortedList<T, Pred>::~SortedList() throw()
{
	destroyAllNodes(head_);
	if (freeAllocator_)
	{
		destroyAllocator();
	}
}

/*!\brief Overloaded assignment operator.
 *
 * Copies the values in all of the nodes in the rhs to the current SortedList.
 *
 * The current Sortedlist will inherit the allocator sharing settings from the rhs.
 *
 * \param rhs
 * 	The SortedList to copy from.
 *
 * \return A reference to the current SortedList.
 */
template <typename T, typename Pred>
SortedList<T, Pred>& SortedList<T, Pred>::operator=(const SortedList &rhs) throw(SortedListException)
{
	// Special case, check for self-assignment and short circuit if true.
	if (this == &rhs)
	{
		return(*this);
	}

	if (rhs.shareAllocator_)
	{
		// We may have to get rid of an existing allocator.
		if (freeAllocator_)
		{
			destroyAllocator();
		}

		freeAllocator_ = false;
		shareAllocator_ = true;
		objAllocator_ = rhs.objAllocator_;
	}
	else
	{
		// Well, we already have an existing allocator, so...
		// I don't think we want to create a new one.
		// So, use an old one.
		shareAllocator_ = false;
//		OAConfig new_config(true); // Use CPP mem manager.
//		objAllocator_ = createAllocator(new_config);
	}

	sorter_ = rhs.sorter_;

	// Gank everything!
	destroyAllNodes(head_);
	// Build dummy head and tail nodes.
/*	head_ = allocNode();
	tail_ = allocNode();*/

	head_ = createNode(0);
	tail_ = createNode(0);

	// Everything's good, link'em.
	head_->Prev = NULL;
	head_->Next = tail_;

	tail_->Prev = head_;
	tail_->Next = NULL;

	copyNodes(rhs);
	// All done.
	
	return(*this);
}

/*!\brief Pushes a value on to the back of the SortedList.
 *
 * Will not resort the List, the value may be out of place until the next sort is called.
 *
 * \param value
 * 	The value to append to the SortedList.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::push_back(const T& value) throw(SortedListException)
{
	Node* temp = createNode(value);

	tail_->Prev->Next = temp;
	temp->Prev = tail_->Prev;
	tail_->Prev = temp;
	temp->Next = tail_;

	++size_;
}

/*!\brief Inserts a value into the SortedList in a proper sorted position.
 *
 * Does NOT work by pushing the value on to the list, and then sorting.
 * The value is inserted in sorted position.
 *
 * \param value
 * 	The value to insert into the SortedList.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::insert(const T& value) throw (SortedListException)
{
	insertNode(head_->Next, value);
	++size_;
}

/*!\brief Obtains the current size of the SortedList.
 *
 * \return The size of the SortedList.
 */
template <typename T, typename Pred>
unsigned SortedList<T, Pred>::size() const throw()
{
	return(size_);
}

/*!\brief Clears all the data from the current SortedList.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::clear() throw()
{
	// What are we doing here when size is 0 anyways?
	if (size_ == 0)
	{
		return;
	}
	tail_->Prev->Next = NULL;

	destroyAllNodes(head_->Next);

	head_->Next = tail_;
	tail_->Prev = head_;
	size_ = 0;
}

/*!\brief Sorts the list.
 *
 * Uses a selection sort algorithm to do so in-place.
 */
template <typename T, typename Pred>
template <typename Sorter>
void SortedList<T, Pred>::selection_sort(Sorter sorter)
{
	SortedList<T, Pred>::Node* current = head_->Next;
	
	while(current != tail_)
	{
		SortedList<T, Pred>::Node* temp = findMinNode(current, current, sorter);
		swapNodes(current, temp);
		current = temp->Next;
	}
}

/*!\brief Sorts the list.
 *
 * Uses an in-place mergesort algorithm.
 */
template <typename T, typename Pred>
template <typename Sorter>
void SortedList<T, Pred>::merge_sort(Sorter sorter)
{
	// TODO: STUB!
	// Short circuit if there's nothing to sort.
	if (size_ <= 1U)
		return;

	merge_sort_helper(head_->Next, size_, sorter);
}

/*!\brief Returns whether the extra credit is implemented.
 *
 * \return True if extra credit is implemented, false otherwise.
 */
template <typename T, typename Pred>
bool SortedList<T, Pred>::ImplementedExtraCredit()
{
	return(false);
}

/*!\brief Obtains the size, in bytes, of each Node.
 *
 * \return The size, in bytes, of a Node.
 */
template <typename T, typename Pred>
unsigned SortedList<T, Pred>::nodesize()
{
	return(sizeof(SortedList<T, Pred>::Node));
}

/*!\brief Helper function that allocates the memory for a single Node.
 *
 * Note that it does not run constructors or any such thing.
 *
 * \return A pointer to the newly allocated memory.
 */
template <typename T, typename Pred>
typename SortedList<T, Pred>::Node* SortedList<T, Pred>::allocNode() throw(SortedListException)
{
	try
	{
		return(reinterpret_cast<Node*>(objAllocator_->Allocate()));
	}
	catch(OAException &)
	{
		throw(SortedListException(SortedListException::E_NO_MEMORY, "Cannot allocate a new node."));
	}
}

/*!\brief Allocates and initializes a new Node to the given value.
 *
 * \return A pointer to the newly constructed Node.
 */
template <typename T, typename Pred>
typename SortedList<T, Pred>::Node* SortedList<T, Pred>::createNode(const T& value) throw(SortedListException)
{
	return(new(allocNode()) SortedList<T, Pred>::Node(value));
}

/*!\brief Creates an allocator.
 *
 * Will set a flag ensuring the allocator will be deleted when this SortedList
 * goes out of scope.
 *
 * \param new_config
 * 	The configuration for the new allocator.
 *
 * \return A pointer to the newly created allocator.
 */
template <typename T, typename Pred>
ObjectAllocator* SortedList<T, Pred>::createAllocator(OAConfig &new_config) throw(SortedListException)
{
	try
	{
		freeAllocator_ = true;
		return(new ObjectAllocator(sizeof(SortedList<T, Pred>::Node), new_config));
	}
	catch (std::bad_alloc &)
	{
		throw(SortedListException(SortedListException::E_NO_MEMORY, "Could not allocate new ObjectAllocator."));
	}
}

/*!\brief Destroys all the nodes starting from the given Node and ending when
 * it reaches NULL.
 *
 * \param current
 * 	The current Node pointer being examined for deletion.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::destroyAllNodes(typename SortedList<T, Pred>::Node* current)
{
	while (current != NULL)
	{
		SortedList<T, Pred>::Node* temp = current->Next;
		// TODO: This breaks things. WHY?!?
		current->~Node();
		objAllocator_->Free(current);

		current = temp;
	}
}

/*!\brief Destroys the current ObjectAllocator.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::destroyAllocator()
{
	delete objAllocator_;
}

/*!\brief Copies the Node list from the given SortedList into the current
 * SortedList.
 *
 * For an exact value copy, it will assume that the current list is, in fact,
 * empty outside of the dummy head and tail.
 *
 * Requires the dummy head and tail to function properly.
 *
 * \param rhs
 * 	The SortedList to copy values out from.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::copyNodes(const SortedList<T, Pred>& rhs)
{
	SortedList<T, Pred>::const_iterator iter = rhs.begin();

	while (iter != rhs.end())
	{
		push_back(*iter);
		++iter;
	}
}

/*!\brief Finds out where a given value should be in the list given sorted order, and inserts it.
 *
 * This is a helper function and should not be called by anything not inside this class.
 *
 * Assumes that at minimum, the head and tail dummy pointers are defined.
 *
 * \param current
 * 	The current Node pointer the function is examining.
 *
 * \param value
 * 	The value to insert.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::insertNode(typename SortedList<T, Pred>::Node* current, const T& value)
{
	if (current != tail_ && sorter_(current->Data, value))
	{
		insertNode(current->Next, value);
	}
	else
	{
		SortedList<T, Pred>::Node *temp = createNode(value);

		temp->Prev = current->Prev;
		temp->Next = current;

		current->Prev->Next = temp;
		current->Prev = temp;
	}
}

/*!\brief Swaps two given Nodes.
 *
 * Behavior may be bad if used on Nodes in different SortedLists.
 *
 * This function will assume that the given Node structs are valid.
 *
 * \param first
 * 	The first Node to swap.
 *
 * \param second
 * 	The Node to swap the first with.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::swapNodes(typename SortedList<T, Pred>::Node* first, typename SortedList<T, Pred>::Node* second)
{
	// Need to swap 4 sets of pointers.
	// Note: Always swap adjacent Node pointers before the pointers to the
	// adjacent Nodes themselves.
	swap_items(first->Prev->Next, second->Prev->Next);
	swap_items(first->Prev, second->Prev);
	swap_items(first->Next->Prev, second->Next->Prev);
	swap_items(first->Next, second->Next);
}

/*!\brief Finds the Node with the minimum value by criterion listed in the provided functor.
 *
 * \param current
 * 	The current node being examined.
 *
 * \param min
 * 	The current minimum.
 *
 * \param sorter
 * 	The functor to use to determine what the order is.
 *
 * \return A pointer to the Node containing the smallest value.
 */
template <typename T, typename Pred>
template <typename Sorter>
typename SortedList<T, Pred>::Node* SortedList<T, Pred>::findMinNode(typename SortedList<T, Pred>::Node* current, typename SortedList<T, Pred>::Node* min, const Sorter &sorter)
{
	if (current != tail_)
	{
		if (sorter(current->Data, min->Data))
		{
			return(findMinNode(current->Next, current, sorter));
		}
		else
		{
			return(findMinNode(current->Next, min, sorter));
		}
	}

	return(min);
}

/*!\brief Advances the node the given number of steps.
 *
 * This function will not go farther than one past the end, no matter what.
 *
 * \param current
 * 	The node that is advancing.
 *
 * \param to_advance
 * 	The number of nodes forward to advance by.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::advanceNode(typename SortedList<T, Pred>::Node* &current, unsigned to_advance)
{
	for (unsigned i = 0; i < to_advance && current != tail_; ++i)
	{
		current = current->Next;
	}
}

/*!\brief Removes a Node from the list, but does not destroy it.
 *
 * Note that the removed Node's Prev and Next pointers are no longer
 * guarunteed to be useful.
 *
 * Also, don't run this on the head or tail dummies, bad things will happen.
 *
 * \param to_remove
 * 	The Node to remove from the list.
 *
 * \return A pointer to the removed Node.
 */
template <typename T, typename Pred>
typename SortedList<T, Pred>::Node* SortedList<T, Pred>::extractNode(typename SortedList<T, Pred>::Node* to_remove)
{
	to_remove->Prev->Next = to_remove->Next;
	to_remove->Next->Prev = to_remove->Prev;

	return(to_remove);
}

/*!\brief Inserts a Node after the given Node.
 *
 * \param to_insert
 * 	The Node to insert.
 *
 * \param position
 * 	The Node to insert after.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::insertAfterNode(typename SortedList<T, Pred>::Node* to_insert, typename SortedList<T, Pred>::Node* position)
{
	to_insert->Next = position->Next;
	to_insert->Prev = position;

	position->Next->Prev = to_insert;
	position->Next = to_insert;
}

/*!\brief Moves a Node after the specified destination Node.
 *
 * \param to_move
 * 	The Node to shuffle.
 *
 * \param destination
 * 	The Node to put the moved Node after.
 */
template <typename T, typename Pred>
void SortedList<T, Pred>::moveNode(typename SortedList<T, Pred>::Node* to_move, typename SortedList<T, Pred>::Node* destination)
{
	insertAfterNode(extractNode(to_move), destination);
}

/*!\brief Merges two ordered lists into one ordered list.
 *
 * The lists do not have to be the same size.
 *
 * \param list1
 * 	The first list to merge.
 *
 * \param length1
 * 	The length of the first list to merge.
 *
 * \param list2
 * 	The second list to merge.
 *
 * \param length2
 * 	The length of the second list to merge.
 *
 * \param sorter
 * 	The functor used to check for ordering.
 *
 * \return A pointer to the start of the new list.
 */
template <typename T, typename Pred>
template <typename Sorter>
typename SortedList<T, Pred>::Node* SortedList<T, Pred>::merge_lists(typename SortedList<T, Pred>::Node* list1, unsigned length1, typename SortedList<T, Pred>::Node* list2, unsigned length2, const Sorter &sorter)
{
	unsigned i = 0, j = 0;
	SortedList<T, Pred>::Node* front = sorter(list1->Data, list2->Data) ? list1 : list2;

	// I will arbitrarily decide to just shove everything into list1.
	while (i < length1 && j < length2 && list2 != tail_)
	{
		if (sorter(list1->Data, list2->Data))
		{
			list1 = list1->Next;
			++i;
		}
		else
		{
			SortedList<T, Pred>::Node* temp = list2;
			list2 = list2->Next;
			++j;

			moveNode(temp, list1->Prev);
		}
	}

	// If there's any left over, append the rest.
	// If list1 is longer it's already in order and junk, so we
	// don't worry about it at all.
/*	while (j < length2 && list2 != tail_)
	{
		SortedList<T, Pred>::Node* temp = list2;
		list2 = list2->Next;
		++j;

		moveNode(temp, list1->Prev);
		list1 = list1->Next;
	} */
	// Aaaaaactually, all that is unnecessary.
	// In mergesort, the right block is always adjacent to the left block.
	// So, there's no point worrying about it, it's already appended for
	// your convenience.

	// The two should be stuck together now.
	// This should work because lists we're comparing should all be
	// adjacent to each other.
	return(front);
}

/*!\brief A helper function to make the mergesort work.
 *
 * Breaks down a list into appropriately-sized chunks, feeds them into a merge
 * algo, them reconstitutes them by adding water.
 *
 * \param current
 * 	A pointer to the start of the current Node segment.
 *
 * \param chunk_size
 * 	How much we're looking at this time around.
 *
 * \param sorter
 * 	The functor used to determine the order of elements.
 *
 * \return A pointer to the start of the range that was just assessed.
 */
template <typename T, typename Pred>
template <typename Sorter>
typename SortedList<T, Pred>::Node* SortedList<T, Pred>::merge_sort_helper(typename SortedList<T, Pred>::Node* current, unsigned chunk_size, const Sorter &sorter)
{
	if (current != tail_ && chunk_size > 1)
	{
		SortedList<T, Pred>::Node* temp = current;
		advanceNode(temp, chunk_size / 2);
		// Mergesort the left, mergesort the right, and merge the results!
		return(merge_lists(merge_sort_helper(current, chunk_size / 2, sorter),
				   chunk_size / 2,
				   merge_sort_helper(temp, chunk_size - (chunk_size / 2), sorter),
				   chunk_size - (chunk_size / 2),
				   sorter));
	}
	
	return(current);
}

#ifdef MARCUS_DEBUG
template<typename T, typename Pred>
void SortedList<T, Pred>::print_nodes(SortedList<T, Pred>::Node* current, unsigned length)
{
	for (unsigned i = 0; i < length && current != tail_; ++i)
	{
		std::cerr << current->Data << ' ';
		current = current->Next;
	}
	std::cerr << std::endl;
}
#endif

