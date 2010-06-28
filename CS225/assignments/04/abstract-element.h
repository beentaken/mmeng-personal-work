#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H
#include <iostream>
#include "CRTP.h"
/*
 * Interface for elements.
 * Class is derived from ObjectCounter<AbstractElement>
 * to implement object counting using Curiously Recurring Template Pattern
 */
namespace CS225 {

  class AbstractElement : public ObjectCounter<AbstractElement> {
    public:
      int Get() const = 0;
      void Set(int new_val) = 0;
      void Print() const = 0;
  };
}
#endif
