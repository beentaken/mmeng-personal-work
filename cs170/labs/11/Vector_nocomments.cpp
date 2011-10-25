/* file_header_comment */

#include <iostream>  // cout
#include <cstdlib>   // abort
#include "Vector.h"

namespace CS170
{

/* function_header_comment */
Vector::Vector(void) : array_(0), size_(0), capacity_(0), allocs_(0)
{
}

/* function_header_comment */
Vector::Vector(const int *array, unsigned size)
:array_(NULL), size_(0), capacity_(0), allocs_(0)
{
	capacity_ = size;
	array_ = new int[capacity_];
	++allocs_;

	copy_array(array, size, array_);
	size_ = size;
}

/* function_header_comment */
Vector::Vector(const Vector &rhs)
:array_(NULL), size_(0), capacity_(0), allocs_(0)
{
	(*this) = rhs;
}

/* function_header_comment */
Vector::~Vector(void)
{
	clear();
}

/* function_header_comment */
bool Vector::empty(void) const
{
  return size_ == 0;
}

/* function_header_comment */
void Vector::push_back(int value)
{
	if (size() >= capacity())
	{
		grow();
	}

	array_[size_] = value;
	++size_;
}

/* function_header_comment */
void Vector::push_front(int value)
{
	insert(value, 0);
}

/* function_header_comment */
void Vector::pop_back(void)
{
	if (!empty())
	{
		--size_;
	}
}

/* function_header_comment */
void Vector::pop_front(void)
{
	if (!empty())
		remove(array_[0]);
}

/* function_header_comment */
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

/* function_header_comment */
void Vector::remove(int value)
{
	if (empty())
		return;

	const int index = find(value);

	copy_array(array_ + index + 1, size() - index, array_ + index);
	--size_;
}

/* function_header_comment */
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

/* function_header_comment */
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

/* function_header_comment */
void Vector::clear(void)
{
	delete[] array_;
	array_ = NULL;
	size_ = capacity_ = 0;
}

/* function_header_comment */
unsigned Vector::size(void) const
{
  return size_;
}

/* function_header_comment */
unsigned Vector::capacity(void) const
{
  return capacity_;
}

/* function_header_comment */
unsigned Vector::allocations(void) const
{
  return allocs_;
}

/* function_header_comment */
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

/* function_header_comment */
Vector& Vector::operator+=(const Vector& rhs)
{
	for (unsigned i = 0; i < rhs.size(); ++i)
	{
		push_back(rhs[i]);
	}

	return(*this);
}

/* function_header_comment */
Vector Vector::operator+(const Vector& rhs) const
{
	Vector temp(*this);
	temp += rhs;

	return(temp);
}

/* function_header_comment */
int Vector::operator[](unsigned index) const
{
	check_bounds(index);
	return(array_[index]);
}

/* function_header_comment */
int& Vector::operator[](unsigned index)
{
	check_bounds(index);
	return(array_[index]);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* function_header_comment */
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

/* function_header_comment */
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

/* function_header_comment */
void Vector::copy_array(const int *source, const unsigned size, int *destination)
{
	for (unsigned i = 0; i < size; ++i)
	{
		destination[i] = source[i];
	}
}

/* function_header_comment */
void Vector::reverse_copy_array(const int *source, const unsigned size, int *destination)
{
	for (int i = static_cast<int>(size); i >= 0; --i)
	{
		destination[i] = source[i];
	}
}

} // namespace CS170

