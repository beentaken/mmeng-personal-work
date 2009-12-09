/*******************************************************************************
filename    spellcheck.c
author      Marcus Meng
DP email    marcus.meng@digipen.edu
course      CS120
section     A
assignment  7
due date    December 09, 2009

Brief Description:
  Contains functions for reading data out of simple dictionary text files.
*******************************************************************************/
#include <string.h> /* strlen, strcmp, strcpy, memset */
#include <stdio.h>  /* FILE, fopen, fgets, fclose */

/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h" 

/*****************************************************************************
   Function: mystrupr

Description: Makes all the english letters in a string uppercase.

     Inputs: string - a pointer to the string that will be operated on.

    Outputs: Returns a pointer to the parsed string.
******************************************************************************/
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

/*****************************************************************************
   Function: info

Description: Calculates the shortest, longest, and number of words in a text
             file.

     Inputs: dictionary - the filename of the dictionary to use.

    Outputs: shortest - a pointer containing length of shortest word.
             longest - a pointer to the length of the longest word.
             num_words - a pointer to the number of words.
******************************************************************************/
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

/******************************************************************************
   Function: spell_check

Description: Checks to see whether a word is in a dictionary file.

     Inputs: dictionary - the filename of the dictionary file to use.
             word - the word to check.

    Outputs: Returns WORD_OK if the word is in the dictionary, WORD_BAD
             otherwise.
******************************************************************************/
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

/******************************************************************************
   Function: word_lengths

Description: Counts how many words of varying lengths exist in a dictionary.

     Inputs: dictionary - the filename of the dictionary to use.
             count - the maximum word length to search for.

    Outputs: lengths - an array containing the number of words for each length.
******************************************************************************/
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

/******************************************************************************
   Function: words_starting_with

Description: Counts the number of words starting with a letter.

     Inputs: dictionary - the filename of the dictionary to use.
             letter - the starting letter for the words in question.

    Outputs: Returns the number of words starting with letter.
******************************************************************************/
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

