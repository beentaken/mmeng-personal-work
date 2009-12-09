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

	/* Initialize stuff to sane values. */
	*shortest = LONGEST_WORD;
	*longest = 0;
	*num_words = 0;

	while (fgets(current_word, LONGEST_WORD, working_file))
	{
		int length;

		current_word[strlen(current_word) - 1] = '\0';
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
	}

	fclose(working_file);

	return FILE_OK;
}

int spell_check(const char *dictionary, const char *word)
{
	FILE* working_file = fopen(dictionary, "rt"); /* Current dictionary. */
	char current_word[LONGEST_WORD];
	char testing_word[LONGEST_WORD];

	if (working_file == NULL)
	{
		return FILE_ERR_OPEN;
	}

	strcpy(testing_word, word);
	mystrupr(testing_word);

	while (fgets(current_word, LONGEST_WORD, working_file))
	{
		mystrupr(current_word);
		current_word[strlen(current_word) - 1] = '\0';
		if (!strcmp(current_word, testing_word))
		{
			fclose(working_file);
			return WORD_OK;
		}
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

	memset(lengths, 0, sizeof(int) * (count + 1));


	while (fgets(current_word, LONGEST_WORD, working_file))
	{
		int length;
		current_word[strlen(current_word) - 1] = '\0';
		length = strlen(current_word);

		if (length <= count)
		{
			++lengths[length];
		}

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


	while (fgets(current_word, LONGEST_WORD, working_file))
	{
		mystrupr(current_word);
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
	}

	fclose(working_file);

	return count;
}

