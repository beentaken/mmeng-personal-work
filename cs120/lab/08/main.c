#include <stdio.h>

/* Prototypes */
int strtoint(const char string[]);
void inttostr(int number, char string[]);
void reverse_words1(const char input[], char output[]);
void reverse_words2(char input[]);

void test1(void)
{
  printf("%i\n", strtoint("0"));
  printf("%i\n", strtoint("1"));
  printf("%i\n", strtoint("12"));
  printf("%i\n", strtoint("123"));
  printf("%i\n", strtoint("1234"));
  printf("%i\n", strtoint("1234567890"));
  printf("%i\n", strtoint("-0"));
  printf("%i\n", strtoint("-12"));
  printf("%i\n", strtoint("-123"));
  printf("%i\n", strtoint("-124"));
  printf("%i\n", strtoint("-1234567890"));
}

void test2(void)
{
  char buffer[12];
  
  inttostr(1, buffer);
  printf("|%s|\n", buffer);

#if 1
  inttostr(12, buffer);
  printf("|%s|\n", buffer);

  inttostr(123, buffer);
  printf("|%s|\n", buffer);

  inttostr(1234, buffer);
  printf("|%s|\n", buffer);

  inttostr(1234567890, buffer);
  printf("|%s|\n", buffer);

  inttostr(0, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1, buffer);
  printf("|%s|\n", buffer);

  inttostr(-12, buffer);
  printf("|%s|\n", buffer);

  inttostr(-123, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1234, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1234567890, buffer);
  printf("|%s|\n", buffer);
#endif
}

void test3(void)
{
  {
  char words1[] = "This";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "This is";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

#if 1
  {
  char words1[] = "This is a";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "This is a string";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "forth brought fathers our ago years seven and score Four";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  /* Bonus */
  {
  char words1[] = "   This  is another   string ";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }
#endif
}

void test4(void)
{
  {
  char words[] = "This";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  {
  char words[] = "This is";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

#if 1
  {
  char words[] = "This is a";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  {
  char words[] = "This is a string";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  {
  char words[] = "forth brought fathers our ago years seven and score Four";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  /* Bonus */
  {
  char words[] = "   This  is another   string ";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }
#endif
}

int main(void)
{
  printf("\n============== Test 1 ================\n");
  test1();  

#if 1
  printf("\n============== Test 2 ================\n");
  test2();  

  printf("\n============== Test 3 ================\n");
  test3();  

  printf("\n============== Test 4 ================\n");
  test4();  
#endif

  return 0;
}
