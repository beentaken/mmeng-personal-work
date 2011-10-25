/*****************************************************************************/
/*!
\file   filename
\author Marcus Meng
\par    email: marcus.meng@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment 7
\date   April 14, 2010
\brief
	This file contains the implementations for various string utilities
	and the SpellChecker class.

Hours spent on this assignment: 4

Specific portions that gave you the most trouble:

The WordWrap function, which refuses to play nicely on line_length == 1;

*/
/*****************************************************************************/
#include <fstream>        // ifstream
#include "FileStrings.h"  // SpellChecker, StringUtils, DictionaryInfo

namespace CS170
{

/*****************************************************************************/
/*!
\brief
	Converts a given string to all caps.

\param string
	The string to convert.

\return
	A reference to the newly converted string.
*/
/*****************************************************************************/
std::string& StringUtils::UpperCase(std::string& string)
{
  std::string::iterator it;
  for (it = string.begin(); it != string.end(); ++it)
    if (*it >= 'a' && *it <= 'z')
      *it -= SPACE;

  return string;
}

/*****************************************************************************/
/*!
\brief
	Splits up a string into the appropriately wrapped lines. Does not
	break words.

\param words
	The string to break up.

\param line_length
	The length of each line.

\return
	A vector containing the nicely cut lines.
*/
/*****************************************************************************/
std::vector<std::string> StringUtils::WordWrap(const std::string &words,
		size_t line_length)
{
	// Somewhere to stick our lines into.
	std::vector<std::string> lines;
	// What seperates the words?
	const std::string delimiters(" \t");
	// Track the end of the current line with this.
	std::string::size_type found;
	// Track the start of the current line with this.
	std::string::size_type i = 0;

	while (i != std::string::npos && i < words.size())
	{
		// Start of last word before the end of the line.
		found = words.find_last_of(delimiters, i + line_length);
		
		// If the remaining length is smaller than a line,
		// stick the rest into the vector and GTFO.
		if (line_length >= (words.size() - i))
		{
			lines.push_back(words.substr(i, words.size() - i));
			break;
		}

		// Let's hope that it can find a delimiter to use before the
		// line break.
		if (found != std::string::npos)
		{
			// Make sure it's not finding something preceding
			// our current index. (found > i) == good.
			if (found > i)
				lines.push_back(words.substr(i, found - i));
			// Oh dear. Push the rest of the word on, I guess.
			else
			{
				found = words.find_first_of(delimiters, i);
				lines.push_back(words.substr(i, found - i));
			}
		}
		// Advance to the start of the next word, to start
		// the line with.
		i = words.find_first_not_of(delimiters,found);
	} // while (i < words.size())

	return(lines);
}

/*****************************************************************************/
/*!
\brief
	Splits up and obtains all the words in a string.

\param words
	The string to tokenize.

\return
	A vector containing all the words in the string.
*/
/*****************************************************************************/
std::vector<std::string> StringUtils::Tokenize(const std::string &words)
{
	// What constitutes seperation between words?
	const std::string delimiters(" \t\n");
	// Store the words we pull out.
	std::vector<std::string> tokens;
	// End of a word?
	std::string::size_type found = 0;
	// Start of a word!
	std::string::size_type i = words.find_first_not_of(delimiters);

	while (i < words.size())
	{
		found = words.find_first_of(delimiters, i);
		if (found != std::string::npos)
		{
			tokens.push_back(words.substr(i, found - i));
		}
		else
		{
			tokens.push_back(words.substr(i, words.size() - i));
			break;
		}

		i = words.find_first_not_of(delimiters, found);
	}

	return tokens;
}

/*****************************************************************************/
/*!
\brief
	Constructor for the SpellChecker.

\param dictionary
	The filename of the dictionary to use.
*/
/*****************************************************************************/
SpellChecker::SpellChecker(const std::string &dictionary)
{
	dictionary_ = dictionary;

	std::ifstream input;

	input.open(dictionary.c_str());

	if(input)
	{
		std::string current;
		while(input >> current)
		{
			if (input.eof())
				break;

			words_.push_back(current);
		}

		// Force an init.
		DictionaryInfo temp;
		GetInfo(temp);
	}
}

/*****************************************************************************/
/*!
\brief
	Gets various info about the loaded dictionary.

\param info
	A struct to put the various dictionary information fields into.

\return
	A code denoting whether the function ran successfully.
*/
/*****************************************************************************/
SpellChecker::SCResult SpellChecker::GetInfo(DictionaryInfo &info) const
{
	info.shortest = words_.front().length();
	for (size_t i = 0; i < words_.size(); ++i)
	{
		if (words_[i].size() > info.longest)
		{
			info.longest = words_[i].length();
		}
		if (words_[i].size() < info.shortest)
		{
			info.shortest = words_[i].length();
		}
	}

	info.count = words_.size();

	return scrWORD_OK;
}

/*****************************************************************************/
/*!
\brief
	Checks the spelling of a given word against the internal dictionary.

\param word
	The word to spellcheck.

\return
	scrWORD_OK if the word is correctly spelled, scrWORD_BAD otherwise.
*/
/*****************************************************************************/
SpellChecker::SCResult SpellChecker::SpellCheck(const std::string &word) const
{
	std::vector<std::string>::const_iterator iter;
	iter = words_.begin();
	std::string to_compare(word);
	to_compare = StringUtils::UpperCase(to_compare);

	while(iter != words_.end())
	{
		std::string upper_compare(*iter);
		StringUtils::UpperCase(upper_compare);
		int result = to_compare.compare(upper_compare);

		if (result == 0)
			return scrWORD_OK;
		else if (result > 0)
			break;

		++iter;
	}

	return scrWORD_BAD;
}

/*****************************************************************************/
/*!
\brief
	Find the number of words of various lengths in the dictionary.

\param lengths
	A vector containing the number of words of each length.

\param count
	The max word length to record.

\return
	A code denoting the success of the function.
*/
/*****************************************************************************/
SpellChecker::SCResult SpellChecker::WordLengths(std::vector<int>& lengths, size_t count) const
{
	std::vector<std::string>::const_iterator iter;
	iter = words_.begin();

	lengths.assign(count, 0);

	while (iter != words_.end())
	{
		if ((*iter).size() <= count)
		{
			++lengths[(*iter).size()];
		}
		++iter;
	}

	return scrFILE_OK;
}

/*****************************************************************************/
/*!
\brief
	Finds the number of words starting with a certain letter.

\param letter
	The letter to check for.

\return
	A code denoting the success of the function's run.
*/
/*****************************************************************************/
SpellChecker::SCResult SpellChecker::WordsStartingWith(char letter, int& count) const
{
	std::vector<std::string>::const_iterator iter = words_.begin();
	count = 0;
	
	// Convert to uppercase.
	if (letter >= 'a' && letter <= 'z')
		letter -= SPACE;

	while (iter != words_.end())
	{
		if ((*iter)[0] == letter)
			count++;
		++iter;
	}

	return scrWORD_OK;
}

/*****************************************************************************/
/*!
\brief
	Finds out what words might fit a given acronym.

\param acronym
	A string containing the acronym to try to expand.

\param words
	A vector containing the expanded words.

\param maxlen
	The maximum length of the words to expand to.

\return
	A code denoting the success of the function's execution.
*/
/*****************************************************************************/
SpellChecker::SCResult SpellChecker::AcronymToWord(const std::string &acronym,
		std::vector<std::string> &words,
		size_t maxlen) const
{
	std::vector<std::string>::const_iterator iter = words_.begin();
	std::string to_compare(acronym);

	StringUtils::UpperCase(to_compare);

	while (iter != words_.end())
	{
		if ((*iter).size() > maxlen)
		{
			++iter;
			continue;
		}

		std::string upper_compare(*iter);
		StringUtils::UpperCase(upper_compare);
		// The individual letters of our acronym.
		std::string::const_iterator match = to_compare.begin();
		// The letters of the word we're comparing it to.
		std::string::const_iterator letter = upper_compare.begin();
		if ((*letter) == (*match))
		{
			++letter;
			++match;
			while (letter != upper_compare.end())
			{
				if ((*letter) == (*match))
				{
					++match;
					if (match == to_compare.end())
						break;
				}
				++letter;
			}
		}

		if (match == to_compare.end())
		{
			words.push_back(*iter);
		}

		++iter;
	}

	return scrFILE_OK;
}

} // namespace CS170

