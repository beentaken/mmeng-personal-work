#include <stdio.h> /* printf */

/* Gets the digit of number in the place specified. */
int get_digit(int number, int place)
{
	while (place > 1)
	{
		number /= 10;
		--place;
	}

	return(number % 10);
}

void print_cubes(void)
{
	int i, j;

	for (i = 100; i < 1000; ++i)
	{
		int sum;
		int digits[3];

		for (j = 0; j < 3; ++j)
		{
			digits[j] = get_digit(i, j+1);
			digits[j] = digits[j] * digits[j] * digits[j];
		}
		
		sum = digits[0] + digits[1] + digits[2];

		if (sum == i)
		{
			printf("%d has the cube property. (%d + %d + %d)\n",
				i, digits[2], digits[1], digits[0]);
		}
	}
}

/* Returns 0 if the three numbers passed in are not a triple,
 * and a nonzero number otherwise. */
int test_pythagorean_triple(int a, int b, int c)
{
	return((a * a) + (b * b) == (c * c));
}

/* Just to print out everything formatted nicely. */
void print_formatted_triple(int number_found, int a, int b, int c)
{
	printf("Triple #%3d:%4d,%3d,%3d -->%5d +%5d = %4d\n",
		number_found, a, b, c,
		a * a, b * b, c * c);
}

void print_pythagorean_triples(int low, int high)
{
	/* i, j, and k are just loop counters.
	 * number_found is incremented whenever we find another
	 * pythagorean triple. */
	int i, j, k, number_found = 0;

	for (i = low; i < high; ++i)
	{
		for (j = i; j < high; ++j)
		{
			for (k = j; k < high; ++k)
			{
				/* Test all permutations of i, j, and k. */
				if (test_pythagorean_triple(i, j, k))
				{
					++number_found;
					print_formatted_triple(number_found, i, j, k);
				}
			}
		}
	}
}

