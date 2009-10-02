#include <stdio.h>
#include <math.h>

int main(void)
{
	float number1, number2, number3;
	
	printf("Enter 3 numbers between 0 and 9.999: ");
	scanf("%f %f %f", &number1, &number2, &number3);

	printf("\nNumber\tsin\tcos\ttan\tatan\n");
	printf("-------------------------------------------\n");

	printf("%.5f\t%.3f\t%.3f\t%.3f\t%.3f\n",
		number1, sin(number1), cos(number1),
		tan(number1), atan(number1));
	
	printf("%.5f\t%.3f\t%.3f\t%.3f\t%.3f\n",
		number2, sin(number2), cos(number2),
		tan(number2), atan(number2));
	
	printf("%.5f\t%.3f\t%.3f\t%.3f\t%.3f\n",
		number3, sin(number3), cos(number3),
		tan(number3), atan(number3));

        return(0);
}

