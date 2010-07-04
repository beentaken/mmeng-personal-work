/*****************************************************************************/
/*!
\file   array.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 4
\date   4 July, 2010
\brief
	Implements the functions needed to use the Array object.
*/
/*****************************************************************************/

#include "array.h"

/* \brief Constructor.
 *
 * \param array
 * 	A simple array to build the initial elements of the Array out of.
 *
 * \param _size
 * 	The maximum size of the array.
 *
 * \param _pElementFactory
 * 	The factory to use to generate Array items.
 */
CS225::Array::Array(int * array, 
		unsigned int _size, 
		const ElementFactory* _pElementFactory
		) 
	: data(new AbstractElement*[_size]),size(_size),
		pElementFactory(_pElementFactory),
		reference_counter(new unsigned int(1))
{
	for (unsigned int i=0;i<size;++i)
	{
		//create Element with id = 1 (that is Element1 )
		data[i] = pElementFactory->MakeElement( 1, array[i] );
	}
}

/* \brief Copy constructor.
 *
 * Performs a shallow copy of the various elements and ensures that the reference counter
 * is updated appropriately.
 *
 * \param rhs
 * 	The Array to copy from.
 */
CS225::Array::Array(const Array &rhs)
	: data(rhs.data), size(rhs.size), pElementFactory(rhs.pElementFactory),
		reference_counter(rhs.reference_counter)
{
	++(*reference_counter);
}

/* \brief Destructor.
 *
 * Ensures that the reference counter is consistent.
 *
 * If there are no other references to the data, the data is deallocated.
 */
CS225::Array::~Array(void)
{
	removeReference();
}

/* \brief Helper function for destructor and similar processes.
 *
 * Decrements the reference counter, making it safe to reassign the data
 * pointer consistently, and removes data if this object held the last
 * reference to the data.
 */
void CS225::Array::removeReference(void)
{
	if ((*reference_counter) > 1)
	{
		--(*reference_counter);
	}
	else /* No other references, safe to deallocate data. */
	{
		for (unsigned int i(0); i < size; ++i)
		{
			delete(data[i]);
		}
		delete[] data;
		delete reference_counter;
	}
}

/* \brief Assignement operator.
 *
 * Does a shallow copy of the data in the provided Array and updates
 * the reference counter as appropriate.
 *
 * \param rhs
 * 	The Array to copy.
 *
 * \return
 * 	A reference to the modified current array.
 */
CS225::Array& CS225::Array::operator=(const Array &rhs)
{
	if (this != &rhs)
	{
		removeReference();

		data = rhs.data;
		reference_counter = rhs.reference_counter;
		size = rhs.size;
		pElementFactory = rhs.pElementFactory;

		++(*reference_counter);
	}

	return(*this);
}

/* \brief Gets the value of the Array at the specified index.
 *
 * \param pos
 * 	The index of the value to obtain.
 *
 * \return
 * 	The value stored at the index specified.
 */
int CS225::Array::Get(unsigned int pos) const
{
	return data[pos]->Get();
}

/* \brief Sets the value of the Array at the specified index.
 *
 * \param id
 * 	The ID of the type that the element should be.
 *
 * \param pos
 * 	The index to create the item at.
 * 
 * \param value
 * 	The value of the element to create.
 */
void CS225::Array::Set(int id, int pos, int value)
{ 
	deepCopy();
	//setter will delete the old and create new 
	//slightly inefficient if new and old have the same type
	delete data[pos];
	data[pos] = pElementFactory->MakeElement(id,value); 
}

/* \brief Prints out the contents of the Array.
 */
void CS225::Array::Print() const
{
	for (unsigned int i=0;i<size;++i) data[i]->Print(); 
	std::cout << std::endl;
}

/* \brief Performs a deep copy of the data in the Array object.
 */
void CS225::Array::deepCopy(void)
{
	if ((*reference_counter) > 1) /* No need to deep copy if we're the only owner. */
	{
		AbstractElement** newData = new AbstractElement*[size];

		for (unsigned int i(0); i < size; ++i)
		{
			newData[i] = data[i]->clone();
		}

		data = newData;
		--(*reference_counter);
		reference_counter = new unsigned int(1);

	}
}

