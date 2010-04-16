/*****************************************************************************/
/*!
\file   Vector.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Lab 11
\date   April 16, 2010
\brief
	This file contains the implementations for the various Vector member
	functions.

Hours spent on this assignment: 1

Specific portions that gave you the most trouble:

Figuring out when to use grow() and when to manually allocate stuff.

*/
/*****************************************************************************/

#include <iostream>  // cout
#include <cstdlib>   // abort
#include "Vector.h"

namespace CS170
{

/*****************************************************************************/
/*!
\brief
	Default constructor.
*/
/*****************************************************************************/
Vector::Vector(void) : array_(0), size_(0), capacity_(0), allocs_(0)
{
}

/*****************************************************************************/
/*!
\brief
	Constructs a new Vector from the given array of integers.

\param array
	The array containing the data to initialize the Vector to.

\param size
	The size of the array.
*/
/*****************************************************************************/
Vector::Vector(const int *array, unsigned size)
:array_(NULL), size_(0), capacity_(0), allocs_(0)
{
	capacity_ = size;
	array_ = new int[capacity_];
	++allocs_;

	copy_array(array, size, array_);
	size_ = size;
}

/*****************************************************************************/
/*!
\brief
	Copy constructor.

\param rhs
	The Vector containing the data to initialize the current object to.

\return
	Return_desc
*/
/*****************************************************************************/
Vector::Vector(const Vector &rhs)
:array_(NULL), size_(0), capacity_(0), allocs_(0)
{
	(*this) = rhs;
}

/*****************************************************************************/
/*!
\brief
	Destructor.
*/
/*****************************************************************************/
Vector::~Vector(void)
{
	clear();
}

/*****************************************************************************/
/*!
\brief
	Finds whether the current Vector is empty.

\return
	True if the current Vector is empty, false otherwise.
*/
/*****************************************************************************/
bool Vector::empty(void) const
{
  return size_ == 0;
}

/*****************************************************************************/
/*!
\brief
	Appends the given value to the Vector.

\param value
	The value to append to the Vector.
*/
/*****************************************************************************/
void Vector::push_back(int value)
{
	if (size() >= capacity())
	{
		grow();
	}

	array_[size_] = value;
	++size_;
}

/*****************************************************************************/
/*!
\brief
	Prepends a value to the current Vector.

\param value
	The value to prepend.
*/
/*****************************************************************************/
void Vector::push_front(int value)
{
	insert(value, 0);
}

/*****************************************************************************/
/*!
\brief
	Removes the last value in the Vector.
*/
/*****************************************************************************/
void Vector::pop_back(void)
{
	if (!empty())
	{
		--size_;
	}
}

/*****************************************************************************/
/*!
\brief
	Removes the first value in the vector.
*/
/*****************************************************************************/
void Vector::pop_front(void)
{
	if (!empty())
		remove(array_[0]);
}

/*****************************************************************************/
/*!
\brief
	Inserts a given value into the index provided.

\param value
	The value to insert.

\param position
	The index to insert the new value at.
*/
/*****************************************************************************/
void Vector::insert(int value, unsigned position)
{
	if (size() >= capacity())
	{
		grow();
	}

	reverse_copy_array(array_ + position, size() - position, array_ + position +1);
	array_[position] = value;
	++size_;
}

/*****************************************************************************/
/*!
\brief
	Removes the first occurance of a given value from the array.

\param value
	The value to remove.
*/
/*****************************************************************************/
void Vector::remove(int value)
{
	if (empty())
		return;

	const int index = find(value);

	copy_array(array_ + index + 1, size() - index, array_ + index);
	--size_;
}

/*****************************************************************************/
/*!
\brief
	Finds the index of the first occurance of the given value.

\param value
	The value to locate.

\return
	The index of the value provided, -1 if the value was not found.
*/
/*****************************************************************************/
int Vector::find(int value) const
{
	for (unsigned i = 0; i < size(); ++i)
	{
		if (value == array_[i])
		{
			return(i);
		}
	}

	return(-1); // I DUN CAN FIND NUMBAH.
}

/*****************************************************************************/
/*!
\brief
	Reallocates the capacity of the current Vector to match the actual
	size of the vector.
*/
/*****************************************************************************/
void Vector::pack(void)
{
	if (capacity() > size())
	{
		int *temp = array_;
		capacity_ = size_;
		array_ = new int[capacity_];
		++allocs_;

		for (unsigned i = 0; i < size_; ++i)
		{
			array_[i] = temp[i];
		}

		delete[] temp;
	}
}

/*****************************************************************************/
/*!
\brief
	Deallocates the current array and sets the various helper variables
	to a default.
*/
/*****************************************************************************/
void Vector::clear(void)
{
	delete[] array_;
	array_ = NULL;
	size_ = capacity_ = 0;
}

/*****************************************************************************/
/*!
\brief
	Finds the number of existing elements in the current Vector.

\return
	The number of elements in the Vector.
*/
/*****************************************************************************/
unsigned Vector::size(void) const
{
  return size_;
}

/*****************************************************************************/
/*!
\brief
	Finds the amount of units allocated in the current Vector.

\return
	The number of units allocated.
*/
/*****************************************************************************/
unsigned Vector::capacity(void) const
{
  return capacity_;
}

/*****************************************************************************/
/*!
\brief
	Finds the number of memory allocations performed by this object.

\return
	The number of memory allocations performed.
*/
/*****************************************************************************/
unsigned Vector::allocations(void) const
{
  return allocs_;
}

/*****************************************************************************/
/*!
\brief
	Overloaded assignment operator.

\param rhs
	The Vector containing data to assign to the current Vector.

\return
	A reference to the current Vector.
*/
/*****************************************************************************/
Vector& Vector::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		if (rhs.size() > capacity())
		{
			clear();
			capacity_ = rhs.size();
			array_ = new int[capacity()];
			++allocs_;
		}
		for (unsigned i = 0; i < rhs.size(); ++i)
			array_[i] = rhs[i];

		size_ = rhs.size();
	}

	return(*this);
}

/*****************************************************************************/
/*!
\brief
	Overloaded add-and-assign operator.

\param rhs
	The Vector containing the data to append to the current Vector.

\return
	A reference to the current Vector.
*/
/*****************************************************************************/
Vector& Vector::operator+=(const Vector& rhs)
{
	for (unsigned i = 0; i < rhs.size(); ++i)
	{
		push_back(rhs[i]);
	}

	return(*this);
}

/*****************************************************************************/
/*!
\brief
	Overloaded addition operator.

\param rhs
	The Vector containing information to append.

\return
	A new Vector containing the contents of the current and rhs Vectors.
*/
/*****************************************************************************/
Vector Vector::operator+(const Vector& rhs) const
{
	Vector temp(*this);
	temp += rhs;

	return(temp);
}

/*****************************************************************************/
/*!
\brief
	Overloaded index operator (const version).

\param index
	The index of the value to obtain.

\return
	A copy of the contents at that index.
*/
/*****************************************************************************/
int Vector::operator[](unsigned index) const
{
	check_bounds(index);
	return(array_[index]);
}

/*****************************************************************************/
/*!
\brief
	Overloaded index operator.

\param index
	The index of the value to get.

\return
	A reference to the value at the specified index.
*/
/*****************************************************************************/
int& Vector::operator[](unsigned index)
{
	check_bounds(index);
	return(array_[index]);
}

/*****************************************************************************/
/*!
\brief
	Runs a bubble sort on the Vector.

\returns
	A SortResult struct containing the number of swaps and compares done.
*/
/*****************************************************************************/
Vector::SortResult Vector::bubble_sort(void)
{
	SortResult to_return = {0, 0};
	bool sorted = false;
	for (unsigned i = 0; i < size() && !sorted; ++i)
	{
		sorted = true;
		for(unsigned j = 0; j < size() - 1 - i; ++j)
		{
			++to_return.compares;
			if (array_[j] > array_[j + 1])
			{
				swap(array_[j], array_[j+1]);
				++to_return.swaps;

				sorted = false;
			}
		}
	}

	return to_return;
}

/*****************************************************************************/
/*
\brief
	Runs a selection sort on the Vector.

\returns
	A SortResult struct containing the number of swaps and compares done.
*/
/*****************************************************************************/
Vector::SortResult Vector::selection_sort(void)
{
	SortResult to_return = {0, 0};
	for (unsigned i = 0; i < size(); ++i)
	{
		unsigned index_small = i;
		for (unsigned j = i + 1; j < size(); ++j)
		{
			++to_return.compares;
			if (array_[j] < array_[index_small])
			{
				index_small = j;
			}
		}

		if (i < index_small)
		{
			++to_return.swaps;
			swap(array_[i], array_[index_small]);
		}
	}

	return to_return;
}

/*****************************************************************************/
/*
\brief
	Finds an item in the Vector using a binary search.

\param value
	The item to search for.

\returns
	The index of the item in question.
*/
/*****************************************************************************/
int Vector::bsearch(int value) const
{
	unsigned low = 0, high = size();
	while (low < high)
	{
		const unsigned current = (low + high) / 2;

		if (array_[current] > value)
		{
			high = current;
		}
		else if (array_[current] < value)
		{
			low = current;
		}
		else
		{
			return(current);
		}
	}
	return -1;
}

/*****************************************************************************/
/*
\brief
	Reverses the internal array. O(n) time.
*/
/*****************************************************************************/
void Vector::reverse(void)
{
	for (unsigned i = 0; i < size() - i; ++i)
	{
		swap(array_[i], array_[size() - 1 - i]);
	}
}

/*****************************************************************************/
/*
\brief
	Swaps the data in this Vector with the data in another vector.
*/
/*****************************************************************************/
void Vector::swapv(Vector &other)
{
	swap(size_, other.size_);
	swap(capacity_, other.capacity_);
	swap(allocs_, other.allocs_);
	swap(array_, other.array_);
}

/*****************************************************************************/
/*
\brief
	Overloaded equality operator. Checks whether the size and contents
	of two vectors are equivalent.

\param rhs
	The Vector to compare to.

\return
	true if the size and contents of each Vector are equal, false
	otherwise.
*/
/*****************************************************************************/
bool Vector::operator==(const Vector &rhs) const
{
	if (size() != rhs.size())
		return false;

	for (unsigned i = 0; i < size(); ++i)
	{
		if (array_[i] != rhs[i])
			return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/*!
\brief
	Checks whether the specified index is valid within the current
	Vector.

\param index
	The index to check.
*/
/*****************************************************************************/
void Vector::check_bounds(unsigned index) const
{
    // Don't have to check for < 0 because index is unsigned
  if (index >= size_)
  {
    std::cout << "Attempting to access index " << index << ".";
    std::cout << " The size of the array is " << size_ << ".  Aborting...\n";
    std::abort();
  }
}

/*****************************************************************************/
/*!
\brief
	Doubles the capacity of the internally allocated array.
*/
/*****************************************************************************/
void Vector::grow(void)
{
	// Double the capacity
	capacity_ = (capacity_) ? capacity_ * 2 : 1;
	// Rest of the code here...

	int *new_array = new int[capacity()];

	copy_array(array_, size(), new_array);

	delete[] array_;

	array_ = new_array;

	++allocs_;
}

/*****************************************************************************/
/*!
\brief
	Copies the contents of a source array into a destination array.

\param source
	A pointer to the start of the array to copy from

\param size
	The number of elements to copy from the source.

\param destination
	A pointer to the start of the array to copy to.
*/
/*****************************************************************************/
void Vector::copy_array(const int *source, const unsigned size, int *destination)
{
	for (unsigned i = 0; i < size; ++i)
	{
		destination[i] = source[i];
	}
}

/*****************************************************************************/
/*!
\brief
	Copies the contents of a source array into a destination array
	starting from the last sequential value.

\param source
	The source array to copy from.

\param size
	The number of elements to copy from the source.

\param destination
	A pointer to the start of the array to copy to.
*/
/*****************************************************************************/
void Vector::reverse_copy_array(const int *source, const unsigned size, int *destination)
{
	for (int i = static_cast<int>(size); i >= 0; --i)
	{
		destination[i] = source[i];
	}
}

template <typename T>
void Vector::swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

} // namespace CS170

