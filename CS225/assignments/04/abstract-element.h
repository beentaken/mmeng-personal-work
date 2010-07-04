#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H
#include <iostream>
#include "CRTP.h"
/*
 * Interface for elements.
 * Class is derived from ObjectCounter<AbstractElement>
 * to implement object counting using Curiously Recurring Template Pattern
 */
namespace CS225
{
	class AbstractElement : public ObjectCounter<AbstractElement>
	{
		public:
			virtual ~AbstractElement() {};
			virtual int Get() const = 0;
			virtual void Set(int new_val) = 0;
			virtual void Print() const = 0;
			virtual AbstractElement * clone() const = 0;
	};
}
#endif

