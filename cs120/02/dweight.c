/* Dimensional weight program from Chapter 2.
 * Modified to take user input.
 *
 * Marcus Meng
 */

#include <stdio.h>

#define INCHES_PER_POUND 166

int main(void)
{
	int height, length, width;

	printf("Enter the height:\t");
	scanf("%d", &height);
	printf("Enter the length:\t");
	scanf("%d", &length);
	printf("Enter the width:\t");
	scanf("%d", &width);

	int volume = height*length*width;

	printf("Dimensions:\t\t\t%dx%dx%d\n", length, width, height);
	printf("Volume (cubic inches):\t\t%d\n", volume);
	printf("Dimensional weight (pounds):\t%d\n", (volume+INCHES_PER_POUND-1)/INCHES_PER_POUND);
	
	return(0);
}

