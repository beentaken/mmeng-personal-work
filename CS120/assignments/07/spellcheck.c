/*******************************************************************************
  FILE HEADER
*******************************************************************************/
#include <string.h> /* isalpha,  strlen */                                     
#include <stdio.h>  /* FILE, fopen, fgets, fclose */

/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h" 

char *mystrupr(char *string)
{
	char * current_letter = string;
	while(*current_letter)
	{
		if(*current_letter >= 'a' && *current_letter <= 'z')
		{
			*current_letter -= ('a' - 'A');
		}
		current_letter++;
	}

	return string;
}

int info(const char *dictionary, int *shortest, int *longest, int *num_words)
{
	FILE *working_file = fopen(dictionary, "rt"); /* Current dictionary. */
	char current_word[LONGEST_WORD];
	if (working_file == NULL)
	{
		return FILE_ERR_OPEN;
	}

	*shortest = LONGEST_WORD;
	*longest = 0;
	*num_words = 0;

	fgets(current_word, LONGEST_WORD, working_file);

	while (current_word != NULL)
	{
		int length;
		current_word[strlen(current_word)] = '\0';
		length = strlen(current_word);

		++(*num_words);

		if (length > *longest)
		{
			*longest = length;
		}
		if (length < *shortest)
		{
			*shortest = length;
		}

		fgets(current_word, LONGEST_WORD, working_file);
	}

	return FILE_OK;
}

int spell_check(const char *dictionary, const char *word)
{
	FILE* working_file = fopen(dictionary, "rt"); /* Current dictionary. */
	char current_word[LONGEST_WORD];

	if (working_file == NULL)
	{
		return FILE_ERR_OPEN;
	}

	fgets(current_word, LONGEST_WORD, working_file);

	while (current_word != NULL)
	{
		mystrupr(current_word);
		current_word[strlen(current_word)] = '\0';
		if (strcmp(current_word, word))
		{
			fclose(working_file);
			return WORD_OK;
		}

		fgets(current_word, LONGEST_WORD, working_file);
	}

	fclose(working_file);

	return WORD_BAD;
}

int word_lengths(const char *dictionary, int lengths[], int count)
{
	FILE* working_file = fopen(dictionary, "rt"); /* Current dictionary. */
	char current_word[LONGEST_WORD];
	
	if (working_file == NULL)
	{
		return FILE_ERR_OPEN;
	}

	memset(lengths, sizeof(int), sizeof(int) * count);

	fgets(current_word, LONGEST_WORD, working_file);
	current_word[strlen(current_word)] = '\0';

	while (current_word != NULL)
	{
		int length = strlen(current_word);

		if (length < count)
		{
			++lengths[length];
		}

		fgets(current_word, LONGEST_WORD, working_file);
		current_word[strlen(current_word)] = '\0';
	}

	fclose(working_file);

	return FILE_OK;
}

int words_starting_with(const char *dictionary, char letter)
{
	FILE* working_file = fopen(dictionary, "rt"); /* Current dictionary. */
	char current_word[LONGEST_WORD]; /* Stores current input. */
	int count = 0; /* Accumulates the running total of words found. */

	if (working_file == NULL)
	{
		return FILE_ERR_OPEN;
	}

	if (letter >= 'a' && letter <= 'z')
	{
		letter -= ('a' - 'A');
	}

	fgets(current_word, LONGEST_WORD, working_file);
	mystrupr(current_word);

	while (current_word != NULL)
	{
		if (current_word[0] == letter)
		{
			++count;
		}
		else
		{
			if (count)
			{
				break;
			}
		}

		fgets(current_word, LONGEST_WORD, working_file);
		mystrupr(current_word);
	}

	fclose(working_file);

	return count;
}

