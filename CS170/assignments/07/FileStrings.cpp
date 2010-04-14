/*
* A PROPER FILE HEADER COMMENT MUST BE CREATED BY THE STUDENT
*/
#include <fstream>        // ifstream
#include "FileStrings.h"  // SpellChecker, StringUtils, DictionaryInfo

namespace CS170
{

/*
* A PROPER FUNCTION COMMENT MUST BE CREATED BY THE STUDENT
*/
std::string& StringUtils::UpperCase(std::string& string)
{
  std::string::iterator it;
  for (it = string.begin(); it != string.end(); ++it)
    if (*it >= 'a' && *it <= 'z')
      *it -= SPACE;

  return string;
}


}
