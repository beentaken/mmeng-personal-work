/* Computes the volume of a sphere of fixed size.
 *
 * Marcus Meng
 */

#include <stdio.h>

int main(void)
{
	float radius = 10.0f;
	printf("Radius:\t%f\n", radius);
	printf("Volume:\t%f\n", 4.0f/3.0f * 3.14f * radius*radius*radius);

	return(0);
}

