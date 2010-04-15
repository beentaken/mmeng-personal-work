/*******************************************************************************
 driver-sample.cpp
*******************************************************************************/
#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <string>   // string
#include <cstdlib>  // atoi

#include "FileStrings.h" 

void test1(void)
{
  const char *words[] = {"Four", "score", "and", "seven", "years", "ago", "our",
                         "fathers", "brought", "forth", "on", "this",
                         "continent", "a", "new", "NATION", "fast123",
                         "123  abc", "Hello!!", "", "*&^%$#8UPPERlower"
                        };

  int num_words = sizeof(words) / sizeof(*words);

  CS170::SpellChecker sc("");
  std::cout << "\nTest1--------------------------------------------------------\n";
  for (int i = 0; i < num_words; i++)
  {
    std::string uword = words[i];
    CS170::StringUtils::UpperCase(uword);
    std::cout << "Word: " << words[i] << " (" << uword << ")" << std::endl;
  }
}

void test2(const std::string& dictionary)
{
  CS170::SpellChecker::SCResult file_result; /* For file errors                      */
  CS170::DictionaryInfo info;

  std::cout << "\nTest2--------------------------------------------------------\n";
  CS170::SpellChecker sc(dictionary);
  file_result = sc.GetInfo(info);

  if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
  {
    std::cout << "Can't open " << dictionary << std::endl;
    return;
  }

  std::cout << "Dictionary: " << dictionary << std::endl;
  std::cout << "Number of words: " << info.count << std::endl;
  std::cout << "Shortest word: " << info.shortest << " letters" << std::endl;
  std::cout << "Longest word: " << info.longest << " letters" << std::endl;
}

void test3(const std::string& dictionary, char letter)
{
  std::cout << "\nTest3--------------------------------------------------------\n";
  CS170::SpellChecker sc(dictionary);

  int count = 0;
  CS170::SpellChecker::SCResult file_result = sc.WordsStartingWith(letter, count);
  if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
  {
    std::cout << "Can't open " << dictionary << std::endl;
    return;
  }

  std::cout << "Dictionary: " << dictionary << std::endl;
  std::cout << "Number of words starting with " << letter << ": "; 
  std::cout << count << std::endl;
}

void test4(const std::string& dictionary, const char *word)
{
  std::cout << "\nTest4--------------------------------------------------------\n";
  CS170::SpellChecker sc(dictionary);

  CS170::SpellChecker::SCResult file_result = sc.SpellCheck(word);
  if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
  {
    std::cout << "Can't open " << dictionary << std::endl;
    return;
  }

  if (file_result == CS170::SpellChecker::scrWORD_OK)
    std::cout << "The word " << word << " is spelled correctly.\n";
  else
    std::cout << "The word " << word << " is misspelled.\n";
}

void test5(void)
{
  const char *words[] = {"Four", "score", "and", "seven", "years", "ago", "our",
                   "fathers", "brought", "forth", "on", "this", "continent",
                   "a", "new", "nation"
                  };

  int num_misspelled = 0;
  int num_words = sizeof(words) / sizeof(*words);

    /* Name of the dictionary file */
  const std::string& dictionary = "allwords.txt";

  std::cout << "\nTest5--------------------------------------------------------\n";
  CS170::SpellChecker sc(dictionary);
  std::cout << "Misspelled words: ";
  for (int i = 0; i < num_words; i++)
  {
    CS170::SpellChecker::SCResult file_result = sc.SpellCheck(words[i]);
    if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
    {
      std::cout << "Can't open " << dictionary << std::endl;
      return;
    }

    if (file_result == CS170::SpellChecker::scrWORD_BAD)
    {
      std::cout << words[i];
      num_misspelled++;
    }
  }
  if (!num_misspelled)
    std::cout << "*** None ***";
  std::cout << std::endl;
}

void test6(void)
{
  const char *words[] = {"Four", "SCORE", "and", "sevn", "years", "ago", "ar",
                   "fawthers", "brought", "foarth", "on", "this", "contnent",
                   "a", "gnu", "nashun"
                  };

  int num_misspelled = 0;
  int num_words = sizeof(words) / sizeof(*words);

    /* Name of the dictionary file */
  const std::string& dictionary = "allwords.txt";

  std::cout << "\nTest6--------------------------------------------------------\n";
  CS170::SpellChecker sc(dictionary);
  std::cout << "Misspelled words: ";
  for (int i = 0; i < num_words; i++)
  {
    CS170::SpellChecker::SCResult file_result = sc.SpellCheck(words[i]);
    if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
    {
      std::cout << "Can't open " << dictionary << std::endl;
      return;
    }

    if (file_result == CS170::SpellChecker::scrWORD_BAD)
    {
      std::cout << words[i] << " ";
      num_misspelled++;
    }
  }
  if (!num_misspelled)
    std::cout << "*** None ***";
  std::cout << std::endl;
}

void test7(int max_length)
{
  int total = 0;
  std::vector<int> lengths(max_length + 1);

    /* Name of the dictionary file */
  const std::string& dictionary = "allwords.txt";

  std::cout << "\nTest7--------------------------------------------------------\n";
  CS170::SpellChecker sc(dictionary);
  std::cout << "Dictionary: " << dictionary << std::endl;
  CS170::SpellChecker::SCResult  file_result = sc.WordLengths(lengths, max_length);
  if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
  {
    std::cout << "Can't open " << dictionary << std::endl;;
    return;
  }
  for (int i = 1; i <= max_length; i++)
  {
    std::cout << "Number of words of length " << std::setw(2) << i << " is " 
              << std::setw(6) << lengths[i] << std::endl;
    total += lengths[i];
  }
  std::cout << "Total number of words counted: " << total << std::endl;
}

void test8(void)
{
  std::cout << "\nTest8--------------------------------------------------------\n";
  const char *p;
  std::string words;
  std::vector<std::string> tokens;
  
  p = "When in the Course of human events";
  words = p;
  std::cout << "String: |" << p << "|" << std::endl;
  tokens = CS170::StringUtils::Tokenize(words);
  std::cout << "There are " << tokens.size() << " tokens\n";
  for (unsigned i = 0; i < tokens.size(); i++)
    std::cout << "|" << tokens[i] << "|" << std::endl;
  std::cout << "----------------------------------\n";

  p = "  When    in the    Course of human events    ";
  words = p;
  std::cout << "String: |" << p << "|" << std::endl;
  tokens = CS170::StringUtils::Tokenize(words);
  std::cout << "There are " << tokens.size() << " tokens\n";
  for (unsigned i = 0; i < tokens.size(); i++)
    std::cout << "|" << tokens[i] << "|" << std::endl;
  std::cout << "----------------------------------\n";

  p = "WhenintheCourseofhumanevents";
  words = p;
  std::cout << "String: |" << p << "|" << std::endl;
  tokens = CS170::StringUtils::Tokenize(words);
  std::cout << "There are " << tokens.size() << " tokens\n";
  for (unsigned i = 0; i < tokens.size(); i++)
    std::cout << "|" << tokens[i] << "|" << std::endl;
  std::cout << "----------------------------------\n";

  p = "";
  words = p;
  std::cout << "String: |" << p << "|" << std::endl;
  tokens = CS170::StringUtils::Tokenize(words);
  std::cout << "There are " << tokens.size() << " tokens\n";
  for (unsigned i = 0; i < tokens.size(); i++)
    std::cout << "|" << tokens[i] << "|" << std::endl;
  std::cout << "----------------------------------\n";
}

void test9(void)
{
  std::cout << "\nTest9--------------------------------------------------------\n";
  const char *p = "When in the Course of human events, it becomes necessary " 
                  "for one people to dissolve the political bands which have "
                  "connected them with another, and to assume among the powers "
                  "of the earth, the separate and equal station to which the " 
                  "Laws of Nature and of Nature's God entitle them, a decent "
                  "respect to the opinions of mankind requires that they "
                  "should declare the causes which impel them to the separation.";

  std::string words(p);
  std::vector<std::string> tokens = CS170::StringUtils::Tokenize(words);
  std::cout << "There are " << tokens.size() << " tokens\n";
  for (unsigned i = 0; i < tokens.size(); i++)
    std::cout << "|" << tokens[i] << "|" << std::endl;
}

void test10(int width)
{
  std::cout << "\nTest10--------------------------------------------------------\n";
  const char *p = "When in the Course of human events, it becomes necessary " 
                  "for one people to dissolve the political bands which have "
                  "connected them with another, and to assume among the powers "
                  "of the earth, the separate and equal station to which the " 
                  "Laws of Nature and of Nature's God entitle them, a decent "
                  "respect to the opinions of mankind requires that they "
                  "should declare the causes which impel them to the separation.";

  std::string words(p);
  std::vector<std::string> lines = CS170::StringUtils::WordWrap(words, width);
  std::cout << "There are " << lines.size() << " lines wrapped at " << width << " characters:\n";
  size_t shortest = 100000, longest = 0;
  for (unsigned i = 0; i < lines.size(); i++)
  {
    size_t size = lines[i].size();
    std::cout << "Line #" << std::setw(3) << (i + 1) << " [";
    std::cout << std::setw(2) << size << "] ";
    std::cout << "|" << lines[i] << "|" << std::endl;
    if (size < shortest)
      shortest = size;
    if (size > longest)
      longest = size;
  }
  std::cout << "Shortest line: " << shortest << std::endl;
  std::cout << " Longest line: " << longest << std::endl;
  std::cout << std::endl;
}

void SomeWidths(int width)
{
  std::cout << "\nSomeWidths--------------------------------------------------------\n";
  const char *p = "When in the Course of human events, it becomes necessary for";

  std::string words(p);
  std::vector<std::string> lines = CS170::StringUtils::WordWrap(words, width);
  std::cout << "There are " << lines.size() << " lines wrapped at " << width << " characters:\n";
  size_t shortest = 100000, longest = 0;
  for (unsigned i = 0; i < lines.size(); i++)
  {
    size_t size = lines[i].size();
    std::cout << "Line #" << std::setw(3) << (i + 1) << " [";
    std::cout << std::setw(2) << size << "] ";
    std::cout << "|" << lines[i] << "|" << std::endl;
    if (size < shortest)
      shortest = size;
    if (size > longest)
      longest = size;
  }
  std::cout << "Shortest line: " << shortest << std::endl;
  std::cout << " Longest line: " << longest << std::endl;
  std::cout << std::endl;
}

void test11(void)
{
  SomeWidths(1);
  SomeWidths(4);
  SomeWidths(8);
  SomeWidths(12);
  SomeWidths(19);
  SomeWidths(25);
  SomeWidths(35);
  SomeWidths(70);
  SomeWidths(59);
  SomeWidths(60);
  SomeWidths(61);
}

void AllWidths(int width)
{
  std::cout << "\nAllWidths--------------------------------------------------------\n";
  const char *p = "When in the Course of human events, it becomes necessary " 
                  "for one people to dissolve the political bands which have "
                  "connected them with another, and to assume among the powers "
                  "of the earth, the separate and equal station to which the " 
                  "Laws of Nature and of Nature's God entitle them, a decent "
                  "respect to the opinions of mankind requires that they "
                  "should declare the causes which impel them to the separation.";

  std::string words(p);
  std::vector<std::string> lines = CS170::StringUtils::WordWrap(words, width);
  std::cout << "There are " << lines.size() << " lines wrapped at " << width << " characters:\n";
  size_t shortest = 100000, longest = 0;

  for (unsigned i = 0; i < lines.size(); i++)
  {
    size_t size = lines[i].size();
    std::cout << "Line #" << std::setw(3) << (i + 1) << " [";
    std::cout << std::setw(2) << size << "] ";
    std::cout << "|" << lines[i] << "|" << std::endl;
    if (size < shortest)
      shortest = size;
    if (size > longest)
      longest = size;
  }
  std::cout << "Shortest line: " << shortest << std::endl;
  std::cout << " Longest line: " << longest << std::endl;
  std::cout << std::endl;
}

void test12(void)
{
  for (int i = 1; i <= 100; i++)
    AllWidths(i);
}

void TestAcronyms(const std::vector<std::string> acronyms, 
                  const std::string& dictionary, size_t maxlen, 
                  bool showstrings)
{
  CS170::SpellChecker::SCResult file_result; /* For file errors                      */

  CS170::SpellChecker sc(dictionary);

  for (size_t i = 0; i < acronyms.size(); i++)
  {
    std::vector<std::string> words;
    file_result = sc.AcronymToWord(acronyms[i], words, maxlen);

    if (file_result == CS170::SpellChecker::scrFILE_ERR_OPEN)
    {
      std::cout << "Can't open " << dictionary << std::endl;
      continue;
    }

    std::cout << "Acronym: " << acronyms[i] << ", Words (" << words.size() << "): ";
    if (showstrings)
    {
      std::vector<std::string>::iterator it;
      for (it = words.begin(); it != words.end(); ++it)
        std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

}

void test13(void)
{
  std::cout << "\nTest13--------------------------------------------------------\n";
  
  std::vector<std::string> acronyms;
  acronyms.push_back("GV");
  acronyms.push_back("PAP");
  acronyms.push_back("ABC");
  TestAcronyms(acronyms, "lexicon2.txt", 0, true);
}

void test14()
{
  std::cout << "\nTest14--------------------------------------------------------\n";

  std::vector<std::string> acronyms;
  acronyms.push_back("bbq");
  acronyms.push_back("byob");
  acronyms.push_back("ATHF");
  acronyms.push_back("icbm");
  acronyms.push_back("TCBY");
  acronyms.push_back("bsgd");
  acronyms.push_back("imHO");
  TestAcronyms(acronyms, "allwords.txt", 0, true);
}

void test15()
{
  std::cout << "\nTest15--------------------------------------------------------\n";

  std::vector<std::string> acronyms;
  acronyms.push_back("ROYG");
  acronyms.push_back("rofl");
  acronyms.push_back("otoh");
  acronyms.push_back("asap");
  TestAcronyms(acronyms, "allwords.txt", 10, true);
}

void test16(bool showstrings = true)
{
  std::cout << "\nTest16--------------------------------------------------------\n";

  std::vector<std::string> acronyms;
  acronyms.push_back("PHAT");
  acronyms.push_back("OTOH");
  acronyms.push_back("fdr");
  acronyms.push_back("isbn");
  TestAcronyms(acronyms, "allwords.txt", 0, showstrings);
}

void test17(int width)
{
  std::cout << "\nTest17--------------------------------------------------------\n";
  const char *p = "When   in the    Course of  human events, it   becomes necessary " 
                  "for one    people to dissolve the   political bands   which have "
                  "    connected   them with     another, and to    assume    among the powers "
                  "of the earth, the separate and equal station to which the " 
                  "  Laws of Nature       and         of Nature's God entitle them,     a decent "
                  "respect to the   opinions of       mankind requires   that they   "
                  "should    declare     the  causes  which impel them   to the separation.";

  std::string words(p);
  std::vector<std::string> lines = CS170::StringUtils::WordWrap(words, width);
  std::cout << "There are " << lines.size() << " lines wrapped at " << width << " characters:\n";
  size_t shortest = 100000, longest = 0;
  for (unsigned i = 0; i < lines.size(); i++)
  {
    size_t size = lines[i].size();
    std::cout << "Line #" << std::setw(3) << (i + 1) << " [";
    std::cout << std::setw(2) << size << "] ";
    std::cout << "|" << lines[i] << "|" << std::endl;
    if (size < shortest)
      shortest = size;
    if (size > longest)
      longest = size;
  }
  std::cout << "Shortest line: " << shortest << std::endl;
  std::cout << " Longest line: " << longest << std::endl;
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  int test = 0;
  if (argc > 1)
    test = std::atoi(argv[1]);

  if (test == 1)
  {
    test1(); // Uppercase
  }
  else if (test == 2)
  {
    test2("lexicon.txt");  // GetInfo
    test2("small.txt");    // GetInfo
    test2("allwords.txt"); // GetInfo
  }
  else if (test == 3)
  {
    test3("lexicon.txt", 'a'); // WordsStartingWith
    test3("lexicon.txt", 'A'); // WordsStartingWith
    test3("lexicon.txt", 'l'); // WordsStartingWith
    test3("lexicon.txt", '$'); // WordsStartingWith
    test3("lexicon.txt", 'e'); // WordsStartingWith
    test3("allwords.txt", 'M'); // WordsStartingWith
    test3("allwords.txt", 'q'); // WordsStartingWith
    test3("allwords.txt", '5'); // WordsStartingWith
  }
  else if (test == 4)
  {
    test4("lexicon.txt", "APPLE");            // Spellcheck, correct
    test4("lexicon.txt", "Apple");            // Spellcheck, correct
    test4("lexicon.txt", "apple");            // Spellcheck, correct
    test4("lexicon.txt", "appl");             // Spellcheck, incorrect
    test4("small.txt", "abalone");            // Spellcheck, correct
    test4("allwords.txt", "interdigitation"); // Spellcheck, correct
    test4("allwords.txt", "interdigalizing"); // Spellcheck, incorrect
  }
  else if (test == 5)
  {
    test5(); // Spellcheck, all correct
  }
  else if (test == 6)
  {
    test6(); // Spellcheck, some misspelled
  }
  else if (test == 7)
  {
    test7(5);  // WordLengths, 1 - 5
    test7(20); // WordLengths, 1 - 20
  }
  else if (test == 8)
  {
    test8(); // Simple Tokenize
  }
  else if (test == 9)
  {
    test9(); // Larger Tokenize
  }
  else if (test == 10)
  {
    test10(20); // Wordwrap
  }
  else if (test == 11)
  {
    test11();   // Several Wordwrap test
  }
  else if (test == 12)
  {
    test12();   // Tons 'O Wordwrap tests
  }
  else if (test == 13)
  {
    test13();   // Acronym test, small dictionary
  }
  else if (test == 14)
  {
    test14();   // Acronym test, big dictionary
  }
  else if (test == 15)
  {
    test15();   // Acronym test, big, maxlen = 10
  }
  else if (test == 16)
  {
    test16();   // Acronym test, big, lots of output
  }
  else if (test == 17)
  {
    test17(20); // Wordwrap!!!
  }
  else
  {
    test1(); // Uppercase
    test2("lexicon.txt");  // GetInfo
    test2("small.txt");    // GetInfo
    test2("allwords.txt"); // GetInfo
    test3("lexicon.txt", 'a'); // WordsStartingWith
    test3("lexicon.txt", 'A'); // WordsStartingWith
    test3("lexicon.txt", 'l'); // WordsStartingWith
    test3("lexicon.txt", '$'); // WordsStartingWith
    test3("lexicon.txt", 'e'); // WordsStartingWith
    test3("allwords.txt", 'M'); // WordsStartingWith
    test3("allwords.txt", 'q'); // WordsStartingWith
    test3("allwords.txt", '5'); // WordsStartingWith
    test4("lexicon.txt", "APPLE");            // Spellcheck, correct
    test4("lexicon.txt", "Apple");            // Spellcheck, correct
    test4("lexicon.txt", "apple");            // Spellcheck, correct
    test4("lexicon.txt", "appl");             // Spellcheck, incorrect
    test4("small.txt", "abalone");            // Spellcheck, correct
    test4("allwords.txt", "interdigitation"); // Spellcheck, correct
    test4("allwords.txt", "interdigalizing"); // Spellcheck, incorrect
    test5(); // Spellcheck, all correct
    test6(); // Spellcheck, some misspelled
    test7(5);  // WordLengths, 1 - 5
    test7(20); // WordLengths, 1 - 20
    test8(); // Simple Tokenize
    test9(); // Larger Tokenize
    test10(20);  // Wordwrap
    test11();    // Several Wordwrap test
    test12();    // Tons 'O Wordwrap tests
    test13(); // Acronyms, simple, small lexicon
    test14(); // Acronyms, big lexicon, all sizes
    test15(); // Acronyms, big lexicon, maxlen=10
    test16(); // Acronyms, big lexicon, lots of output
    test17(20); // Wordwrap!!!
  }

  return 0;
}
