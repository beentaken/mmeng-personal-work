#include "element2.h"

/* \brief Constructor.
 *
 * \param _val
 * 	The value to set the newly created element to.
 */
CS225::Element2::Element2(int _val) : p_val(new int(_val))
{
	// I do... nothing! HAHAHAHA.
}

/* \brief Copy constructor.
 *
 * \param rhs
 * 	The Element2 to take the value from.
 */
CS225::Element2::Element2(const Element2& rhs) 
	: AbstractElement(), p_val(new int(*rhs.p_val)) 
{
}

/* \brief Assignment operator.
 *
 * \param rhs
 * 	The Element2 to get the value to assign to the current
 * 	object from.
 *
 * \return
 * 	A reference to the current, modified element.
 */
CS225::Element2& CS225::Element2::operator=(const Element2& rhs)
{
	if (this!=&rhs)
	{
		delete p_val;
		p_val = new int(*rhs.p_val);
	}
	return *this;
}

/* \brief Gets the value of the current Element.
 *
 * \return
 * 	The value of the current element.
 */
int CS225::Element2::Get() const
{
	return *p_val;
}

/* \brief Prints the value of the current element.
 */
void CS225::Element2::Print() const
{ 
	std::cout << "(" << *p_val << ") "; 
}

/* \brief Sets the value of the current element.
 *
 * \param new_val
 * 	The new value to set the current element to.
 */
void CS225::Element2::Set(int new_val)
{ 
	*p_val = new_val; 
}

/* \brief Destructor.
 *
 * Ensures that the data in this object is properly deallocated.
 */
CS225::Element2::~Element2()
{
	delete p_val;
}

/* \brief Creates a copy of the current object.
 *
 * \return
 * 	A pointer to the newly-allocated copy of the current object.
 */
CS225::Element2 * CS225::Element2::clone(void) const
{
	return(new Element2(*p_val));
}

