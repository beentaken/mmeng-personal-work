/* Fills out a dollar amount with 20, 10, 5, and 1 dollar bills.
 *
 * Marcus Meng
 */

#include <stdio.h>

int main(void)
{
	int amount;
	printf("Enter a dollar amount: ");
	scanf("%d", &amount);

	int twenty = 0, ten = 0, five = 0;

	twenty = amount / 20;
	amount %= 20;

	ten = amount / 10;
	amount %= 10;

	five = amount / 5;
	amount %= 5;

	printf("$20 bills: %d\n", twenty);
	printf("$10 bills: %d\n", ten);
	printf(" $5 bills: %d\n", five);
	printf(" $1 bills: %d\n", amount);

	return(0);
}

