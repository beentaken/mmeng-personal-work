#include "element1.h"

/* \brief Constructor.
 *
 * \param _val
 * 	The value for this element to hold.
 */
CS225::Element1::Element1(int _val) : val(_val)
{
}

/* \brief Gets the value of this element.
 *
 * \return
 * 	The value of the Element1.
 */
int CS225::Element1::Get() const
{
	return val;
}

/* \brief Sets the value of this Element1.
 *
 * \param new_val
 * 	The new value to set the element to.
 */
void CS225::Element1::Set(int new_val)
{
	val=new_val;
}

/* \brief Prints the value of the current Element1.
 */
void CS225::Element1::Print() const
{ 
	std::cout << "[" << Get() << "] "; 
}

/* \brief Creates a copy of the current element.
 *
 * \return
 * 	A pointer to the newly-allocated copy of the current element.
 */
CS225::Element1 * CS225::Element1::clone() const
{
	return(new Element1(val));
}

