/******************************************************************************/
/*!
\file   List.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment #4
\date   March 3, 2010
\brief
	This file contains the prototypes for the various functions dealing
	with the List class.
*/
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // ostream

namespace CS170
{

  class List
  {
    public:
        // Three constructors
        // Destructor
	List(void);
	List(const List& to_copy);
	List(const int* array, const int size);
	~List(void);
        
        // Six methods:
        //   push_front, adds the item to the front of the list
        //   push_back, adds the item to the end of the list
        //   pop_front, removes the first item in the list
        //   size, returns the number of items in the list
        //   empty, returns true if empty, else false
        //   clear, clears the list (removes all of the nodes)
	void push_front(const int new_value);
	void push_back(const int new_value);
	int pop_front(void);
	int size(void) const;
	bool empty(void) const;
	void clear(void);

        // Five operators: 
        //   operator=
        //   operator+=
        //   operator+
        //   operator[] (2 of these)
	List& operator=(const List& rhs);
	List& operator+=(const List& rhs);
	List operator+(const List& rhs) const;
	int& operator[](const int index);
	int operator[](const int index) const;

        // Output operator for printing lists (<<)
      friend std::ostream & operator<<(std::ostream & os, const List &list);

        // Returns the number of Lists that have been created
      static int object_count(void);

    private:
      
        // used to build a linked list of integers
      struct Node
      {
        Node *next;  // pointer to the next Node
        int data;    // the actual data in the node
      };

      Node *head_; // pointer to the head of the list
      Node *tail_; // pointer to the last node
      int size_;   // number of items on the list

      static int object_count_;       // number of Lists created
      Node *new_node(int data) const; // allocate node, initialize data/next
  };

} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
