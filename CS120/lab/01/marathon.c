/******************************************************************************
  filename    marathon.c
  author      Marcus Meng, taken from the CS120 Website.
  DP email    marcus.meng@digipen.edu
  course      CS120
  section     A
  assignment  1
  due date    September 28, 2009

  Brief Description:
    Marathon program from the Fundamentals section of the CS120 Website.
        
******************************************************************************/

#include <stdio.h> /* printf */

#define YARDS_PER_MILE 1760
#define KILOS_PER_MILE 1.609

/* A marathon is 26 miles, 285 yards			*/
/* Prints the distance of a marathon in kilometers	*/
int main(void)
{
	int miles, yards;
	double kilometers;

	miles = 26;
	yards = 385;
	kilometers = (miles + (double)yards / YARDS_PER_MILE) * KILOS_PER_MILE;
	printf("A marathon is %f kilometers\n", kilometers);

	return 0;
}

