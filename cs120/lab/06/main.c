#include <stdio.h>
#include "sieve.h"

#define SIZE 10001

int main(void)
{
	int array[SIZE];
	int count = 0;
	double bruns;
	int i;

	sieve(array, SIZE - 1);

	for (i = 0; i < SIZE; i++)
	{
		if (array[i] == TRUE)
		{
		 count++;
		 #if 1
		 	printf("Prime #%04i:  %4i\n", count, i);
		#endif
		}
	}

	printf("%i primes found between 0 and %i.\n", count, SIZE - 1);

	count = twin_primes(array, SIZE - 1);
	printf("%i twin primes found between 0 and %i.\n", count, SIZE - 1);

	bruns = brun_constant(array, SIZE - 1);
	printf("Brun's constant with %i twin primes is %1.12f.\n", count, bruns);

	return 0;
}

