/*******************************************************************************
filename	fibonacci.c
author		Marcus Meng
DP email	marcus.meng@digipen.edu
course		CS120
section		A
assignment	3
due date	October 9, 2009

Brief Description:
	This program displays all the fibonacci numbers up to the index specified
	by the user. The index must be between 2 and 46, inclusive.

*******************************************************************************/

#include <stdio.h> /* Just need printf and scanf for this. */
#include <math.h> /* Square root function. */

int get_input();
void print_header();
void fibonacci(int end_value);

int main(void)
{
	int input;
	input = get_input();
	
	if (input != 1)
	{
		fibonacci(input);
	}

	return(0);
}

/*
 * Gets input from user and returns it.
 * Ensures that it's between 1 and 46, inclusive.
 */
int get_input()
{
	int input;

	do
	{
		printf("Enter the Fibonacci number to calculate.\n");
		printf("The number must be an integer between 2 and 46. "
			"(Enter 1 to quit): ");
		scanf("%d", &input);
	} while(input < 1 || input > 46);

	return(input);
}

/*
 * Tosses out a nice looking header.
 */
void print_header()
{
	int i;

	printf("\n");
	printf("           Fibonacci        Fibonacci\n");
	printf(" N           number          quotient\n");
	printf("-------------------------------------\n");

	/* Stick the first two indices in the header, since they're always
	 * the same anyways.
	 */

	for (i = 0; i < 2; ++i)
	{
		printf("%2i%14i                  N/A\n", i, i);
	}
}

/*
 * Outputs a formatted fibonacci quotient.
 */
void fibonacci(int end_value)
{
	int i;
	double current_value = 1.0, previous_value = 1.0, temp = 0.0;

	print_header();

	/* Start from 2, since the first two indices are in the header. */

	for(i=2; i <= end_value; ++i)
	{
		printf("%2i%14.0f%21.16f\n", i, current_value,
			current_value/previous_value);

		temp = previous_value;
		previous_value = current_value;
		current_value = previous_value + temp;
	}
}

