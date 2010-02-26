#include <iostream> // cout, endl
#include <iomanip>  // setw
#include "List.h"

void TestAdd(void)
{
  std::cout << "\n******************** TestAdd ********************\n";

  List list1;
  List list2; 
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  int size = sizeof(numbers) / sizeof(*numbers);

    // Create two lists
  for (int i = 0; i < size; i++)
  {
    list1.AddToEnd(numbers[i]);
    list2.AddToFront(numbers[i]);

    std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
    std::cout << list1 << std::endl;
    std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
    std::cout << list2 << std::endl;
    std::cout << std::endl;
  }
}

void TestFind(void)
{
  std::cout << "\n******************** TestFind ********************\n";

  List list1;
  const int numbers[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  int size = sizeof(numbers) / sizeof(*numbers);
  for (int i = 0; i < size; i++)
    list1.AddToEnd(numbers[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

    // Find an existing value
  int value = 56;
  Node *node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

  value = 22;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

  value = 59;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

    // Find a non-existant value
  value = 123;
  node = list1.FindItem(value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
}

void TestDelete1(void)
{
  std::cout << "\n******************** TestDelete1 ********************\n";

  List list1;
  const int numbers[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  int size = sizeof(numbers) / sizeof(*numbers);
  for (int i = 0; i < size; i++)
    list1.AddToEnd(numbers[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(56);
  std::cout << "Deleting: 56 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(22);
  std::cout << "Deleting: 22 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(59);
  std::cout << "Deleting: 59 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  list1.Delete(99);
  std::cout << "Deleting: 99 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;

  {
    const int numbers[] = {
                           23, 38, 94, 34, 
                           67, 56, 88, 19, 10
                          };
    int size = sizeof(numbers) / sizeof(*numbers);
    for (int i = 0; i < size; i++)
    {
      list1.Delete(numbers[i]);
      std::cout << "Deleting: " << numbers[i] << " (" << std::setw(2) 
                << list1.Count() << " nodes): ";
      std::cout << list1 << std::endl;
    }
    list1.Delete(99);
    std::cout << "Deleting: 99 (" << std::setw(2) << list1.Count() << " nodes): ";
    std::cout << list1 << std::endl;
  }
}

void TestDelete2(void)
{
  std::cout << "\n******************** TestDelete2 ********************\n";

  List list1;
  const int numbers1[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  for (int i = 0; i < size1; i++)
    list1.AddToEnd(numbers1[i]);

  List list2;
  const int numbers2[] = {
                         94, 23, 56, 22, 56, 19, 
                         67, 38, 34, 59
                        };
  int size2 = sizeof(numbers2) / sizeof(*numbers2);
  for (int i = 0; i < size2; i++)
    list2.AddToEnd(numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;

  list1.Delete(list2);
  std::cout << "List1 after deleting list2 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;
}

void TestConcat(void)
{
  std::cout << "\n******************** TestConcat ********************\n";

  List list1;
  List list2; 
  const int numbers1[] = {12, 34, 21, 56, 38, 94, 23};
  const int numbers2[] = {67, 56, 88, 19, 59, 10, 17};

  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  for (int i = 0; i < size1; i++)
    list1.AddToEnd(numbers1[i]);

  for (int i = 0; i < size2; i++)
    list2.AddToEnd(numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
  std::cout << list1 << std::endl;
  std::cout << "List2 (" << std::setw(2) << list2.Count() << " nodes): ";
  std::cout << list2 << std::endl;

  std::cout << "Adding both lists (" << std::setw(2) << list1.Count() << " nodes): ";
  list1.Concat(list2);

  std::cout << list1 << std::endl;
}

void TestInsert1(void)
{
  std::cout << "\n******************** TestInsert1 ********************\n";

  List list1;
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  for (int i = 0; i < 5; i++)
  {
    list1.AddToEnd(numbers[i]);
    std::cout << "List1 (" << std::setw(2) << list1.Count() << " nodes): ";
    std::cout << list1 << std::endl;
    std::cout << std::endl;
  }

  std::cout << "Inserting... 91 at position 3\n";
  list1.Insert(91, 3);
  std::cout << list1 << std::endl;
  std::cout << "Inserting... 92 at position 0\n";
  list1.Insert(92, 0);
  std::cout << list1 << std::endl;
  std::cout << "Inserting... 93 at position 7\n";
  list1.Insert(93, 7);
  std::cout << list1 << std::endl;
  std::cout << "Inserting... 94 at position 9\n";
  list1.Insert(94, 9);
  std::cout << list1 << std::endl;
}

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

int main(void)
{
  TestAdd();
  TestFind();
  TestInsert1();

  TestConcat();
  TestDelete1();
  TestDelete2();
  TestInsert2(); 
}
