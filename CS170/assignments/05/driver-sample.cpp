#include <iostream> // ostream, cout, endl
#include "Functions.h"

using std::cout;
using std::endl;

struct Student
{
  char login[9];
  int age;
  int year;
  double GPA;
};

std::ostream& operator<<(std::ostream& os, const Student& s)
{
  os << "(login) " << s.login << ", ";
  os << "(age) " << s.age << ", ";
  os << "(year) " << s.year << ", ";
  os << "(GPA) " << s.GPA << endl;
  return os;
}

bool operator>(const Student& lhs, const Student& rhs)
{
  return lhs.GPA > rhs.GPA;
}

bool operator<(const Student& lhs, const Student& rhs)
{
  return lhs.GPA < rhs.GPA;
}

void print_students(const Student *s, int size)
{
  for (int i = 0; i < size; i++)
    cout << s[i];
}

static void TestSwap1(void)
{
  cout << "***** TestSwap1 *****" << endl;

  int a = 5, b = 8;

  cout << "a = " << a << ", b = " << b << endl;
  CS170::swap(a, b);
  cout << "a = " << a << ", b = " << b << endl;
}

static void TestSwap2(void)
{
  cout << "***** TestSwap2 *****" << endl;
  Student s1 = {"jdoe", 20, 3, 3.82};
  Student s2 = {"fbar", 22, 1, 1.28};

  cout << "s1: " << s1;
  cout << "s2: " << s2;
  CS170::swap(s1, s2);
  cout << "s1: " << s1;
  cout << "s2: " << s2;
}

static void TestSwapRanges1(void)
{
  cout << "***** SwapRanges *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};
  int i2[] = {3, 6, 8, 0, -1, 5, -3, -9, 3, 5, 8};

  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  CS170::display(i2, i2 + size);
  CS170::swap_ranges(i1, i1 + size, i2);
  CS170::display(i1, i1 + size);
  CS170::display(i2, i2 + size);
}

static void TestRemove1(void)
{
  cout << "***** Remove1 *****" << endl;
  int i1[] = {5, -7, 4, 10, -21, 15, 9};

  int size = sizeof(i1) / sizeof(int);
  CS170::display(i1, i1 + size);
  int item = -1;
  int *newend = CS170::remove(i1, i1 + size,  item);
  cout << "remove " << item << ", new list: ";
  CS170::display(i1, newend);
}

static void TestRemove2(void)
{
  cout << "***** Remove2 *****" << endl;
  int i1[] = {5, -7, 4, 10, -7, 15, 9};

  int size = sizeof(i1) / sizeof(int);
  CS170::display(i1, i1 + size);
  int item = -7;
  int *newend = CS170::remove(i1, i1 + size,  item);
  cout << "remove " << item << ", new list: ";
  CS170::display(i1, newend);
}

static void TestRemove3(void)
{
  cout << "***** Remove3 *****" << endl;
  int i1[] = {-1, -1, -1, -1, -1, -1, -1};

  int size = sizeof(i1) / sizeof(int);
  CS170::display(i1, i1 + size);
  int item = -1;
  int *newend = CS170::remove(i1, i1 + size,  item);
  cout << "remove " << item << ", new list: ";
  CS170::display(i1, newend);
}

static void TestCount1(void)
{
  cout << "***** Count1 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size = sizeof(i1) / sizeof(int);
  CS170::display(i1, i1 + size);
  int item = -1;
  int c = CS170::count(i1, i1 + size, item);
  cout << "Count of " << item << " is " << c << endl;
}

static void TestCount2(void)
{
  cout << "***** Count2 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size = sizeof(i1) / sizeof(int);
  CS170::display(i1, i1 + size);
  int item = 50;
  int c = CS170::count(i1, i1 + size, item);
  cout << "Count of " << item << " is " << c << endl;
}

static void TestFind1(void)
{
  cout << "***** Find1 *****" << endl;
  const int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size = sizeof(i1) / sizeof(int);
  const int *end = i1 + size;
  CS170::display(i1, end);
  const int item = 9;
  const int *pos = CS170::find(i1, end, item);
  if (pos != end)
    cout << "Item " << item << " is " << *pos << endl;
  else
    cout << "Item " << item << " was not found" << endl;
}

static void TestFind2(void)
{
  cout << "***** Find2 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size = sizeof(i1) / sizeof(int);
  int *end = i1 + size;
  CS170::display(i1, end);
  const int item = 9;
  int *pos = CS170::find(i1, end, item);
  
  if (pos != end)
  {
    cout << "Changing " << item << " to 100" << endl;
    *pos = 100;
  }
  else
    cout << "Item " << item << " was not found" << endl;

  CS170::display(i1, end);
}

static void TestFind3(void)
{
  cout << "***** Find3 *****" << endl;
  const int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size = sizeof(i1) / sizeof(int);
  const int *end = i1 + size;
  CS170::display(i1, end);
  const int item = 19;
  const int *pos = CS170::find(i1, end, item);
  if (pos != end)
    cout << "Item " << item << " is " << *pos << endl;
  else
    cout << "Item " << item << " was not found" << endl;
}

static void TestCopy1(void)
{
  cout << "***** Copy1 *****" << endl;
  const short i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};
  int size = sizeof(i1) / sizeof(short);
  short i2[20] = {0};

  CS170::display(i1, i1 + size);
  short *i2end = CS170::copy(i1, i1 + size, i2);
  CS170::display(i2, i2end);
}

static void TestFill1(void)
{
  cout << "***** Fill1 *****" << endl;
  int i1[10];
  int size = 10;

  CS170::fill(i1, i1 + size, 12);
  CS170::display(i1, i1 + size);
}

static void TestReplace1(void)
{
  cout << "***** Replace1 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};
  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  int olditem = -1;
  int newitem = -8;
  cout << "Replacing " << olditem << " with " << newitem << endl;
  CS170::replace(i1, i1 + size, olditem, newitem);
  CS170::display(i1, i1 + size);
}

static void TestMin1(void)
{
  cout << "***** Min1 *****" << endl;
  const int i1[] = {-1, 2, 6, -31, 9, 5, 7, -21, -1, 8, -10};
  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  const int *pos = CS170::min_element(i1, i1 + size);

  cout << "The min element is: " << *pos << endl;
}

static void TestMin2(void)
{
  cout << "***** Min2 *****" << endl;
  int i1[] = {-1, 2, 6, -31, 9, 5, 7, -21, -1, 8, -10};
  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  int *pos = CS170::min_element(i1, i1 + size);

  cout << "The min element is: " << *pos << endl;
}

static void TestMin3(void)
{
  cout << "***** Min3 *****" << endl;
  Student s1[] = { {"jdoe", 20, 3, 3.82},
                   {"fbar", 22, 1, 1.28},
                   {"wxyz", 19, 3, 1.59},
                   {"abcd", 20, 1, 1.99},
                   {"jbar", 22, 2, 3.38}
                 };

  int size = sizeof(s1) / sizeof(*s1);
  Student *end = s1 + size;

  print_students(s1, size);
  Student *pos = CS170::min_element(s1, end);

  cout << "The min element is: " << *pos;
}

static void TestMax1(void)
{
  cout << "***** Max1 *****" << endl;
  const int i1[] = {-1, 2, 6, -31, 9, 5, 7, -21, -1, 8, -10};
  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  const int *pos = CS170::max_element(i1, i1 + size);

  cout << "The max element is: " << *pos << endl;
}

static void TestMax2(void)
{
  cout << "***** Max2 *****" << endl;
  int i1[] = {-1, 2, 6, -31, 9, 5, 7, -21, -1, 8, -10};
  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  int *pos = CS170::max_element(i1, i1 + size);

  cout << "The max element is: " << *pos << endl;
}

static void TestMax3(void)
{
  cout << "***** Max3 *****" << endl;
  Student s1[] = { {"jdoe", 20, 3, 3.82},
                   {"fbar", 22, 1, 1.28},
                   {"wxyz", 19, 3, 1.59},
                   {"abcd", 20, 1, 1.99},
                   {"jbar", 22, 2, 3.38}
                 };

  int size = sizeof(s1) / sizeof(*s1);
  Student *end = s1 + size;

  print_students(s1, size);
  Student *pos = CS170::max_element(s1, end);

  cout << "The max element is: " << *pos;
}

static void TestEqual1(void)
{
  cout << "***** Equal1 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};
  short i2[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size1 = sizeof(i1) / sizeof(int);
  int size2 = sizeof(i2) / sizeof(short);

  CS170::display(i1, i1 + size1);
  CS170::display(i2, i2 + size2);
  bool same = CS170::equal(i1, i1 + size1, i2);
  if (same)
    std::cout << "Arrays are equal\n";
  else
    std::cout << "Arrays are not equal\n";
}

static void TestEqual2(void)
{
  cout << "***** Equal2 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7};
  short i2[] = {-1, 2, 6, -1, 9, 5, 7, -1, -1, 8, -1};

  int size1 = sizeof(i1) / sizeof(int);
  int size2 = sizeof(i2) / sizeof(short);

  CS170::display(i1, i1 + size1);
  CS170::display(i2, i2 + size2);
  bool same = CS170::equal(i1, i1 + size1, i2);
  if (same)
    std::cout << "Arrays are equal\n";
  else
    std::cout << "Arrays are not equal\n";
}

static void TestEqual3(void)
{
  cout << "***** Equal3 *****" << endl;
  int i1[] = {-1, 2, 6, -1, 9, 5, 7};
  short i2[] = {-1, 2, 6, -1, 9, 6, 7};

  int size1 = sizeof(i1) / sizeof(int);
  int size2 = sizeof(i2) / sizeof(short);

  CS170::display(i1, i1 + size1);
  CS170::display(i2, i2 + size2);
  bool same = CS170::equal(i1, i1 + size1, i2);
  if (same)
    std::cout << "Arrays are equal\n";
  else
    std::cout << "Arrays are not equal\n";
}

static void TestSum1(void)
{
  cout << "***** Sum1 *****" << endl;
  int i1[] = {3, 6, 8, 0, -1, 5, -3, -9, 3, 5, 8, -20, -5};

  int size = sizeof(i1) / sizeof(int);

  CS170::display(i1, i1 + size);
  int total = CS170::sum(i1, i1 + size);
  std::cout << "Sum is " << total << std::endl;
}

int main(void)
{
  TestSwap1();
  TestSwap2();
  TestSwapRanges1();
  TestRemove1();
  TestRemove2();
  TestRemove3();
  TestCount1();
  TestCount2();
  TestFind1();
  TestFind2();
  TestFind3();
  TestCopy1();
  TestFill1();
  TestReplace1();
  TestMin1();
  TestMin2();
  TestMin3();
  TestMax1();
  TestMax2();
  TestMax3();
  TestEqual1();
  TestEqual2();
  TestEqual3();
  TestSum1();
  return 0;
}
