#include <iostream> // cout, endl
#include <cstdlib>  // rand, srand
#include <ctime>    // time_t, clock
#include "Vector.h"

#define PRINT_RESULTS

// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int number = std::rand() % (high - low + 1) + low;
  return number;
}

void Shuffle(int *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    int r = std::rand() % size;
    int t = array[i];
    array[i] = array[r];
    array[r] = t;
  }
}  

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

#ifdef PRINT_RESULTS
void PrintSortResults(const CS170::Vector::SortResult& results)
{
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
}
#else
void PrintSortResults(const CS170::Vector::SortResult&)
{
}
#endif

void TestSelectionSort1(int count)
{
  std::cout << "\n********** TestSelectionSort1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 random integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, 20));

  Print(a);
  CS170::Vector::SortResult results = a.selection_sort();

  PrintSortResults(results);
  Print(a);
}

void TestSelectionSort2(int count)
{
  std::cout << "\n********** TestSelectionSort2 **********\n";
  CS170::Vector a;

  std::cout << "push_back " << count << " integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  Print(a);
  CS170::Vector::SortResult results = a.selection_sort();
  PrintSortResults(results);
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(i);

  Print(a);
  results = a.selection_sort();
  PrintSortResults(results);
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(5);

  Print(a);
  results = a.selection_sort();
  PrintSortResults(results);
  Print(a);
}

void TestSelectionSortStress(int count)
{
  std::cout << "\n********** TestSelectionSortStress **********\n";
  CS170::Vector a;

  std::srand(6);
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, count));

  CS170::Vector::SortResult results = a.selection_sort();

  PrintSortResults(results);
  for (int i = 1; i < count; i *= 2)
    std::cout << a[i] << "  ";
  std::cout << std::endl;
  //Print(a);
}

void TestBubbleSort1(int count)
{
  std::cout << "\n********** TestBubbleSort1 **********\n";
  CS170::Vector a;

  std::srand(6);
  std::cout << "push_back 10 random integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, 20));

  Print(a);
  CS170::Vector::SortResult results = a.bubble_sort();

  PrintSortResults(results);
  Print(a);
}

void TestBubbleSort2(int count)
{
  std::cout << "\n********** TestBubbleSort2 **********\n";
  CS170::Vector a;

  std::cout << "push_back " << count << " integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  Print(a);
  CS170::Vector::SortResult results  = a.bubble_sort();
  PrintSortResults(results);
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(i);

  Print(a);
  results = a.bubble_sort();
  PrintSortResults(results);
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(5);

  Print(a);
  results = a.bubble_sort();
  PrintSortResults(results);
  Print(a);
}

void TestBubbleSortStress(int count)
{
  std::cout << "\n********** TestBubbleSortStress **********\n";
  CS170::Vector a;

  std::srand(6);
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, count));

  CS170::Vector::SortResult results = a.bubble_sort();

  PrintSortResults(results);
  for (int i = 1; i < count; i *= 2)
    std::cout << a[i] << "  ";
  std::cout << std::endl;
  //Print(a);
}

void TestBSearch1(int count)
{
  std::cout << "\n********** TestBSearch1 **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 10 random integers:\n";
  for (int i = 0; i < count; i++)
  {
    a.push_back(RandomInt(1000, 9999));
    b.push_back(a[i]);
  }

  Print(a);
  a.selection_sort();
  Print(a);

  for (unsigned i = 0; i < a.size(); i++)
  {
    int index = a.bsearch(b[i]);
    std::cout << "Index of " << b[i] << " is " << index << std::endl;
  }
}

void TestBSearchStress(int count)
{
  std::cout << "\n********** TestBSearchStress **********\n";
  CS170::Vector a;

  int *ia = new int[count];

  std::cout << "Generating...\n";
  for (int i = 0; i < count; i++)
    ia[i] = i;

  std::cout << "Shuffling...\n";
  Shuffle(ia, count);

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(ia[i]);

  //Print(a);
  a.selection_sort();
  //Print(a);

  std::cout << "Searching...\n";
  std::time_t start = std::clock();
  for (int i = 0; i < 1000; i++)
  {
    for (int j = 0; j < count; j++)
    {
      a.bsearch(ia[i]);
      //std::cout << "Index of " << ia[i] << " is " << index << std::endl;
    }
  }
  std::time_t end = std::clock();
  std::cout << "Done...\n";
  std::cout << "Elapsed time: " <<  (end - start) << std::endl;

  delete [] ia;
}

int main(void)
{
  TestSelectionSort1(10); 
  TestSelectionSort2(10); 
  TestBubbleSort1(10);  
  TestBubbleSort2(10); 
  TestBSearch1(10);
  TestBSearchStress(10000);
  TestBubbleSortStress(10000);
  TestSelectionSortStress(10000);

  return 0;
}
