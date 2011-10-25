/* Does some formatting on input.
 *
 * Marcus Meng
 */

#include <stdio.h>

int main(void)
{
	int item, purchase_date_month, purchase_date_day, purchase_date_year;
	float unit_price;
	
	printf("Enter item number: ");
	scanf("%d", &item);

	printf("Enter unit price: ");
	scanf("%f", &unit_price);

	printf("Enter purchase date (mm/dd/yyyyy): ");
	scanf("%2.2d/%2.2d/%4.4d", &purchase_date_month, &purchase_date_day, &purchase_date_year);

	printf("Item\t\tUnit\t\tPurchase\n");
	printf("\t\tPrice\t\tDate\n");
	printf("%d\t\t$%7.2f\t%d/%d/%d\n", item, unit_price, purchase_date_month, purchase_date_day, purchase_date_year);

	return(0);
}

