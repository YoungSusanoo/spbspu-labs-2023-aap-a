#ifndef INP_MATRIX_HPP
#define INP_MATRIX_HPP
#include <fstream>
#include <iomanip>
namespace arakelyan
{
  void inputMatrix(std::istream & input, int * matrix, size_t el);
  std::ostream & outputMatrix(std::ostream & output, double * matrix, size_t rows, size_t cols);
}
#endif
