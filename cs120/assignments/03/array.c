/******************************************************************************
filename    array.c
author      Marcus Meng
DP email    marcus.meng@digipen.edu
course      CS120
section     A
assignment  3
due date    November 4, 2009

Brief Description:
  Contains various calculation functions for working on integer arrays.
******************************************************************************/

/******************************************************************************
   Function: reverse_array

Description: Given an array, it will reverse it.

     Inputs: a - the array to reverse.
             size - the size of a.

    Outputs: a is reversed.
******************************************************************************/
void reverse_array(int a[], int size)
{
  int temp, i;

  for (i = 0; i < size - i - 1; ++i)
  {
    /* Swap a[i] with a[size - 1 - i]. */
    temp = a[i];
    a[i] = a[size - i - 1];
    a[size - i - 1] = temp;
  }
}

/******************************************************************************
   Function: add_arrays

Description: Given two arrays of equal size, puts the sum of the elements of
             the first two arrays into the elements of the third array.

     Inputs: a - First array to add.
             b - Second array to add.
             c - Array to put results in.
             size - Size of the arrays used.

    Outputs: c contains the sum of the elements of the first two arrays.
******************************************************************************/
void add_arrays(const int a[], const int b[], int c[], int size)
{
  int i;

  for (i = 0; i < size; ++i)
  {
    c[i] = a[i] + b[i];
  }
}

/******************************************************************************
   Function: scalar_multiply

Description: Multiplies all elements of an array by a factor.

     Inputs: a - The array to scale.
             size - the size of the array.
             multiplier - the factor to scale the elements by.

    Outputs: a is scaled.
******************************************************************************/
void scalar_multiply(int a[], int size, int multiplier)
{
  int i;

  for (i = 0; i < size; ++i)
  {
    a[i] *= multiplier;
  }
}

/******************************************************************************
   Function: dot_product

Description: Calculates the dot product of two given integer arrays.

     Inputs: a - the first array.
             b - the second array.
             size - the size of arrays a and b.

    Outputs: The dot product (int) of the two arrays.
******************************************************************************/
int dot_product(const int a[], const int b[], int size)
{
  int sum = 0;
  int i;

  for (i = 0; i < size; ++i)
  {
    sum += a[i] * b[i];
  }

  return sum;
}

/******************************************************************************
   Function: cross_product

Description: Calculates the cross product of two given arrays.

     Inputs: a - the first array.
             b - the second array.
             c - stores the output of the function.

    Outputs: c contains the resulting vector.
******************************************************************************/
void cross_product(const int a[], const int b[], int c[])
{
  c[0] =   a[1] * b[2] - a[2] * b[1];
  c[1] = -(b[2] * a[0] - b[0] * a[2]);
  c[2] =   a[0] * b[1] - a[1] * b[0];
}

