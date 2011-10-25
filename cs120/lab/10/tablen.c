#include <stdio.h>
#include <string.h>

#include "tablen.h"

static int count_tabs(const char* line)
{
	int num_tabs = 0;
#ifndef NDEBUG
	printf("Entering count_tabs.\n");
#endif
	for (num_tabs = 0; *line != '\0'; line++)
	{
		if (*line == '\t')
		{
			num_tabs++;
		}
	}

	return num_tabs;
}

void show_tab_info(char* filename)
{
	char line[MAX_LINE_LENGTH+1];
	FILE *working_file;
#ifndef NDEBUG
	printf("Entering show_tab_info.\n");
#endif
	working_file = fopen(filename, "rt");

	if (working_file)
	{
		int linecount = 0;
		int tabcount = 0;
#ifndef NDEBUG
		printf("File opened, entering fgets loop.\n");
#endif
		while (fgets(line, MAX_LINE_LENGTH, working_file))
		{
			int tabs = count_tabs(line);

			line[strlen(line)-2] = '\0';

			++linecount;

			if (tabs)
			{
#ifndef NDEBUG
				printf("Tabs found, printing line.\n");
#endif
				printf("#%3d: (tabs: %d) |%s|\n",
					linecount, tabs, line);
				tabcount += tabs;
			}
		}
		fclose(working_file);

		if (tabcount > 0)
		{
			printf("*****  TABS IN USE  *****: "
				"Number of tabs in the file"
				" is %d.\n", tabcount);
		}
	}
}

void show_length_info(char* filename)
{
	char line[MAX_LINE_LENGTH+1];
	FILE* working_file;

	working_file = fopen(filename, "rt");

	if (working_file)
	{
		int linecount = 0;
		int longest_line = 0;
		int longest_line_length = 0;
		int long_lines = 0;

		while(fgets(line, MAX_LINE_LENGTH, working_file))
		{
			int length;
			line[strlen(line)-2] = '\0';
			length = strlen(line);
			++linecount;

			if (length > 80)
			{
				++long_lines;
				if (length > longest_line)
				{
					longest_line = linecount;
					longest_line_length = length;
				}
				printf("#%3d: (%3d) |%s|\n",
					linecount,
					length,
					line);
			}
		}

		if (long_lines > 0)
		{
			printf("***** LINE TOO LONG *****: %d lines longer"
				" than 80. Longest line is %d at %d chars.\n",
				long_lines, longest_line,
				longest_line_length);
		}
		fclose(working_file);
	}
}

