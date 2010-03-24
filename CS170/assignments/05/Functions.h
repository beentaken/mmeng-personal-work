/*****************************************************************************/
/*!
\file   Functions.h
\author Marcus Meng
\par    email: marcus.meng@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment 5
\date   Marcus 24, 2010
\brief
	This file contains the prototypes for various templated range-based
	functions.
*/
/*****************************************************************************/

//---------------------------------------------------------------------------
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//---------------------------------------------------------------------------

namespace CS170
{
  /* 
   *  Other template function declarations for count, remove, replace, etc.
   *  go here. Make sure all of your declarations are sorted in alphabetical
   *  order. This includes putting the swap function above in the proper
   *  position.
   *
   */ 

	template <typename T> T *copy(const T *current, const T *end, T* destination);
	template <typename T> int count(const T *current, const T *end, const T &item);
	template <typename T> void display(const T *start, const T *end);
	template <typename T1, typename T2> bool equal(const T1 *current, const T1 *end, const T2 *to_compare);
	template <typename T> void fill(T *current, const T *end, const T &value);
	template <typename T1, typename T2> T1 *find(T1 *current, T1 *end, const T2 &item);
	template <typename T> T *max_element(T *current, T *end);
	template <typename T> T *min_element(T *current, T *end);
	template <typename T> T* remove(T *current, const T *end, const T &value);
	template <typename T> void replace(T *current, const T *end, const T &old_item, const T &new_item);
	template <typename T> T sum(const T *current, const T *end);
	template <typename T> void swap(T &left, T &right);
	template <typename T> void swap_ranges(T *current, const T *end, T* to_swap);
	#include "Functions.cpp"
}

#endif
//---------------------------------------------------------------------------
