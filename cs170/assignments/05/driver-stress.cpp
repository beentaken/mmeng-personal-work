#include <iostream>
#include "Functions.h"
#include <cstdlib>  // rand

using std::cout;
using std::endl;

// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int number = std::rand() % (high - low + 1) + low;
  return number;
}

void TestStress1(void)
{
  cout << "***** Stress1 *****" << endl;
  
  int size = 100;
  int *array = new int[size];
  int low = 1;
  int high = 9;
  for (int i = 0; i < size; i++)
    array[i] = RandomInt(1, 9);

  int *begin = array;
  int *end = array + size;
  CS170::display(begin, end);

  int *newend = end;
  for (int i = low; i <= high; i++)
  {
    int item = i;
    newend = CS170::remove(begin, newend, item);
    cout << "remove " << item << ", new list: ";
    CS170::display(begin, newend);
  }
}

void TestStress2(void)
{
  cout << "***** Stress2 *****" << endl;
  
  int size = 10000000;
  int *array = new int[size];
  int low = -10;
  int high = 10;
  for (int i = 0; i < size; i++)
    array[i] = RandomInt(low, high);

  int *begin = array;
  int *end = array + size;
  //CS170::display(begin, end);

  int sum = CS170::sum(begin, end);
  std::cout << "Sum is " << sum << std::endl;

  int *newend = end;
  for (int i = low; i <= high; i++)
  {
    int item = i;
    newend = CS170::remove(begin, newend, item);
    sum = CS170::sum(begin, newend);
    cout << "remove " << item << ", sum is " << sum << std::endl;
    //std::cout << "new list: ";
    //CS170::display(begin, newend);
  }
}

void TestStress3(void)
{
  cout << "***** Stress3 *****" << endl;
  
  int size = 10000000;
  int *array = new int[size];
  for (int i = 0; i < size; i++)
    array[i] = 1;

  for (int i = 1; i < size; i *= 10)
    array[i] = 5;

  int *begin = array;
  int *end = array + size;
  //CS170::display(begin, end);

  int sum = CS170::sum(begin, end);
  std::cout << "Sum is " << sum << std::endl;

  int *newend = end;
  int item = 1;
  newend = CS170::remove(begin, newend, item);
  sum = CS170::sum(begin, newend);
  cout << "remove " << item << ", sum is " << sum << std::endl;
  //std::cout << "new list: ";
  //CS170::display(begin, newend);
}

int main(int argc, char **argv)
{
  std::srand(0);

  int test = 0;
  if (argc > 1)
    test = std::atoi(argv[1]);

  switch (test)
  {
    case 1:
        TestStress1();
      break;

    case 2:
        TestStress2();
      break;

    case 3:
        TestStress3();
      break;

    default:
        TestStress1();
        TestStress2();
        TestStress3();
      break;
  }
  return 0;
}
