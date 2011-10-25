/* function declarations */
void print_cubes(void);
void print_pythagorean_triples(int low, int high);

int main(void)
{
	/* Print all of the integers with the cube property */
	print_cubes();

	/* Print all of the triples from 1 to 100 */
	print_pythagorean_triples(1, 100);

	return 0;
}

