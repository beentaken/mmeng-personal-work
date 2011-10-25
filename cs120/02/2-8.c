/* Calculates remaining balance after each of three payments at user-defined interest rates.
 *
 * Marcus Meng
 */

#include <stdio.h>

int main(void)
{
	float loan, rate, monthly;

	printf("Enter amount of loan: ");
	scanf("%f", &loan);
	printf("Enter interest rate: ");
	scanf("%f", &rate);
	printf("Enter monthly payment: ");
	scanf("%f", &monthly);

	rate=rate/100/12+1;

	loan*=rate;
	loan-=monthly;

	printf("Balance remaining after first payment: %.2f\n", loan);
	loan*=rate;
	loan-=monthly;
	printf("Balance remaining after second payment: %.2f\n", loan);
	loan*=rate;
	loan-=monthly;
	printf("Balance remaining after third payment: %.2f\n", loan);

	return(0);
}

