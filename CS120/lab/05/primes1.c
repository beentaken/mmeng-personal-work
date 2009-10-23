#include <stdio.h> /* printf */

#define FALSE 0
#define TRUE 1

int is_prime(int number)
{
	/* 1 is never a prime. */
	if (1 == number)
	{
		return FALSE;
	}

	/* 2 always is prime. */
	if (2 == number)
	{
		return TRUE;
	}

	if (number % 2 != 0)
	{
		int i;

		for (i = 3; i < number / 2; ++i)
		{
			if (number % i == 0)
			{
				return FALSE;
			}
		}
	}
	else
	{
		/* number is even, diiiiie. */
		return FALSE;
	}

	/* Didn't hit any of the triggers, must be prime. */
	return TRUE;
}

void conjecture(int low, int high)
{
	int first, second;

	/* Can't have low be an even number. */
	if (low % 2 != 0)
	{
		++low;
	}

	for ( ; low <= high; low += 2)
	{
		for (first = 2; first <= low; first += 2)
		{
			if (is_prime(first))
			{
				for (second = first; second <= low; second += 2)
				{
					/* If it matches, print it out and
					 * break to avoid duplicate sums. */
					if (is_prime(second) && (first + second) == low)
					{
						printf("%3i = %3i + %3i\n", low, first, second);
						break;
					}

					/* 2 becomes 3 after the first loop if 2 didn't
					 * trigger anything. */
					if (2 == second)
					{
						second = 1;
					}
				}

				/* Break to avoid duplicate sums. */
				if (first + second == low)
				{
					break;
				}
			}

			/* 2 becomes 3 after the first loop if 2 didn't trigger
			 * anything */
			if (2 == first)
			{
				first = 1;
			}
		}
	}
}

