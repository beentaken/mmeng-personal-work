/*****************************************************************************/
/*!
\file   Functions.cpp
\author Marcus Meng
\par    email: marcus.meng@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment 5
\date   March 24, 2010
\brief
	This file contains the implementations for various range-based
	templated functions.

Hours spent on this assignment: 1

Specific portions that gave you the most trouble:

N/A

*/
/*****************************************************************************/

#include <iostream> // cout, endl

/******************************************************************************/
/*!
  \brief
    Swaps two objects. There is no return value but the two objects are
    swapped in place.
  
  \param left
    The first object to swap.
  
  \param right
    The second object to swap.
*/
/******************************************************************************/
template <typename T> 
void swap(T &left, T &right)
{
  T temp(right); // need a temporary copy
  right = left;
  left = temp;
}

/*****************************************************************************/
/*!
\brief
	Displays, using cout, all the elements in the provided range.

\param start
	The beginning of the range.

\param end
	The end of the range.
*/
/*****************************************************************************/
template <typename T>
void display(const T *start, const T *end)
{
	while (start != end)
	{
		std::cout << *start;
		if (start + 1 != end)
		{
			std::cout << ", ";
		}
		++start;
	}

	std::cout << std::endl;
}

/*****************************************************************************/
/*!
\brief
	Swaps the given ranges of two arrays.

\param current
	The starting position in the first array.

\param end
	The ending position in the first array.

\param to_swap
	The start of the array to swap into.
*/
/*****************************************************************************/
template <typename T>
void swap_ranges(T *current, const T *end, T* to_swap)
{
	while (current != end)
	{
		swap(*current, *to_swap);
		++current;
		++to_swap;
	}
}

/*****************************************************************************/
/*!
\brief
	Removes all occurances of the provided value from the given range.

\param current
	The start of the range.

\param end
	The end of the given range.

\param value
	The value to remove.

\return
	A pointer to the new end of the range.
*/
/*****************************************************************************/
template <typename T>
T* remove(T *current, const T *end, const T &value)
{
	T *first_swap = current; // Keeps track of the next swap position.

	while (current != end)
	{
		if (*current != value)
		{
			*first_swap = *current;
			++first_swap;
		}

		++current;
	}

	return(first_swap);
}

/*****************************************************************************/
/*!
\brief
	Counts the number of occurances of the given item in the range.

\param current
	A pointer to the start of the range.

\param end
	A pointer to the end of the range.

\param item
	The item to watch for.

\return
	The number of times item was seen in the range.
*/
/*****************************************************************************/
template <typename T>
int count(const T *current, const T *end, const T &item)
{
	int counter = 0; // Keep track of the number of times we've seen item.

	while (current != end)
	{
		if (*current == item)
		{
			++counter;
		}

		++current;
	}

	return(counter);
}

/*****************************************************************************/
/*!
\brief
	Finds the given item in the given range.

\param current
	The start of the range.

\param end
	The end of the range.

\param item
	The value of the item to look for.

\return
	A pointer to the item containing the value given.
*/
/*****************************************************************************/
template <typename T1, typename T2>
T1 *find(T1 *current, T1 *end, const T2 &item)
{
	while (current != end)
	{
		if (*current == item)
		{
			return(current);
		}
		++current;
	}

	return(current);
}

/*****************************************************************************/
/*!
\brief
	Copies the contents of a given range into a destination array.

	Does NOT check the destination array to prevent overflows.

\param current
	The start of the range to copy.

\param end
	The end of the range to copy.

\param destination
	The start of the array to copy to.

\return
	A pointer to the end of the newly-copied range.
*/
/*****************************************************************************/
template <typename T>
T *copy(const T *current, const T *end, T* destination)
{
	while (current != end)
	{
		*destination = *current;
		++destination;
		++current;
	}

	return(destination);
}

/*****************************************************************************/
/*!
\brief
	Fills a range with a given value.

\param current
	The start of the range to fill.

\param end
	The end of the range to fill.

\param value
	The value to fill the range with.
*/
/*****************************************************************************/
template <typename T>
void fill(T *current, const T *end, const T &value)
{
	while (current != end)
	{
		*current = value;

		++current;
	}
}

/*****************************************************************************/
/*!
\brief
	Replaces all occurances of a given value in a range with a new value.

\param current
	The start of the range to run the replacements on.

\param end
	The end of the range.

\param old_item
	The value to replace.

\param new_item
	The value to replace the old_item with.
*/
/*****************************************************************************/
template <typename T>
void replace(T *current, const T *end, const T &old_item, const T &new_item)
{
	while (current != end)
	{
		if (*current == old_item)
		{
			*current = new_item;
		}

		++current;
	}
}

/*****************************************************************************/
/*!
\brief
	Finds the smallest element in a range.

	Requires that the comparison operators exist for the type being
	examined.

\param current
	The start of the range to inspect.

\param end
	The end of the range to inspect.

\return
	A pointer to the element containing the smallest value in the range.
*/
/*****************************************************************************/
template <typename T>
T *min_element(T *current, T *end)
{
	T *minimum = current; // Keep track of our current minimum.
	while (current != end)
	{
		if ((*minimum) > (*current))
		{
			minimum = current;
		}
		++current;
	}

	return(minimum);
}

/*****************************************************************************/
/*!
\brief
	Finds the largest value in a given range.

\param current
	The start of the range to inspect.

\param end
	The end of the range to inspect.

\return
	A pointer to the element holding the largest value in the range.
*/
/*****************************************************************************/
template <typename T>
T *max_element(T *current, T *end)
{
	T *maximum = current; // Keep track of our current maximum.
	while (current != end)
	{
		if (*maximum < *current)
		{
			maximum = current;
		}
		++current;
	}

	return(maximum);
}

/*****************************************************************************/
/*!
\brief
	Checks whether two ranges are equivilant.

	Does not check the second array past the size of the first array.

\param current
	The start of the range to inspect.

\param end
	The end of the range to inspect.

\param to_compare
	The range to compare to.

\return
	True if the inspected ranges are equal, false otherwise.
*/
/*****************************************************************************/
template <typename T1, typename T2>
bool equal(const T1 *current, const T1 *end, const T2 *to_compare)
{
	while (current != end)
	{
		if (*current != *to_compare)
		{
			return(false);
		}

		++current;
		++to_compare;
	}

	return(true);
}

/*****************************************************************************/
/*!
\brief
	Sums up the values in the range given.

\param current
	The start of the range to sum up.

\param end
	The end of the range to sum up.

\return
	The sum of all values contained in the range.
*/
/*****************************************************************************/
template <typename T>
T sum(const T *current, const T *end)
{
	T sum = 0; // An accumulator to track our running total.

	while(current != end)
	{
		sum += *current;
		++current;
	}

	return(sum);
}

