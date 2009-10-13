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

#include <math.h> /* Need square root function. */

/* The radius of the circle we are using for the approximation is always 1.0.
 */
#define RADIUS 1.0

/* Calculates the height of a right-angle triangle given two measurements.
 *
 * base^2 + height^2 = hypotenuse^2, so height can be solved for.
 */
double height(double base, double hypotenuse)
{
    return(sqrt(hypotenuse*hypotenuse - base*base));
}

/* Approximates pi using the area of a circle.
 *
 * Compute the area with a sort of Riemann Sum, then solve for pi using the
 * equation A = pi * r^2.
 *
 * We are using the midpoint of the top of the rectangle for the
 * approximation.
 *
 * Note that we're only calculating a quarter circle's area. Final area
 * needs to be multiplied by 4.
 */
double circle_pi(int rectangles)
{
    int i;
	double sum = 0.0, width = RADIUS/rectangles;

	for (i = 0; i < rectangles; ++i)
	{
        sum += width * height((0.5+i)*width, RADIUS);
	}

    return(4.0 * sum);
}

/* Approximates pi using Leibniz's method.
 *
 * General series is pi/4 = 1 - 1/3 + 1/5 - 1/7...
 */
double leibniz_pi(int iterations)
{
	int denominator = 1;
	double sum = 0.0;

	while (denominator < iterations*2)
	{
	    if ((denominator/2) % 2 == 0)
		{
	        sum += 1.0 / denominator;
	    }
		else
		{
		    sum += -1.0 / denominator;
		}
		
		denominator += 2;
	}

    return(sum * 4);
}

