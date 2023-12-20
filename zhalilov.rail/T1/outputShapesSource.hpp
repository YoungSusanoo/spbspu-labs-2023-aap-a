#ifndef OUTPUTSHAPESSOURCE_HPP
#define OUTPUTSHAPESSOURCE_HPP

#include <ostream>
#include <cstddef>

#include "Shape.hpp"

namespace zhalilov
{
  std::ostream &outputShapesSource(Shape **shapes, size_t size, std::ostream &output);
}

#endif
