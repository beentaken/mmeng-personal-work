#include "parser.h"

void test_print()
{
	printf("This is a test print.\n");
}

struct COMMAND get_command()
{
	char input[MAX_INPUT_LENGTH + 1];
	char* next_token;
	char delims[] = " \t";
	struct COMMAND current_input;
	printf("Enter a command: ");

	fgets(input, MAX_INPUT_LENGTH, stdin);

	next_token = strtok(input, delims);

	if (!next_token)
	{
		current_input.order = INVALID;
		current_input.value = 0;

		return current_input;
	}

	switch (tolower(next_token[0]))
	{
		case 'q':
			current_input.order = QUIT;
			break;
		case 'c':
			current_input.order = CREATE;
			break;
	}

	next_token = strtok(NULL, delims);

	if (next_token)
	{
		current_input.value = atoi(next_token);
	}
	else
	{
		current_input.value = 0;
	}

	return current_input;
}

