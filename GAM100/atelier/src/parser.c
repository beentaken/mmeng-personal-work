#include <stdio.h>
#include "parser.h"

void test_print()
{
	printf("This is a test print.\n");
}

struct COMMAND get_command()
{
	struct COMMAND current_input;
	printf("Enter a command: ");

	current_input.order = QUIT;
	current_input.value = 0;

	return current_input;
}

