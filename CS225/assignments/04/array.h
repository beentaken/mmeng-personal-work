/*****************************************************************************/
/*!
\file   array.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 4
\date   4 July, 2010
\brief
	This file contains the definitions for a basic array object.
*/
/*****************************************************************************/
#ifndef ARRAY_H
#define ARRAY_H
#include "abstract-element.h"
#include "element-factory.h"
#include <iostream>

namespace CS225 {

/*
 * Class Array implements a simple array-like data structure.
 * Objects inside the Array have to be derived from AbstractElement.
 */
	class Array
	{
		public:
			Array(int * array, unsigned int _size, 
					const ElementFactory* _pElementFactory
					);

			Array(const Array& rhs);
			~Array(void);

			Array& operator=(const Array& rhs);

			int Get(unsigned int pos) const;
			void Set(int id, int pos, int value);

			void Print() const;
		private:
			AbstractElement** data;
			unsigned int size;
			const ElementFactory* pElementFactory;
			unsigned int * reference_counter;

			void removeReference(void);
			void deepCopy(void);
	};
}
#endif

