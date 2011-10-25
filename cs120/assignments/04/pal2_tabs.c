/******************************************************************************
   Function: is_palindrome2

Description: Determines whether an array is a palindrome using dereference
             operators.

     Inputs: phrase - the array to test.
             length - the size of phrase.

    Outputs: 0 if phrase is not a palindrome, 1 otherwise.
******************************************************************************/
int is_palindrome2(const char phrase[], int length)
{
	int i, j; /* Iteration counters. */

	for (i = 0, j = length - 1; i < j; ++i, --j)
	{
		if (*(phrase + i) != *(phrase + j))
		{
			return 0;
		}
	}

	return 1;
}

