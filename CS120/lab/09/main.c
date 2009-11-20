#include <stdio.h> /* printf */

/* Prototype for the dumper function */
void dump(const char *filename);

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: %s filename\n", argv[0]);
		return -1;
	}

	dump(argv[1]);

	 return 0;
}

