////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

struct Node
{
  int number; // data portion
  Node *next; // pointer portion
};

  // Adds a node to the end of the list
void AddToEnd(struct Node **ppList, int value);

  // Adds a node to the front of the list
void AddToFront(struct Node **ppList, int value);

  // Returns the number of nodes in the list
int Count(struct Node *list);

  // Frees (deletes) all of the nodes in the list
void FreeList(struct Node *pList);

  // Prints all of the nodes values
void PrintList(struct Node *list);

  // Inserts a new node at the specified position
void Insert(struct Node **ppList, int value, int position);

  // Searches a linked list for a value and returns the node
  // Returns NULL if the value isn't found
struct Node *FindItem(struct Node *list, int value);

void Delete(struct Node **ppList, int value);

void Concat(struct Node **Destination, struct Node *Source);

void Delete(struct Node **ppList, struct Node *Items);

void Insert(struct Node **ppList, int value);

#endif // LIST_H
