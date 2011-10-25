/******************************************************************************
filename    palindrome1.c and palindrome2.c
author      Marcus Meng
DP email    marcus.meng@digipen.edu
course      CS120
section     A
assignment  4
due date    November 11, 2009

Brief Description:
  Contains a function for determining whether or not a particular array of
  characters provided is a palindrome.
******************************************************************************/

/******************************************************************************
   Function: is_palindrome1

Description: Determines whether phrase is a palindrome using array brackets.

     Inputs: phrase - the array to test.
             length - the size of phrase.

    Outputs: 0 if phrase is not a palindrome, 1 otherwise.
******************************************************************************/
int is_palindrome1(const char phrase[], int length)
{
	int i, j; /* Iteration counters. */

	for (i = 0, j = length - 1; i < j; ++i, --j)
	{
		if (phrase[i] != phrase[j])
		{
			return 0;
		}
	}

	return 1;
}

