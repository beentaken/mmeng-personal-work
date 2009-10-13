/******************************************************************************
filename    main.c
author      Artie Fufkin
DP email    afufkin2@digipen.edu
course      CS120
section     F
assignment  7
due date    11/26/2037

Brief Description:
  This file contains the main function for the pi assignment.

******************************************************************************/
#include <stdio.h> /* scanf, printf */

double circle_pi(int rectangles);  /* Calculates PI using a quarter circle */
double leibniz_pi(int iterations); /* Calculates PI using a series         */

int main(void)
{
  int iterations; /* loop counter */

    /* Print out table header */
  printf("Approximations for pi\n");
  printf("Iterations      Circle Method   Leibniz Method\n");
  printf("----------------------------------------------\n");

    /* Print out values for each set of numbers */
  for (iterations = 1; iterations <= 1000000; iterations *= 10)
  {
      /* Calculate PI with both methods */
    double pi_circle = circle_pi(iterations);
    double pi_leibniz = leibniz_pi(iterations);

      /* Print the results of the calculations */
    printf("%10i%20.12f%16.12f\n", iterations, pi_circle, pi_leibniz);
  }

  return 0; /* Return to the OS */
}
