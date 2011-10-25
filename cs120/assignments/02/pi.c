/*****************************************************************************
filename    pi.c
author      Marcus Meng
DP email    marcus.meng@digipen.edu
course      CS120
section     A
assignment  2
due date    October 18, 2009

Brief Description:
  This file contains two functions and any associated code necessary to
  approximate the value of pi using the area of a circle and the Leibniz
  method.
*****************************************************************************/

#include <math.h> /* sqrt */

/* The radius of the circle we are using for the approximation is always 1.0.
 */
#define RADIUS 1.0

/*****************************************************************************
 *    Function: height
 *
 * Description: Finds the height of a right-angle triangle given the length
 *              of the base and hypotenuse.
 *
 *      Inputs: base - length of the base.
 *              hypotenuse - length of the hypotenuse.
 *
 *     Outputs: The appropriate height for the triangle.
 ****************************************************************************/
double height(double base, double hypotenuse)
{
  return(sqrt(hypotenuse * hypotenuse - base * base));
}

/*****************************************************************************
 *    Function: circle_pi
 *
 * Description: Approximates pi using the area of a circle formula.
 *
 *      Inputs: rectangles - number of rectangles to use in the approximation
 *                           of the area under the quarter-circle.
 *
 *     Outputs: An approximate value of pi.
 ****************************************************************************/
double circle_pi(int rectangles)
{
  /* Iteration counter for the 'for' loop. */
  int i;

  /* sum accumulates the areas of the rectangles in the loop.
   * width is the base length of each rectangle. */
  double sum = 0.0, width = RADIUS/rectangles;

  for (i = 0; i < rectangles; ++i)
  {
    /* Add 0.5 to each width measurement to use midpoint instead of left
     * corner for the height calculation. */
    sum += width * height((0.5 + i) * width, RADIUS);
  }

  /* sqrt(RADIUS*RADIUS) is always 1, since radius is 1. So don't use it. */
  return(4.0 * sum);
}

/*****************************************************************************
 *    Function: leibniz_pi
 *
 * Description: Approximates pi using Leibniz's method.
 *              General series is pi/4 = 1 - 1/3 + 1/5 - 1/7...
 *
 *      Inputs: iterations - number of terms to calculate in the series.
 *
 *     Outputs: An approximate value for pi.
 ****************************************************************************/
double leibniz_pi(int iterations)
{
  /* First term is 1/1. */
  int denominator = 1;

  /* Accumulate the approximation in sum. */
  double sum = 0.0;

  while (denominator < iterations * 2)
  {
    /* denominator is always twice as large as the number of iterations
     * we've gone through, so make sure to cut it in half before testing
     * whether we're on an even or odd iteration. */
    if ((denominator / 2) % 2 == 0)
    {
      sum += 1.0 / denominator;
    }
    else
    {
      sum -= 1.0 / denominator;
    }
    
    denominator += 2;
  }

  /* Formula approximates pi/4, so make sure to scale the value back up
   * when it's returned. */
  return(sum * 4);
}

