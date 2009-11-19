/*******************************************************************************
  FILE HEADER TO BE ADDED BY THE STUDENT
*******************************************************************************/

/*******************************************************************************
  FUNCTION HEADER TO BE ADDED BY THE STUDENT
*******************************************************************************/
static int mystrlen(const char *string)
{
  int length = 0;
  
  while (*string++)
    length++;

  return length;
}

static int is_whitespace(const char glyph)
{
	if (glyph == ' ' || glyph == '\t' || glyph == '\n')
		return 1;
	return 0;
}

static const char * get_next_token(const char *string)
{
	/* Do nothing, just count indices until next non-whitespace. */
	while ((*string) && is_whitespace(*string))
	{
		string++;
	}
	while ((*string) && (!is_whitespace(*string)))
	{
		string++;
	}

	return string;
}

int count_words(const char *string)
{
	int sum = 0; /* Accumulates the number of words found so far. */

	while (*(string = get_next_token(string)))
	{
		++sum;
	}

	return sum;
}

int count_tabs(const char *string)
{
	int i; /* Iteration counter. */
	int length = mystrlen(string); /* Length of string. */
	int sum = 0; /* Accumulates number of tabs found so far. */

	for (i = 0; i < length; ++i)
	{
		if (string[i] == '\t')
		{
			++sum;
		}
	}

	return sum;
}

void calculate_lengths(const char *string, int tabsize, int *string_length, int *display_length)
{
	*string_length = mystrlen(string);
	*display_length = (*string_length) + ((tabsize - 1) * count_tabs(string));
}

int substitute_char(char *string, char old_char, char new_char)
{
	int i; /* Iteration counter. */
	int length = mystrlen(string); /* Length of string. */
	int substitutions = 0; /* Number of substitutions performed. */

	for (i = 0; i < length; ++i)
	{
		if (string[i] == old_char)
		{
			string[i] = new_char;
			++substitutions;
		}
	}

	return substitutions;
}

