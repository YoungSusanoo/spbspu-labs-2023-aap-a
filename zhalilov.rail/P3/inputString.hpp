#ifndef INPUTSTRING_HPP
#define INPUTSTRING_HPP

#include <iostream>

namespace zhalilov
{
  char *inputString(size_t &lastDataIndex, size_t &size, std::istream &in);
  char *resizeString(char string[], size_t oldSize, size_t newSize);
}

#endif
