/* Reformats a telephone number.
 *
 * Marcus Meng
 */

#include <stdio.h>

int main(void)
{
	int area, prefix, suffix;

	printf("Enter phone number [(xxx) xxx-xxxx]: ");
	scanf("(%d) %d-%d", &area, &prefix, &suffix);

	printf("You entered %3.3d.%3.3d.%4.4d\n", area, prefix, suffix);

	return(0);
}

