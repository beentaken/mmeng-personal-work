#include <iostream>
#include <cstdlib>  // atoi

#include "Vector.h"

void Print(const CS170::Vector& array, bool newline = true)
{
  for (unsigned i = 0; i < array.size(); i++)
  {
    std::cout << array[i] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

void TestPush(void)
{
  std::cout << "\n********** TestPush **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(i);
    Print(a);
  }

  std::cout << "pop_back until empty:\n";
  while (!a.empty())
  {
    a.pop_front();
    Print(a);
  }
}

void TestPop(void)
{
  std::cout << "\n********** TestPop **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(i);
    Print(a);
  }

  std::cout << "pop_back/pop_front:\n";
  a.pop_back();
  a.pop_front();
  Print(a);

  std::cout << "pop_back/front until empty:\n";
  while (!a.empty())
  {
    a.pop_front();
    a.pop_back();
    Print(a);
  }
}

void TestRemove(void)
{
  std::cout << "\n********** TestRemove **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "remove(0), remove(3):\n";
  a.remove(0);
  a.remove(3);
  Print(a);
}

void TestInsert1(void)
{
  std::cout << "\n********** TestInsert **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "insert(99, 3):\n";
  a.insert(99, 3);
  Print(a);
  std::cout << "insert(98, 0):\n";
  a.insert(98, 0);
  Print(a);
  std::cout << "insert(97, 6):\n";
  a.insert(97, 6);
  Print(a);
}

void TestSubscripts(void)
{
  std::cout << "\n********** TestSubscripts **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  Print(a);

  std::cout << "multiple each value by 3:\n";
  for (int i = 0; i < 10; i++)
    a[i] = a[i] * 3;
  Print(a);
}

void TestArray(void)
{
  std::cout << "\n********** TestArray **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);
  std::cout << "Construct from int array:\n";
  CS170::Vector a(ia, size);
  Print(a);
}

void TestSubscript1(void)
{
  std::cout << "\n********** TestSubscript1 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);
  std::cout << "Construct from int array:\n";
  const CS170::Vector a(ia, size);
  Print(a);

  int index = a.size() / 2;
  std::cout << "using subscript: a[" << index << "]" << std::endl;
  std::cout << "a[" << index << "] = " << a[index] << std::endl;
}

void TestSubscript2(void)
{
  std::cout << "\n********** TestSubscript2 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);
  std::cout << "Construct from int array:\n";
  const CS170::Vector a(ia, size);
  Print(a);

#if 0
  int index = a.size() * 2; // illegal
  std::cout << "using subscript: a[" << index << "]" << std::endl;
  std::cout << "a[" << index << "] = " << a[index] << std::endl;
#endif
}

void TestInsert2(void)
{
  std::cout << "\n********** TestInsert2 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);
  std::cout << "Construct from int array:\n";
  CS170::Vector a(ia, size);
  Print(a);
  std::cout << "Allocations: " << a.allocations() << std::endl;

#if 0
  int index = a.size() * 2; // illegal
  std::cout << "insert integer at index " << index << ":\n";
  a.insert(99, index);
#endif
}

void TestALot1(void)
{
  std::cout << "\n********** TestALot1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "push_back 10 odd integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i + 1);
  Print(a);

  std::cout << "empty/fill with 10 ints 3 times:\n";
  for (int i = 0; i < 3; i++)
  {
    while (!a.empty())
      a.pop_back();

    for (int j = 0; j < 10; j++)
      a.push_back(j);
  }
  Print(a);

  std::cout << "remove all but 3 integers:\n";
  while (a.size() > 3)
    a.pop_back();
  Print(a);

  std::cout << "pack:\n";
  a.pack();
  Print(a);

  std::cout << "push_back 10 more integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);
}

void TestCopy(void)
{
  std::cout << "\n********** TestCopy **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  std::cout << "Copy: b(a), print a,b\n";
  CS170::Vector b(a);
  Print(a);
  Print(b);

  std::cout << "Copy: c(b), print b,c\n";
  const CS170::Vector c(b);
  Print(b);
  Print(c);
}

void TestAssign(void)
{
  std::cout << "\n********** TestAssign **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 10 integers:\n";
  for (int i = 0; i < 10; i++)
  {
    a.push_back(2 * i);
    b.push_back(i);
  }

  Print(a);
  Print(b);

  std::cout << "Assign: b = a, print a,b\n";
  b = a;
  Print(a);
  Print(b);

  std::cout << "Assign: a = a, print a\n";
  a = a;
  Print(a);
}

void TestAdd1(void)
{
  std::cout << "\n********** TestAdd1 **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    b.push_front(10 * i);
    Print(b);
  }

  std::cout << "c = a + b:\n";
  CS170::Vector c;
  c = a + b;

  Print(a);
  Print(b);
  Print(c);

  std::cout << "clear a,b print c\n";
  a.clear();
  b.clear();
  Print(c);
}

void TestAdd2(void)
{
  std::cout << "\n********** TestAdd2 **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    b.push_front(10 * i);
    Print(b);
  }

  std::cout << "a += b:\n";
  a += b;
  Print(a);
  Print(b);

  std::cout << "clear b print a\n";
  b.clear();
  Print(a);
}

int main(int argc, char **argv)
{
  int test_num = 0;
  if (argc > 1)
    test_num = std::atoi(argv[1]);

  typedef void (*Test)(void);
  Test Tests[] = {
                    TestPush,        //  1 
                    TestPop,         //  2
                    TestRemove,      //  3
                    TestInsert1,     //  4
                    TestSubscripts,  //  5
                    TestArray,       //  6
                    TestSubscript1,  //  7
                    TestSubscript2,  //  8
                    TestInsert2,     //  9
                    TestALot1,       // 10
                    TestCopy,        // 11
                    TestAssign,      // 12
                    TestAdd1,        // 13
                    TestAdd2,        // 14
                 };

  int num = sizeof(Tests) / sizeof(*Tests);
  if (test_num == 0)
  {
    for (int i = 0; i < num; i++)
      Tests[i]();
  }
  else if (test_num > 0 && test_num <= num)
    Tests[test_num - 1]();

  return 0;
}

