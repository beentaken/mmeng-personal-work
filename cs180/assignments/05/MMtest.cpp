// MMtest.cpp
// -- simple test of MemoryManager class
// cs180 3/08

#include <iostream>
#include "MemoryManager.h"
using namespace std;


int main(void) {
  MemoryManager mm(0x1000);
  mm.dump(cout);
  cout << "********" << endl;

  int *iarray = reinterpret_cast<int*>(mm.allocate(10*sizeof(int)));
  mm.dump(cout);
  cout << "********" << endl;

  float *farray = reinterpret_cast<float*>(mm.allocate(20*sizeof(float)));
  mm.dump(cout);
  cout << "********" << endl;

  mm.deallocate(iarray);
  mm.dump(cout);
  cout << "********" << endl;

  char *carray = reinterpret_cast<char*>(mm.allocate(15*sizeof(char)));
  mm.dump(cout);
  cout << "********" << endl;

  double *darray = reinterpret_cast<double*>(mm.allocate(5*sizeof(double)));
  mm.dump(cout);
  cout << "********" << endl;

  mm.deallocate(carray);
  mm.dump(cout);
  cout << "********" << endl;

  mm.deallocate(farray);
  mm.dump(cout);
  cout << "********" << endl;

  mm.deallocate(darray);
  mm.dump(cout);

  return 0;
}
