#include "countDiffSymbs.hpp"

#include <cctype>
#include <cstddef>
#include <iostream>

unsigned int zhalilov::countDiffSymbs(const char *string)
{
  bool doesLetterOccur[26] = {};
  while (*string)
  {
    if (isalpha(*string))
    {
      int symIndex = tolower(*string) - 97;
      doesLetterOccur[symIndex] = true;
    }
    string++;
  }

  unsigned char diffSymbs = 0;
  for (size_t i = 0; i < 26; i++)
  {
    if (doesLetterOccur[i])
    {
      diffSymbs++;
    }
  }
  return diffSymbs;
}
