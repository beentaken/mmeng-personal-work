#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <vector>
#include <cstring>
#include <algorithm>

#include "SortedList.h"
#include "PRNG.h"

bool SHOW_TIMES = false;
bool PRINT_COPY = false;
bool THROW_EXCEPTION = false;
int EXCEPTION_TYPE = 1;

class FooException : public std::exception
{
  private:
    int m_ErrCode;
    std::string m_Description;

  public:
    FooException(int ErrCode, const std::string& Description) :
    m_ErrCode(ErrCode), m_Description(Description) {};

    virtual int code(void) const {
      return m_ErrCode;
    }

    virtual const char *what(void) const throw() {
      return m_Description.c_str();
    }

    virtual ~FooException() throw() {
    }
};

static const int ASIZE = 1;
static const int BSIZE = 23;
struct Foo
{
  static int copy_;
  int a;
  int b;
  int c;
  double d[ASIZE];
  double e[ASIZE];
  double f[ASIZE];
  char *g;
  Foo(int value) : a(value)
  {
    g = new char[BSIZE];
  }
  ~Foo()
  {
    //if (!g)
      delete [] g;
  }
  Foo(const Foo& rhs) : a(rhs.a)
  {
    if (THROW_EXCEPTION && rhs.a == 6)
    {
      if (EXCEPTION_TYPE == 1)
        throw FooException(0, "Foo object can't copy number 6!");
      else if (EXCEPTION_TYPE == 2)
        throw std::exception();
      else if (EXCEPTION_TYPE == 3)
        throw 1;
    }

    g = new char[BSIZE];
    std::memcpy(g, rhs.g, BSIZE);
    copy_++;
    if (PRINT_COPY)
      std::cout << "***** Copy *****\n";
      //std::cout << "***** Copy #" << copy_ << " *****\n";
  }
#if 1
  Foo& operator=(const Foo& rhs)
  {
    a = rhs.a;
    delete [] g;
    g = new char[BSIZE];
    std::memcpy(g, rhs.g, BSIZE);
    //g = rhs.g;
    if (PRINT_COPY)
      std::cout << "***** Assign *****\n";
    return *this;
  }
#endif
  operator int(void) const { return a; }
//private:
};

int Foo::copy_ = 0;

bool operator<(const Foo& lhs, const Foo& rhs)
{
  return lhs.a < rhs.a;
}

bool operator>(const Foo& lhs, const Foo& rhs)
{
  return lhs.a > rhs.a;
}

std::ostream& operator<<(std::ostream& os, const Foo& foo)
{
  os << foo.a;
  return os;
}

template <typename T>
void PrintArray(const T* array, int size)
{
  for (int i = 0; i < size; i++)
  {
    std::cout << array[i] << "  ";
  }
  std::cout << std::endl;
}

template <typename T>
void print(const T& v, bool newline = true)
{
  typename T::const_iterator iter = v.begin();
  for (; iter != v.end(); ++iter)
    std::cout << *iter << "  ";

  std::cout << "(size=" << v.size() << ")";
  if (newline)
    std::cout << std::endl;
}

template <typename T>
void printrev(const T& v, bool newline = true)
{
  typename T::const_iterator iter = v.rbegin();
  for (; iter != v.rend(); --iter)
    std::cout << *iter << "  ";

  std::cout << "(size=" << v.size() << ")";
  if (newline)
    std::cout << std::endl;
}

template <typename T>
T SumArray(const T* array, int size)
{
  T sum = 0;
  for (int i = 0; i < size; i++)
    sum += array[i];
  return sum;
}

template <typename T>
int SumList(const T& list)
{
  typename T::const_iterator it = list.begin();
  int sum = 0;
  for (; it != list.end(); ++it)
    sum += *it;
  return sum;
}

template <typename T, typename Pred, typename Sorter>
bool IsSorted(const SortedList<T, Pred>& list, Sorter sortor)
{
    // less than 2 elements is considered sorted
  if (list.size() < 2)
    return true;

  typename SortedList<T, Pred>::const_iterator prev = list.begin();
  typename SortedList<T, Pred>::const_iterator iter = list.begin();
  ++iter; // next

  while (iter != list.end())
  {
    if (sortor(*iter, *prev))
      return false; // found one out of place
    prev = iter;
    ++iter;
  }
  return true; // must be sorted
}

template <typename T, typename Pred, typename Sorter>
bool IsSorted(const std::list<T, Pred>& list, Sorter sortor)
{
    // less than 2 elements is considered sorted
  if (list.size() < 2)
    return true;

  typename std::list<T, Pred>::const_iterator prev = list.begin();
  typename std::list<T, Pred>::const_iterator iter = list.begin();
  ++iter; // next

  while (iter != list.end())
  {
    if (sortor(*iter, *prev))
      return false; // found one out of place
    prev = iter;
    ++iter;
  }
  return true; // must be sorted
}

template <typename T, typename Pred, typename Sorter>
bool IsSortedRev(const SortedList<T, Pred>& list, Sorter sortor)
{
    // less than 2 elements is considered sorted
  if (list.size() < 2)
    return true;

  typename SortedList<T, Pred>::const_iterator next = list.end();
  --next; // tail

  typename SortedList<T, Pred>::const_iterator iter = list.end();
  --iter; --iter; // tail->Prev

  while (iter != list.rend())
  {
    if (sortor(*next, *iter))
      return false; // found one out of place
    next = iter;
    --iter;
  }
  return true; // must be sorted
}

template <typename T, typename Pred, typename Sorter>
bool IsSortedRev(const std::list<T, Pred>& list, Sorter sortor)
{
    // less than 2 elements is considered sorted
  if (list.size() < 2)
    return true;

  typename std::list<T, Pred>::const_reverse_iterator next = list.rbegin();
  ++next; // tail

  typename std::list<T, Pred>::const_reverse_iterator iter = list.rbegin();
  ++iter; ++iter; // tail->Prev

  while (iter != list.rend())
  {
    if (sortor(*next, *iter))
      return false; // found one out of place
    next = iter;
    ++iter;
  }
  return true; // must be sorted
}

// std::list.sort()
void Test0(void)
{
  std::cout << "\n********** Test0 **********\n";
  Digipen::Utils::srand(1, 1);
  int size = 10;
  int *ia = new int[size];

  for (int i = 0; i < size; i++)
    ia[i] = Digipen::Utils::Random(10, 99);

  try
  {
      /////////////////////////////////////////////////////////////////////
      std::cout << "std:: push_back " << size << " integers\n";
      std::list<Foo> list1;
      std::vector<Foo> list2;
      for (int i = 0; i < size; i++)
      {
        list1.push_back(ia[i]);
        list2.push_back(ia[i]);
      }

      print(list1, true);

      PRINT_COPY = true;
      list1.sort();
      PRINT_COPY = false;
      std::cout << "list sorted\n";
      print(list1, true);

      PRINT_COPY = true;
      std::sort(list2.begin(), list2.end()); // for vectors
      PRINT_COPY = false;
      std::cout << "vector sorted\n";
      print(list2, true);
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
  delete [] ia;
}

// copy constructor, no allocator
void Test1(void)
{
  std::cout << "\n********** Test1 **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

    // for ints, change Foo to int
  typedef Foo T;
  SortedList<T> a;
  std::cout << "push back " << size << " integers:\n";
  try
  {
    for (int i = 0; i < size; i++)
      a.push_back(ia[i]);
    print(a);

    std::cout << "copy b(a)\n";
    SortedList<T> b(a); // copy constructor
    print(a);
    print(b);

    std::cout << "copy c = b\n";
    SortedList<T> c = b; // copy constructor
    print(a);
    print(b);
    print(c);
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
}

// copy constructor with allocator
void Test2(void)
{
  std::cout << "\n********** Test2 **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

  typedef Foo T;

  bool UseCPPMemManager = false;
  unsigned ObjectsPerPage = 1024;
  unsigned MaxPages = 0;
  bool DebugOn = true;
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<T, std::less<T> >::nodesize(), config);
  SortedList<T> a(std::less<T>(), &oa, SharedAllocator);

  std::cout << "push back " << size << " integers:\n";
  try
  {
    for (int i = 0; i < size; i++)
      a.push_back(ia[i]);
    print(a);

    std::cout << "copy b(a)\n";
    SortedList<T> b(a); // copy constructor
    print(a);
    print(b);

    std::cout << "copy c = b\n";
    SortedList<T> c = b; // copy constructor
    print(a);
    print(b);
    print(c);
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
}

// copy constructor with allocator and exception safety
void Test3(int objects)
{
  typedef Foo T;
  if (!SortedList<T>::ImplementedExtraCredit())
    return;

  std::cout << "\n********** Test3 **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

  bool UseCPPMemManager = false;
  unsigned ObjectsPerPage = objects;
  unsigned MaxPages = 1;
  bool DebugOn = true;
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<T, std::less<T> >::nodesize(), config);
  SortedList<T> a(std::less<T>(), &oa, SharedAllocator);

  std::cout << "push back " << size << " integers: (objects = " << objects << ")\n";
  try
  {
    for (int i = 0; i < size * 2; i++)
      a.push_back(ia[i % size]);
    print(a);

      // This will throw an exception and leak memory if
      // it's not exception safe
    std::cout << "copy b(a)\n";

    SortedList<T> b(a); // copy constructor
    print(b);
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
}

// copy constructor with allocator and exception safety
void Test3a(int ex_type)
{
  typedef Foo T;
  if (!SortedList<T>::ImplementedExtraCredit())
    return;

  std::cout << "\n********** Test3a **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

  int objects = size;
  bool UseCPPMemManager = false;
  unsigned ObjectsPerPage = 50;
  unsigned MaxPages = 1;
  bool DebugOn = true;
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<T, std::less<T> >::nodesize(), config);
  SortedList<T> a(std::less<T>(), &oa, SharedAllocator);

  std::cout << "push back " << size << " integers: (objects = " << objects << ")\n";
  try
  {
    THROW_EXCEPTION = false;
    for (int i = 0; i < size; i++)
      a.push_back(ia[i]);
    print(a);

      // This will throw an exception and leak memory if
      // it's not exception safe
    THROW_EXCEPTION = true;
    EXCEPTION_TYPE = ex_type;
    std::cout << "copy b(a)\n";
    SortedList<T> b(a); // copy constructor
    print(b);
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
  THROW_EXCEPTION = false;
}


// assignment operator with allocator
void Test4a(void)
{
  std::cout << "\n********** Test4a **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

  typedef Foo T;

  bool UseCPPMemManager = false;
  unsigned ObjectsPerPage = 100;
  unsigned MaxPages = 1;
  bool DebugOn = true;
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<T, std::less<T> >::nodesize(), config);
  SortedList<T> a(std::less<T>(), &oa, SharedAllocator);
  SortedList<T> b(std::less<T>(), &oa, SharedAllocator);
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);

  std::cout << "push back " << size << " integers:\n";
  try
  {
    for (int i = 0; i < size * 2; i++)
      a.push_back(ia[i % size]);
    print(a);
    print(b);

      // This should not throw
    std::cout << "assign b = a\n";
    b = a; // assignment

  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
  print(a);
  print(b);
}


/*
Correct output:

********** Test4 **********
push back 9 integers:
1  2  3  4  5  6  7  8  9  1  2  3  4  5  6  7  8  9  (size=18)
10  11  12  (size=3)
assign b = a
Caught exception: allocate_new_page: The maximum number of pages has been allocated.
1  2  3  4  5  6  7  8  9  1  2  3  4  5  6  7  8  9  (size=18)
10  11  12  (size=3)


Incorrect output
********** Test4 **********
push back 9 integers:
1  2  3  4  5  6  7  8  9  1  2  3  4  5  6  7  8  9  (size=18)
10  11  12  (size=3)
assign b = a
Caught exception: allocate_new_page: The maximum number of pages has been allocated.
1  2  3  4  5  6  7  8  9  1  2  3  4  5  6  7  8  9  (size=18)
1  2  3  4  5  6  7  8  9  1  2  3  (size=12)
*/
// assignment operator with allocator and exception safety
void Test4b(void)
{
  typedef Foo T;

  if (!SortedList<T>::ImplementedExtraCredit())
    return;

  std::cout << "\n********** Test4b **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

  bool UseCPPMemManager = false;
  unsigned ObjectsPerPage = 35;
  unsigned MaxPages = 1;
  bool DebugOn = true;
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<T, std::less<T> >::nodesize(), config);
  SortedList<T> a(std::less<T>(), &oa, SharedAllocator);
  SortedList<T> b(std::less<T>(), &oa, SharedAllocator);
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);

  std::cout << "push back " << size << " integers:\n";
  try
  {
    THROW_EXCEPTION = false;
    for (int i = 0; i < size * 2; i++)
      a.push_back(ia[i % size]);
    print(a);
    print(b);

      // This will throw an exception
    std::cout << "assign b = a\n";

    b = a; // assignment
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
  print(a);
  print(b);
}

void Test4c(void)
{
  typedef Foo T;

  if (!SortedList<T>::ImplementedExtraCredit())
    return;

  std::cout << "\n********** Test4c **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(ia)/sizeof(*ia);

  bool UseCPPMemManager = false;
  unsigned ObjectsPerPage = 35;
  unsigned MaxPages = 1;
  bool DebugOn = true;
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<T, std::less<T> >::nodesize(), config);
  SortedList<T> a(std::less<T>(), &oa, SharedAllocator);
  SortedList<T> b(std::less<T>(), &oa, SharedAllocator);
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);

  std::cout << "push back " << size << " integers:\n";
  try
  {
    THROW_EXCEPTION = false;
    for (int i = 0; i < size * 2; i++)
      a.push_back(ia[i % size]);
    print(a);
    print(b);

      // This will throw an exception
    std::cout << "assign b = a\n";

    THROW_EXCEPTION = true;
    EXCEPTION_TYPE = 1;
    b = a; // assignment
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
  THROW_EXCEPTION = false;
  print(a);
  print(b);
}

typedef int (*AllocHookFn)(int, void *, size_t, int,  long, const unsigned char *, int);

static int BLOCKS = 0;
int AllocHook(int, void *, size_t, int,  long, const unsigned char *, int)
{
#if 0
  return 0;
#else
  BLOCKS++;
  if (BLOCKS == 4)
    return 0;
  else
    return 1;
#endif
}

// simple push_back
void Test5(void)
{
  std::cout << "\n********** Test5 **********\n";
  int ia[] = {1, 2, 3, 4, 5, 6};
  int size = sizeof(ia)/sizeof(*ia);

/*
  This demonstrates the strong guarantee for exception safety without requiring extra work.
  If a node can't be allocated during the push_back operation, the list is not changed and
  no damage has been done. 
*/
#define FAILNEWx
#ifdef FAILNEW
  bool UseCPPMemManager = true;
  unsigned ObjectsPerPage = 1024;
  unsigned MaxPages = 0;
  bool DebugOn = true; 
  unsigned PadBytes = 0;
  unsigned HeaderSize = 0;
  unsigned Alignment = 0;
  bool SharedAllocator = true;
  OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);
  ObjectAllocator oa(SortedList<int, std::less<int> >::nodesize(), config);
  SortedList<int> a(std::less<int>(), &oa, SharedAllocator);
  AllocHookFn p;
#else
  SortedList<int> a;
#endif

  std::cout << "insert " << size << " integers:\n";
  try
  {
#ifdef FAILNEW
    p = _CrtSetAllocHook(AllocHook);
#endif

    for (int i = 0; i < size; i++)
    {
      print(a);
      printrev(a);
      a.push_back(ia[i]);
    }
    print(a);
    printrev(a);
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
#ifdef FAILNEW
  _CrtSetAllocHook(p);
#endif
}


// simple insert, less
void Test6(void)
{
  std::cout << "\n********** Test6 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);

  SortedList<int> a;

  std::cout << "insert " << size << " integers:\n";
  try
  {
    for (int i = 0; i < size; i++)
    {
      a.insert(ia[i]);
      print(a);
      printrev(a);
    }
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
}

// simple ordering, parameter
template <typename Pred>
void Test7(Pred sorter)
{
  std::cout << "\n********** Test7 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);

    // NEED EXTRA PARENS BELOW. (function prototype or variable decl?)
  //SortedList<int, std::greater<int> > a( (std::greater<int>()) );

  SortedList<int, Pred> a(sorter);

  std::cout << "insert " << size << " integers:\n";
  try
  {
    for (int i = 0; i < size; i++)
      a.insert(ia[i]);
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }
  print(a);
}

// stress comparisons, push back
void Test8(int test, int size)
{
  std::cout << "\n********** Test8 **********\n";
  int *ia;
  ia = new int[size];

  Digipen::Utils::srand(1, 1);

  for (int i = 0; i < size; i++)
    ia[i] = Digipen::Utils::Random(-100, 100);

  //PrintArray(ia, size);

  std::cout << "push_back " << size << " integers";
  try
  {
    std::clock_t start, end;
    /////////////////////////////////////////////////////////////////////
    if (test == 1)
    {
      std::cout << " using unsorted SortedList and new/delete\n";
      SortedList<int> a;

      start = std::clock();
      for (int i = 0; i < size; i++)
        a.push_back(ia[i]);
      end = std::clock();
      std::cout << "Sum is: " << SumList(a) << std::endl;
      if (SHOW_TIMES)
      {
        std::cout << "Time: " << (end - start) << std::endl;
      }
      //print(a);
    }
    else if (test == 2)
    {
      std::cout << " using unsorted SortedList and ObjectAllocator\n";
      /////////////////////////////////////////////////////////////////////
      bool UseCPPMemManager = false;
      unsigned ObjectsPerPage = 1024;
      unsigned MaxPages = 0;
      bool DebugOn = false; 
      unsigned PadBytes = 0;
      unsigned HeaderSize = 0;
      unsigned Alignment = 0;
      bool SharedAllocator = false;
      OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);

      ObjectAllocator oa(SortedList<int, std::less<int> >::nodesize(), config);
      SortedList<int> b(std::less<int>(), &oa, SharedAllocator);

      start = std::clock();
      for (int i = 0; i < size; i++)
        b.push_back(ia[i]);
      end = std::clock();
      std::cout << "Sum is: " << SumList(b) << std::endl;
      if (SHOW_TIMES)
      {
        std::cout << "Time: " << (end - start) << std::endl;
      }
      //print(b);
    }
    else if (test == 3)
    {
      std::cout << " using std::list (unsorted)\n";
      /////////////////////////////////////////////////////////////////////
      std::list<int> list;
      start = std::clock();
      for (int i = 0; i < size; i++)
        list.push_back(ia[i]);
      //list.sort();
      end = std::clock();
      std::cout << "Sum is: " << SumList(list) << std::endl;
      if (SHOW_TIMES)     
      {
        std::cout << "Time: " << (end - start) << std::endl;
      }
    }
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }

  delete [] ia;
}

// stress ordered
void Test9(int test, int size)
{
  std::cout << "\n********** Test9 **********\n";
  int *ia;
  ia = new int[size];

  Digipen::Utils::srand(1, 1);

  for (int i = 0; i < size; i++)
    ia[i] = Digipen::Utils::Random(-100, 100);

  std::cout << "insert " << size << " integers";
  try
  {
    std::clock_t start, end;
    /////////////////////////////////////////////////////////////////////
    if (test == 1)
    {
      std::cout << " using sorted SortedList and new/delete\n";
      SortedList<int> a;

      start = std::clock();
      for (int i = 0; i < size; i++)
        a.insert(ia[i]);
      end = std::clock();
      std::cout << "Sum is: " << SumList(a) << std::endl;
      if (SHOW_TIMES)     
      {
        std::cout << "Time: " << (end - start) << std::endl;
      }
      //print(a);
    }
    else if (test == 2)
    {
      std::cout << " using sorted SortedList and ObjectAllocator\n";
      /////////////////////////////////////////////////////////////////////
      bool UseCPPMemManager = false;
      unsigned ObjectsPerPage = 1024;
      unsigned MaxPages = 0;
      bool DebugOn = false; 
      unsigned PadBytes = 0;
      unsigned HeaderSize = 0;
      unsigned Alignment = 0;
      bool SharedAllocator = false;
      OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);

      ObjectAllocator oa(SortedList<int, std::less<int> >::nodesize(), config);
      SortedList<int> b(std::less<int>(), &oa, SharedAllocator);

      start = std::clock();
      for (int i = 0; i < size; i++)
        b.insert(ia[i]);
      end = std::clock();
      std::cout << "Sum is: " << SumList(b) << std::endl;
      if (SHOW_TIMES)     
      {
        std::cout << "Time: " << (end - start) << std::endl;
      }
      //print(b);
    }
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }

  delete [] ia;
}

// selection sort O(N^2)
template <typename Pred>
void Test10(int size, bool printit, Pred sorter)
{
  std::cout << "\n********** Test10 selection sort **********\n";
  int *ia;
  ia = new int[size];

  Digipen::Utils::srand(1, 1);

  for (int i = 0; i < size; i++)
    ia[i] = Digipen::Utils::Random(-100, 100);

  if (printit)
    PrintArray(ia, size);

  typedef Foo T;
  try
  {
    std::clock_t start, end;
    /////////////////////////////////////////////////////////////////////
    bool UseCPPMemManager = false;
    unsigned ObjectsPerPage = 4;
    unsigned MaxPages = 0;
    bool DebugOn = true; 
    unsigned PadBytes = 0;
    unsigned HeaderSize = 0;
    unsigned Alignment = 0;
    bool SharedAllocator = false;
    OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);

    ObjectAllocator oa(SortedList<T, Pred>::nodesize(), config);
    SortedList<T, Pred> a(sorter, &oa, SharedAllocator);

    std::cout << "push_back " << size << " Foos..." << std::endl;
    for (int i = 0; i < size; i++)
      a.push_back(ia[i]);

    if (printit)
      print(a);

    std::cout << "selection sorting..." << std::endl;
    start = std::clock();
      PRINT_COPY = true;
      a.selection_sort(sorter);
      PRINT_COPY = false;
    end = std::clock();

    if (printit)
      print(a, true);

    if (IsSorted(a, sorter))
      std::cout << "List is sorted\n";
    else
      std::cout << "List is NOT sorted\n";

    if (IsSortedRev(a, sorter))
      std::cout << "List is sorted in rev\n";
    else
      std::cout << "List is NOT sorted in rev\n";

    std::cout << "Sum is: " << SumList(a) << std::endl;
    if (SHOW_TIMES)     
    {
      std::cout << "Time: " << (end - start) << std::endl;
    }
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }

  delete [] ia;
}

// merge sort O(N lg N)
template <typename Pred>
void Test11(int size, bool printit, Pred sorter)
{
  std::cout << "\n********** Test11 mergesort **********\n";
  int *ia;
  ia = new int[size];

  Digipen::Utils::srand(1, 1);

  for (int i = 0; i < size; i++)
    ia[i] = Digipen::Utils::Random(-100, 100);

  if (printit)
    PrintArray(ia, size);

  typedef Foo T;
  try
  {
    std::clock_t start, end;
    /////////////////////////////////////////////////////////////////////
    bool UseCPPMemManager = false;
    unsigned ObjectsPerPage = 1024;
    unsigned MaxPages = 0;
    bool DebugOn = false; 
    unsigned PadBytes = 0;
    unsigned HeaderSize = 0;
    unsigned Alignment = 0;
    bool SharedAllocator = false;
    OAConfig config(UseCPPMemManager, ObjectsPerPage, MaxPages, DebugOn, PadBytes, HeaderSize, Alignment);

    ObjectAllocator oa(SortedList<T, Pred>::nodesize(), config);
    SortedList<T, Pred> a(sorter, &oa, SharedAllocator);

    std::cout << "push_back " << size << " Foos..." << std::endl;
    for (int i = 0; i < size; i++)
      a.push_back(ia[i]);

    if (printit)
      print(a);

    std::cout << "merge sorting..." << std::endl;
    start = std::clock();
      PRINT_COPY = true;
      a.merge_sort(sorter);
      PRINT_COPY = false;
    end = std::clock();

    if (printit)
      print(a, true);

    if (IsSorted(a, sorter))
      std::cout << "List is sorted\n";
    else
      std::cout << "List is NOT sorted\n";

    if (IsSortedRev(a, sorter))
      std::cout << "List is sorted in rev\n";
    else
      std::cout << "List is NOT sorted in rev\n";

    std::cout << "Sum is: " << SumList(a) << std::endl;
    if (SHOW_TIMES)     
    {
      std::cout << "Time: " << (end - start) << std::endl;
    }
  }
  catch (const SortedListException &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception" << std::endl;
  }

  delete [] ia;
}

int main(void)
{
  // std::list.sort(), no copies are made
  Test0();

  ////// copy constructor
  Test1(); // copy constructor, no allocator
  Test2(); // copy constructor with allocator

    // Allocator failures (no more memory)
  for (int i = 0; i < 30; i++)
    Test3(16 + i); // copy constructor with allocator and exception safety

    // Client failures (copy constructor fails duing copy)
  Test3a(1);
  Test3a(2);
  Test3a(3);

  //// assignment operator
  Test4a(); // assignment operator with allocator
  Test4b(); // assignment operator with allocator and exception safety (alloc failure)
  Test4c(); // assignment operator with allocator and exception safety (client failure)

  // push_back
  Test5();
  Test6();

  // ordered
  Test7( std::greater<int>() );
  Test7( std::less<int>() );

  // stress push_back, allocator vs. new
  Test8(1, 10000); 
  Test8(2, 10000);
  Test8(3, 10000);

  // stress insert
  Test9(1, 1000); 
  Test9(2, 1000);

  // selection sort
  Test10(20, true, std::greater<Foo>());
  Test10(20, true, std::less<Foo>()); 

  // stress selection sort
  Test10(1000, false, std::less<Foo>());
  Test10(2000, false, std::less<Foo>());
  Test10(4000, false, std::less<Foo>());
  Test10(8000, false, std::less<Foo>());
  Test10(20000, false, std::less<Foo>());

  // merge sort
  Test11(10, true, std::less<Foo>()); 
  Test11(10, true, std::greater<Foo>()); 
  Test11(30, true, std::less<Foo>()); 
  Test11(30, true, std::greater<Foo>()); 

  // stress merge sort
  Test11(1600000, false, std::less<Foo>()); 

  #ifdef __BORLANDC__
    std::string s;
    std::cout << "Press any key to continue . . . ";
    std::getline(std::cin, s);
  #endif
  return 0;
}
