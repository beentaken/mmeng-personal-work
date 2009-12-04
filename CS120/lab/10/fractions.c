#include "fractions.h"

int GCD(int a, int b)
{
	if (a % b)
	{
		return GCD(b, a % b);
	}
	return b;
}

struct FRACTION add_fractions(const struct FRACTION *a,
				const struct FRACTION *b)
{
	int new_numerator = a->numerator * b->denominator
				+ b->numerator * a->denominator;
	int new_denominator = a->denominator * b->denominator;
	int gcd;
	struct FRACTION new_fraction;
	
	if (new_numerator > new_denominator)
	{
		gcd = GCD(new_numerator, new_denominator);
	}
	else
	{
		gcd = GCD(new_denominator, new_numerator);
	}

	new_fraction.numerator = new_numerator / gcd;
	new_fraction.denominator = new_denominator / gcd;

	if (new_fraction.denominator < 0)
	{
		new_fraction.denominator *= -1;
		new_fraction.numerator *= -1;
	}

	return new_fraction;
}

