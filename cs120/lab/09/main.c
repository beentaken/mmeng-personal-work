#include <stdio.h> /* printf */

/* Prototype for the dumper function */
void dump(const char *filename);

int main(int argc, char **argv)
{
	int i; /* Loop counter. */

	if (argc < 2)
	{
		printf("Usage: %s filename\n", argv[0]);
		return -1;
	}

	for ( i = 1; i < argc; ++i )
	{
		dump(argv[i]);
	}

	 return 0;
}

