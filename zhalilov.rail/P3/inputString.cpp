#include "inputString.hpp"

char *zhalilov::resizeString(char string[], const size_t oldSize, const size_t newSize)
{
  char *temp = new char[newSize];
  size_t dataIndex = 0;
  while (dataIndex < oldSize && dataIndex < newSize)
  {
    temp[dataIndex] = string[dataIndex];
    dataIndex++;
  }
  delete[] string;
  for (size_t i = oldSize; i < newSize - 1; i++)
  {
    temp[i] = 0;
  }
  temp[newSize - 1] = '\0';
  return temp;
}

char *zhalilov::inputString(size_t &lastDataIndex, size_t &size, std::istream &input)
{
  size_t strSize = 100;
  size_t dataIndex = 0;
  char *string = nullptr;
  try
  {
    string = new char[strSize]{};
  }
  catch (const std::bad_alloc &e)
  {
    lastDataIndex = 0;
    size = 0;
    return new char[0];
  }
  input >> std::noskipws;
  char temp = 0;
  while (input >> temp)
  {
    if (temp == '\n')
    {
      string[dataIndex] = '\0';
      break;
    }
    else
    {
      string[dataIndex] = temp;
    }
    if (dataIndex + 1 == strSize)
    {
      try
      {
        string = resizeString(string, strSize, strSize + 40);
        strSize += 40;
      }
      catch (const std::bad_alloc &e)
      {
        break;
      }
    }
    dataIndex++;
  }
  input >> std::skipws;
  lastDataIndex = dataIndex;
  size = strSize;
  return string;
}
