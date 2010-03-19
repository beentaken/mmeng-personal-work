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

template <typename T>
T* remove(T *current, const T *end, const T &value)
{
	T *first_swap = current;

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

template <typename T>
int count(const T *current, const T *end, const T &item)
{
	int counter = 0;

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

template <typename T>
void fill(T *current, const T *end, const T &value)
{
	while (current != end)
	{
		*current = value;

		++current;
	}
}

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

template <typename T>
T *min_element(T *current, T *end)
{
	T *minimum = current;
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

template <typename T>
T *max_element(T *current, T *end)
{
	T *maximum = current;
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

template <typename T>
T sum(const T *current, const T *end)
{
	T sum = 0;

	while(current != end)
	{
		sum += *current;
		++current;
	}

	return(sum);
}

