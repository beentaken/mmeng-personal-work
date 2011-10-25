/*****************************************************************************/
/*!
\file   element2.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 4
\date   4 July, 2010
\brief
	This file contains the prototypes for a dynamically allocated integer
	storage element.
*/
/*****************************************************************************/
#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream>
#include "abstract-element.h"

/*
 * A concrete class implementing AbstractElement interface
 * Uses dynamically allocated data.
 */
namespace CS225
{

	class Element2 : public AbstractElement
	{
		public:
			Element2(int _val);
			Element2(const Element2& rhs);
			Element2& operator=(const Element2& rhs);
			virtual int Get() const;
			virtual void Set(int new_val);
			virtual void Print() const;
			virtual ~Element2();

			virtual Element2 * clone(void) const;
		private:
			int * p_val;
	};
}
#endif

