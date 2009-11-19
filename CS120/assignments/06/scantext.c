/*******************************************************************************
filename    scantext.c
author      Marcus Meng
DP email    marcus.meng@digipen.edu
course      CS120
section     A
assignment  6
due date    November 30, 2009

Brief Description:
  Contains several functions related to manipulating null-terminated strings.
*******************************************************************************/

/*******************************************************************************
   Function: mystrlen

Description: Finds the length of a null-terminated string.

     Inputs: string - the string to find the length of.

    Outputs: Returns an integer representing the length of the string.
*******************************************************************************/
static int mystrlen(const char *string)
{
  int length = 0;
  
  while (*string++)
    length++;

  return length;
}

/******************************************************************************
   Function: is_whitespace

Description: Determines if a character is a space, tab, or newline.

     Inputs: glyph - the character to check.

    Outputs: Returns 1 if character is a space, tab, or newline, 0 otherwise.
******************************************************************************/
static int is_whitespace(const char glyph)
{
  if (glyph == ' ' || glyph == '\t' || glyph == '\n')
    return 1;
  return 0;
}

/******************************************************************************
   Function: trim_leading

Description: Takes out the leading whitespace in a string.

     Inputs: string - the string to process.

    Outputs: Returns a pointer to the first nonwhitespace character in a string.
******************************************************************************/
static const char * trim_leading(const char *string)
{
  while ((*string) && is_whitespace(*string))
  {
    string++;
  }

  return string;
}

/******************************************************************************
   Function: get_next_token

Description: Finds the start of the next token in a given string.

     Inputs: string - the string to examine.

    Outputs: A pointer to the start of the next token, NULL if there is none.
******************************************************************************/
static const char * get_next_token(const char *string)
{
  /* Get to the end of the current token. */
  while ((*string) && (!is_whitespace(*string)))
  {
    string++;
  }

  /* Find the start of the next token. */
  while ((*string) && is_whitespace(*string))
  {
    string++;
  }

  return string;
}

/******************************************************************************
   Function: count_words

Description: Counts the number of words in a null-terminated string.

     Inputs: string - a null-terminated string.

    Outputs: Returns an integer representing the number of words in the string.
******************************************************************************/
int count_words(const char *string)
{
  int sum = 1; /* Accumulates the number of words found so far. */

  string = trim_leading(string);

  while (*(string = get_next_token(string)))
  {
    ++sum;
  }

  return sum;
}

/******************************************************************************
   Function: count_tabs

Description: Counts the number of tab characters in a string.

     Inputs: string - a null-terminated string.

    Outputs: Returns an integer representing the number of tabs found.
******************************************************************************/
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

/******************************************************************************
   Function: calculate_lengths

Description: Finds the current and display lengths of a null-terminated string.

     Inputs: string - a null-terminated string.
             tabsize - the number of spaces each tab expands out to.

    Outputs: string_length contains the length of the unmodified string.
             display_length contains length of the string with tabs expanded.
******************************************************************************/
void calculate_lengths(const char *string, int tabsize,
                       int *string_length, int *display_length)
{
  *string_length = mystrlen(string);
  *display_length = (*string_length) + ((tabsize - 1) * count_tabs(string));
}

/******************************************************************************
   Function: substitute_char

Description: Finds and substitutes all occurances of a character in a string
             with another.

     Inputs: string - a null-terminated string
             old_char - the character to replace.
             new_char - the character to replace old_char with.

    Outputs: Returns an integer representing the number of characters replaced.
             string has all old_char in it swapped for new_char.
******************************************************************************/
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

