/******************************************************************************
 * ***************************************************************************/

void reverse_array(int a[], int size)
{
	int temp, i;

	for (i = 0; i < size - i - 1; ++i)
	{
		temp = a[i];
		a[i] = a[size - i - 1];
		a[size - i - 1] = temp;
	}
}

void add_arrays(const int a[], const int b[], int c[], int size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		c[i] = a[i] + b[i];
	}
}

void scalar_multiply(int a[], int size, int multiplier)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		a[i] *= multiplier;
	}
}

int dot_product(const int a[], const int b[], int size)
{
	int sum = 0;
	int i;

	for (i = 0; i < size; ++i)
	{
		sum += a[i] * b[i];
	}

	return sum;
}

void cross_product(const int a[], const int b[], int c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = -(b[2] * a[0] - b[0] * a[2]);
	c[2] = a[0] * b[1] - a[1] * b[0];
}

