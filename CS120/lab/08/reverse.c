#include <string.h>

void reverse_slice(char *array, int length)
{
	int i;

	for (i = 0; i < length - 1 - i; ++i)
	{
		char temp = array[i];
		array[i] = array[length - i - 1];
		array[length - 1 - i] = temp;
	}
}

int exponent(const int base, const int power)
{
	int i, total = 1;

	if (0 == power)
	{
		return 0;
	}

	for (i = 0; i < power; ++i)
	{
		total *= base;
	}

	return total;
}

int strtoint(const char string[])
{
	int i; /* Loop counter. */
	const int length = strlen(string); /* Length of the string. */
	int number = 0; /* Stores the number to return later. */
	int lower_limit = 0; /* Where to stop for the loop. */

	if ('-' == string[0])
	{
		lower_limit = 1;
	}

	for (i = length - 1; lower_limit <= i; --i)
	{
		int power = exponent(10, length - i - 1);
		if (0 == power)
			++power;

		number += (string[i] - '0') * power;
	}

	if (lower_limit)
		number *= -1;

	return number;
}

int count_digits(int number)
{
	int counter = 0; /* Running total. */

	while (number > 0)
	{
		number /= 10;
		++counter;
	}

	return counter;
}

void inttostr(int number, char string[])
{
	/* Goddammit I should just use
	 * sprintf(string, "%d", number);
	 */

	int i; /* Loop counter. */
	int is_negative = 0; /* Set to nonzero if it is a negative number. */
	int num_digits; /* How many digits are in the number? */

	memset(string, '\0', 12);

	if (number < 0)
	{
		is_negative = !is_negative;
		number *= -1;
	}
	else if (number == 0)
	{
		string[0] = '0';
		return;
	}
	
	num_digits = count_digits(number);

	for (i = 0; i < num_digits; ++i)
	{
		int power = exponent(10, i);
		if (0 == power)
			++power;
		string[i] = '0' + ((number/power) % 10);
	}

	if (is_negative)
	{
		string[num_digits] = '-';
		string[num_digits+1] = '\0';
	}

	reverse_slice(string, strlen(string));
}

void reverse_words2(char string[])
{
	int length = strlen(string);
	int i, j;

	reverse_slice(string, length);

	for (i = 0; i < length; ++i)
	{
		if (string[i] != ' ')
		{
			/* Find next space or end of string. */
			for (j = i; (j < length) && (string[j] != ' '); ++j);

			reverse_slice(string+i, j - i);

			i = j;
		}
	}
}

void reverse_words1(const char input[], char output[])
{
	strcpy(output, input);
	reverse_words2(output);
}


