#include <iostream> // cout, endl
#include <iomanip>  // setw
#include "list.h"

void TestAdd(void)
{
  std::cout << "\n******************** TestAdd ********************\n";

  struct Node *list1 = 0;
  struct Node *list2 = 0; 
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  int size = sizeof(numbers) / sizeof(*numbers);

    // Create two lists
  for (int i = 0; i < size; i++)
  {
    AddToEnd(&list1, numbers[i]);
    AddToFront(&list2, numbers[i]);

    std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
    PrintList(list1);
    std::cout << "List2 (" << std::setw(2) << Count(list2) << " nodes): ";
    PrintList(list2);
    std::cout << std::endl;
  }

  FreeList(list1);
  FreeList(list2);
}

void TestFind(void)
{
  std::cout << "\n******************** TestFind ********************\n";

  struct Node *list1 = 0;
  const int numbers[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  int size = sizeof(numbers) / sizeof(*numbers);
  for (int i = 0; i < size; i++)
    AddToEnd(&list1, numbers[i]);

  std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

    // Find an existing value
  int value = 56;
  struct Node *node = FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

  value = 22;
  node = FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

  value = 59;
  node = FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n";

    // Find a non-existant value
  value = 123;
  node = FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n";
  else
    std::cout << "Value: " << value << " was not found.\n";

  std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

  FreeList(list1);
}

void TestDelete1(void)
{
  std::cout << "\n******************** TestDelete1 ********************\n";

  struct Node *list1 = 0;
  const int numbers[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  int size = sizeof(numbers) / sizeof(*numbers);
  for (int i = 0; i < size; i++)
    AddToEnd(&list1, numbers[i]);

  std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

  Delete(&list1, 56);
  std::cout << "Deleting: 56 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

  Delete(&list1, 22);
  std::cout << "Deleting: 22 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

  Delete(&list1, 59);
  std::cout << "Deleting: 59 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

  Delete(&list1, 99);
  std::cout << "Deleting: 99 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);

  {
    const int numbers[] = {
                           23, 38, 94, 34, 
                           67, 56, 88, 19, 10
                          };
    int size = sizeof(numbers) / sizeof(*numbers);
    for (int i = 0; i < size; i++)
    {
      Delete(&list1, numbers[i]);
      std::cout << "Deleting: " << numbers[i] << " (" << std::setw(2) 
                << Count(list1) << " nodes): ";
      PrintList(list1);
    }
    Delete(&list1, 99);
    std::cout << "Deleting: 99 (" << std::setw(2) << Count(list1) << " nodes): ";
    PrintList(list1);
  }
  FreeList(list1);
}

void TestDelete2(void)
{
  std::cout << "\n******************** TestDelete1 ********************\n";

  struct Node *list1 = 0;
  const int numbers1[] = {
                         22, 23, 38, 94, 56, 34, 
                         67, 56, 88, 19, 10, 59
                        };
  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  for (int i = 0; i < size1; i++)
    AddToEnd(&list1, numbers1[i]);

  struct Node *list2 = 0;
  const int numbers2[] = {
                         94, 23, 56, 22, 56, 19, 
                         67, 38, 34, 59
                        };
  int size2 = sizeof(numbers2) / sizeof(*numbers2);
  for (int i = 0; i < size2; i++)
    AddToEnd(&list2, numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);
  std::cout << "List2 (" << std::setw(2) << Count(list2) << " nodes): ";
  PrintList(list2);

  Delete(&list1, list2);
  std::cout << "List1 after deleting list2 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);
  std::cout << "List2 (" << std::setw(2) << Count(list2) << " nodes): ";
  PrintList(list2);

  FreeList(list1);  
  FreeList(list2);  
}

void TestConcat(void)
{
  std::cout << "\n******************** TestConcat ********************\n";

  struct Node *list1 = 0;
  struct Node *list2 = 0; 
  const int numbers1[] = {12, 34, 21, 56, 38, 94, 23};
  const int numbers2[] = {67, 56, 88, 19, 59, 10, 17};

  int size1 = sizeof(numbers1) / sizeof(*numbers1);
  int size2 = sizeof(numbers2) / sizeof(*numbers2);

  for (int i = 0; i < size1; i++)
    AddToEnd(&list1, numbers1[i]);

  for (int i = 0; i < size2; i++)
    AddToEnd(&list2, numbers2[i]);

  std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
  PrintList(list1);
  std::cout << "List2 (" << std::setw(2) << Count(list2) << " nodes): ";
  PrintList(list2);

  std::cout << "Adding both lists (" << std::setw(2) << Count(list1) << " nodes): ";
  Concat(&list1, list2);
  FreeList(list2);

  PrintList(list1);
  FreeList(list1);
}

void TestInsert1(void)
{
  std::cout << "\n******************** TestInsert1 ********************\n";

  struct Node *list1 = 0;
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  for (int i = 0; i < 5; i++)
  {
    AddToEnd(&list1, numbers[i]);
    std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
    PrintList(list1);
    std::cout << std::endl;
  }

  std::cout << "Inserting... 91 at position 3\n";
  Insert(&list1, 91, 3);
  PrintList(list1);
  std::cout << "Inserting... 92 at position 0\n";
  Insert(&list1, 92, 0);
  PrintList(list1);
  std::cout << "Inserting... 93 at position 7\n";
  Insert(&list1, 93, 7);
  PrintList(list1);
  std::cout << "Inserting... 94 at position 9\n";
  Insert(&list1, 94, 9);
  PrintList(list1);

  FreeList(list1);
}

void TestInsert2(void)
{
  std::cout << "\n******************** TestInsert2 ********************\n";

  struct Node *list1 = 0;
  const int numbers[] = {
                         12, 34, 21, 56, 38, 94, 23, 22, 
                         67, 56, 88, 19, 59, 10, 17
                        };
  int size = sizeof(numbers) / sizeof(*numbers);

  for (int i = 0; i < size; i++)
  {
    Insert(&list1, numbers[i]);

    std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes) ";
    std::cout << "Inserting " << std::setw(2) << numbers[i] << ": ";
    PrintList(list1);
  }

  FreeList(list1);
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
