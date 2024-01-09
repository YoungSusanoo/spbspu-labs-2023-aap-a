#include <istream>
#include <iostream>
#include "createline.hpp"
#include "inputline.hpp"

int main()
{
  using namespace piyavkin;
  size_t length = 0;
  char * new_line = nullptr;
  char * new_alphabet = nullptr;
  std::cin >> std::noskipws;
  try
  {
    new_line = inputLine(std::cin, length);
    new_alphabet = createLine(new_line);
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << e.what() << '\n';
    delete [] new_line;
    delete [] new_alphabet;
    return 1;
  }
  if (new_line == nullptr)
  {
    std::cerr << "Line not read\n";
    delete [] new_alphabet;
    delete [] new_line;
    return 1;
  }
  std::cin >> std::skipws;
  size_t i = 0;
  while (new_alphabet[i] != '\0')
  {
    std::cout << new_alphabet[i++];
  }
  std::cout << '\n';
  delete [] new_line;
  delete [] new_alphabet;
}
