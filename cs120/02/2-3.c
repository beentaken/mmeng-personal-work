/* Computes the volume of a sphere of arbitrary size.
 *
 * Marcus Meng
 */

#include <stdio.h>

int main(void)
{
	float radius;

	do
	{
		printf("Please enter the radius of the sphere: ");
		scanf("%f", &radius);
	} while (radius < 0);

	printf("Radius:\t%f\n", radius);
	printf("Volume:\t%f\n", 4.0f/3.0f * 3.14f * radius*radius*radius);

	return(0);
}

