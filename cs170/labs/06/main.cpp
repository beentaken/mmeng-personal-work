#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi
#include "List.h"

void TestInsert2(void)
{
  std::cout << "\n******************** TestInsert2 ********************\n";

  List list1;
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  int size = sizeof(numbers) / sizeof(*numbers);

  for (int i = 0; i < size; i++)
  {
    list1.Insert(numbers[i]);

    std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes) ";
    std::cout << "Inserting " << std::setw(2) << numbers[i] << ": ";
    std::cout << list1 << std::endl;
  }
}

void TestMerge(const int numbers1[], const int numbers2[], int size1, int size2)
{
  List list1;
  List list2;

    // Get the numbers into a sorted list
  for (int i = 0; i < size1; i++)
    list1.Insert(numbers1[i]);
 
    // Get the numbers into a sorted list
  for (int i = 0; i < size2; i++)
    list2.Insert(numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;

  std::cout << "Merge list2 into list1:\n";
  list1.Merge(list2);
  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;
}

void TestMerge1(void)
{
  std::cout << "\n******************** TestMerge1 ********************\n";

  const int numbers1[] = {12, 70, 21};
  const int numbers2[] = {67, 23, 88};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

void TestMerge2(void)
{
  std::cout << "\n******************** TestMerge2 ********************\n";

  const int numbers1[] = {12, 34, 21, 56, 38, 94, 27, 22};
  const int numbers2[] = {67, 23, 88, 19, 59, 10, 17, 30};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

void TestMerge3(void)
{
  std::cout << "\n******************** TestMerge3 ********************\n";

  const int numbers1[] = {12, 34, 21, 56};
  const int numbers2[] = {67, 23, 88, 19, 59, 10, 17, 30};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

void TestMerge4(void)
{
  std::cout << "\n******************** TestMerge4 ********************\n";

  const int numbers1[] = {12, 34, 21, 56, 38, 94, 27, 22};
  const int numbers2[] = {67, 23, 88};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

void TestMerge5(void)
{
  std::cout << "\n******************** TestMerge5 ********************\n";

  const int numbers1[] = {12, 34, 21, 56, 38, 94, 27, 22};
  const int numbers2[] = {0};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);

  TestMerge(numbers1, numbers2, size1, 0);
}

void TestMerge6(void)
{
  std::cout << "\n******************** TestMerge6 ********************\n";

  const int numbers1[] = {0};
  const int numbers2[] = {67, 23, 88, 19, 59, 10, 17, 30};
                        
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, 0, size2);
}

void TestMerge7(void)
{
  std::cout << "\n******************** TestMerge7 ********************\n";

  const int numbers1[] = {12, 34, 12, 56, 12, 12, 27, 22};
  const int numbers2[] = {12, 12, 88, 12, 59, 12, 17, 12};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  TestMerge(numbers1, numbers2, size1, size2);
}

void TestMerge8(void)
{
  std::cout << "\n******************** TestMerge8 ********************\n";

  const int numbers1[] = {12, 70, 21, 55, 56, 20, 21, 12, 12, 8, 43};
                        
  int size1 = sizeof(numbers1) / sizeof(*numbers1);

  std::cout << "Merging a list into itself...\n";
  TestMerge(numbers1, numbers1, size1, size1);
}



int main(int argc, char **argv)
{
  //TestInsert2(); 

  int test_num = 0;
  if (argc > 1)
    test_num = std::atoi(argv[1]);

  typedef void (*Test)(void);
  Test Tests[] = {
                    TestMerge1, // Test 1
                    TestMerge2, // Test 2
                    TestMerge3, // Test 3
                    TestMerge4, // Test 4
                    TestMerge5, // Test 5 
                    TestMerge6, // Test 6
                    TestMerge7, // Test 7
                    TestMerge8  // Test 8
                 };

  int num = sizeof(Tests) / sizeof(*Tests);
  if (test_num == 0)
  {
    for (int i = 0; i < num; i++)
      Tests[i]();
  }
  else if (test_num > 0 && test_num <= num)
    Tests[test_num - 1]();

}
