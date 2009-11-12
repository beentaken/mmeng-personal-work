/******************************************************************************
filename    jumble.c
author      Marcus Meng
DP email    marcus.meng@digipen.edu
course      CS120
section     A
assignment  9
due date    November 18, 2009

Brief Description:
  Contains a function for determining the length of a null-terminated string,
  and a function to encode or decade a given string using a passphrase and a
  rudimentary character-value cipher.
******************************************************************************/

#include "jumble.h"

/******************************************************************************
   Function: mystrlen

Description: Finds the number of characters in a null-terminated string.

     Inputs: string - the string to find the length of.

    Outputs: The number (int) of characters in the null-terminated string.
******************************************************************************/
int mystrlen(const unsigned char *string)
{
  int i = 0; /* Index counter. */

  while (string[i] != '\0')
  {
    ++i;
  }

  return i;
}

/******************************************************************************
   Function: jumble

Description: Takes a string, and modifies it by adding a keyphrase, matched
             per-character. Runs for a number of passes specified.

     Inputs: string - the string to encode or decode
             password - the keyphrase to use.
             method - Whether to encode or decode the string.
             passes - how many passes to make over each character.

    Outputs: string has been modified according to the other arguments.
******************************************************************************/
void jumble(unsigned char *string,
            const unsigned char *password,
            enum CODE_METHOD method,
            int passes)
{
  int i; /* Loop counter. */

  /* The length of the string. */
  int string_length = mystrlen(string);
  /* The length of the password. */
  int password_length = mystrlen(password);

  /* Test for whether we're encoding or decoding outside of the loop so that
   * we don't have to run the check on every iteration.
   */
  if (ENCODE == method)
  {
    for (i = 0; i < string_length; ++i)
    {
      string[i] += passes * password[i % password_length];
    }
  }
  else
  {
    for (i = 0; i < string_length; ++i)
    {
      string[i] -= passes * password[i % password_length];
    }
  }
}

