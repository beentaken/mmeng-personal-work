/*****************************************************************************/
/*!
\file   element1.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 4
\date   4 July, 2010
\brief
	This file contains the prototypes for a basic integer storage element.
*/
/*****************************************************************************/
#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"
/*
 * A concrete class implementing AbstractElement interface
 * Trivial.
 */
namespace CS225
{

	class Element1 : public AbstractElement
	{
		public:
			Element1(int _val);
			virtual int Get() const;
			virtual void Set(int new_val);
			virtual void Print() const;
			virtual Element1 * clone() const;
		private:
			int val;
	};
}
#endif

