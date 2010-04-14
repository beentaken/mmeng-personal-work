////////////////////////////////////////////////////////////////////////////////
#ifndef FILESTRINGS_H
#define FILESTRINGS_H
////////////////////////////////////////////////////////////////////////////////

#include <string> // string
#include <vector> // vector

namespace CS170
{

const char SPACE = 32;

class StringUtils
{
  public:
    static std::string& UpperCase(std::string& string);
    static std::vector<std::string> WordWrap(const std::string& words, 
                                             size_t line_length);
    static std::vector<std::string> Tokenize(const std::string& words);
};

class DictionaryInfo
{
  public:
    size_t shortest; // Shortest word in the dictionary
    size_t longest;  // Longest word in the dictionary
    size_t count;    // Number of words in the dictionary
};

class SpellChecker
{
  public:
    enum SCResult { scrFILE_OK = -1,       // File was opened successfully 
                    scrFILE_ERR_OPEN = -2, // File was unable to be opened 
                    scrWORD_OK = 1,        // Word found in dictionary      
                    scrWORD_BAD = 2        // Word not found in dictionary  
                  };

    SpellChecker(const std::string &dictionary);
    SCResult GetInfo(DictionaryInfo &info) const;
    SCResult SpellCheck(const std::string& word) const;
    SCResult WordLengths(std::vector<int>& lengths, size_t count) const;
    SCResult WordsStartingWith(char letter, int& count) const;
    SCResult AcronymToWord(const std::string& acronym, 
                           std::vector<std::string>& words, 
                           size_t maxlen = 0) const;
      
  private:
    std::string dictionary_;
};

} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
