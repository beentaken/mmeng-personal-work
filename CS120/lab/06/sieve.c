#include <stdio.h> /* printf      */
#include <math.h>  /* sqrt        */
#include "sieve.h" /* TRUE, FALSE */

void init_array(int array[], int size)
{
	int i;

	array[0] = array[1] = FALSE;

	for (i = 2; i < size; ++i)
	{
		array[i] = TRUE;
	}
}

void sieve(int array[], int size)
{
	int i, j;

	init_array(array, size);

	for (i = 2; i < sqrt(size); ++i)
	{
		if (array[i])
		{
			for (j = i + i; j < size; j += i)
			{
				array[j] = FALSE;
			}
		}
	}
}

int twin_primes(const int primes[], int size)
{
	int total = 0;
	int i;

	for (i = 3; i < size-2; i += 2)
	{
		if (primes[i] == TRUE && primes[i + 2] == TRUE)
		{
			++total;

			printf("twin prime #%4i: %4i and %4i\n",
				total, i, i + 2);
		}
	}

	return total;
}

double brun_constant(const int primes[], int size)
{
	double brun = 0.0;
	int i;

	for (i = 3; i < size - 2; i += 2)
	{
		if (primes[i] == TRUE && primes[i + 2] == TRUE)
		{
			brun += 1.0 / i + 1.0 / (i + 2);
		}
	}

	return brun;
}

