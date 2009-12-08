#define FILE_OK       -1 /* If the file was opened successfully         */
#define FILE_ERR_OPEN -2 /* If the file was unable to be opened         */
#define WORD_OK        1 /* If the word was found in the dictionary     */
#define WORD_BAD       2 /* If the word was not found in the dictionary */

#define LONGEST_WORD 50  /* This is the longest word you need to handle */

char *mystrupr(char *string);
int info(const char *dictionary, int *shortest, int *longest, int *num_words);
int spell_check(const char *dictionary, const char *word);
int word_lengths(const char *dictionary, int lengths[], int count);
int words_starting_with(const char *dictionary, char letter);
