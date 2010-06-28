#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"
/*
 * A concrete class implementing AbstractElement interface
 * Trivial.
 */
namespace CS225 {

  class Element1 : public AbstractElement {
    public:
      Element1(int _val);
      virtual int Get() const;
      virtual void Set(int new_val);
      virtual void Print() const;
    private:
      int val;
  };
}
#endif
