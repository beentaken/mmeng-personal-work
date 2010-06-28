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
	class Array {
		public:
			Array(int * array, unsigned int _size, 
					const ElementFactory* _pElementFactory
					);

			int Get(unsigned int pos) const;
			void Set(int id, int pos, int value);

			void Print() const;
		private:
			AbstractElement** data;
			unsigned int size;
			const ElementFactory* pElementFactory;
	};
}
#endif
