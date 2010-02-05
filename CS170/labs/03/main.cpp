#include <iostream> // cout, endl
#include <iomanip>  // setw
#include "list.h"

int main(void)
{
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

    // Find an existing value
  int value = 56;
  struct Node *node = FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n\n";
  else
    std::cout << "Value: " << node->number << " was not found.\n\n";

    // Find a non-existant value
  value = 123;
  node = FindItem(list1, value);
  if (node)
    std::cout << "Value: " << node->number << " was found.\n\n";
  else
    std::cout << "Value: " << value << " was not found.\n\n";

    // Release the nodes
  FreeList(list1);
  FreeList(list2);

    // Inserting
  list1 = 0;
  for (int i = 0; i < 5; i++)
  {
    AddToEnd(&list1, numbers[i]);
    std::cout << "List1 (" << std::setw(2) << Count(list1) << " nodes): ";
    PrintList(list1);
    std::cout << std::endl;
  }

  std::cout << "Inserting...\n";
  Insert(&list1, 91, 3);
  PrintList(list1);
  Insert(&list1, 92, 0);
  PrintList(list1);
  Insert(&list1, 93, 7);
  PrintList(list1);
  Insert(&list1, 94, 9);
  PrintList(list1);

  FreeList(list1);

  return 0;
}
