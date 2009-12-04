#include <stdio.h>
#include <string.h>

void string_to_lower(char* string)
{
	char* iterator;

	for(iterator = string; *iterator != '\0'; iterator++)
	{
		tolower(*iterator);
	}
}

char* skip_whitespace(const char* string)
{
	while(string != '\0' && !isalpha(*string))
	{
		string++;
	}

	return string;
}

void proper_case(char* filename)
{
	FILE* working_file;

	working_file = fopen(working_file, "rt");

	if (working_file)
	{
		long file_length;
		char* buffer;
		char* iterator;
		fseek(working_file, 0, SEEK_END);
		file_length = ftell(working_file);
		fseek(working_file, 0, SEEK_SET);

		buffer = (char*)malloc(file_length+1);
		buffer[file_length] = '\0';

		string_to_lower(buffer);

		iterator = buffer;

		while (*iterator != '\0')
		{
			iterator = skip_whitespace(iterator);
			*iterator -= 'a' - 'A';

			iterator = strtok(iterator, ".,!");
		}
		fclose(working_file);

		puts(buffer);
	}
}

