#include "inputShapesSource.hpp"

#include <cstring>
#include <string>
#include <cctype>

#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Polygon.hpp"
#include "inputString.hpp"

zhalilov::Shape *zhalilov::inputRectangle(const char string[])
{
  double coords[4] = {};
  size_t delta = 0;
  size_t nameLen = 9;
  const char *newStr = string + nameLen;
  for (size_t i = 0; i < 4; i++)
  {
    coords[i] = std::stod(newStr, &delta);
    newStr += delta;
  }
  if (*newStr != '\0')
  {
    throw std::invalid_argument("Too many args in rect source");
  }
  point_t leftCorner = {coords[0], coords[1]};
  point_t rightCorner = {coords[2], coords[3]};
  return new Rectangle(leftCorner, rightCorner);
}

zhalilov::Shape *zhalilov::inputCircle(const char string[])
{
  double nums[3] = {};
  size_t delta = 0;
  size_t nameLen = 6;
  const char *newStr = string + nameLen;
  for (size_t i = 0; i < 3; i++)
  {
    nums[i] = std::stod(newStr, &delta);
    newStr += delta;
  }
  if (*newStr != '\0')
  {
    throw std::invalid_argument("Too many args in circle source");
  }
  return new Circle({nums[0], nums[1]}, nums[2]);
}

zhalilov::Shape *zhalilov::inputPolygon(const char string[])
{
  size_t size = 10;
  size_t length = 0;
  double *coords = new double[10];
  size_t nameLen = 7;
  const char *newStr = string + nameLen;
  size_t i = 0;
  size_t delta = 0;
  while (*newStr != '\0')
  {
    coords[i] = std::stod(newStr, &delta);
    newStr += delta;
    if (i + 1 == size)
    {
      double *newCoords = nullptr;
      try
      {
        newCoords = new double[size + 4]{};
        for (size_t j = 0; j < size; j++)
        {
          newCoords[j] = coords[j];
        }
        delete[] coords;
        coords = newCoords;
        size += 4;
      }
      catch (const std::bad_alloc &e)
      {
        delete[] coords;
        throw;
      }
    }
    i++;
  }
  length = i;
  if (length % 2 != 0)
  {
    throw std::invalid_argument("Incorrect numf of args for polygon");
  }
  point_t *points = new point_t[length / 2];
  for (size_t j = 0; j < length; j += 2)
  {
    points[j / 2] = {coords[j], coords[j + 1]};
  }
  return new Polygon(points, length / 2);
}

shapeInputFunc zhalilov::identifyShape(const char string[])
{
  const char *names[] = {"RECTANGLE", "CIRCLE", "POLYGON"};
  shapeInputFunc functions[3];
  functions[0] = inputRectangle;
  functions[1] = inputCircle;
  functions[2] = inputPolygon;
  size_t namesSize = 3;
  for (size_t i = 0; i < namesSize; i++)
  {
    size_t nameLen = strlen(names[i]);
    if ((strncmp(names[i], string, nameLen) == 0)
      && (isspace(string[nameLen])))
    {
      return functions[i];
    }
  }
  return nullptr;
}

bool zhalilov::inputScale(point_t &point, double &ratio, const char string[])
{
  char name[] = "SCALE";
  size_t nameLen = 5;
  if ((strncmp(name, string, nameLen) == 0)
    && (isspace(string[nameLen])))
  {
    const char *newStr = string + nameLen;
    size_t delta = 0;
    double x = std::stod(newStr, &delta);
    newStr += delta;
    double y = std::stod(newStr, &delta);
    newStr += delta;
    double inputedRatio = std::stod(newStr, &delta);

    if (*(newStr + delta) != '\0')
    {
      throw std::invalid_argument("Invalid scaling source");
    }
    if (inputedRatio <= 0.0)
    {
      throw std::invalid_argument("Scaling ration should be greater than zero");
    }

    point = {x, y};
    ratio = inputedRatio;
    return true;
  }
  return false;
}

zhalilov::Shape **zhalilov::increaseLength(Shape **shapes, size_t size, size_t delta)
{
  Shape **newShapes = new Shape*[size + delta]{nullptr};
  for (size_t i = 0; i < size; i++)
  {
    newShapes[i] = shapes[i];
  }
  delete[] shapes;
  return newShapes;
}

zhalilov::Shape **zhalilov::inputShapesSource(point_t &point, double &ratio, size_t &length, size_t &size, std::istream &input)
{
  size_t shapeIndex = 0;
  size = 10;
  Shape **shapes = new Shape*[10]{nullptr};
  char *string = nullptr;
  while (true)
  {
    string = inputString(input);
    try
    {
      if (inputScale(point, ratio, string))
      {
        delete[] string;
        length = shapeIndex;
        return shapes;
      }
    }
    catch (const std::invalid_argument &e)
    {
      delete[] string;
      for (size_t i = 0; i < size; i++)
      {
        delete shapes[i];
      }
      delete[] shapes;
      throw;
    }

    shapeInputFunc inputFunc = identifyShape(string);
    if (!inputFunc)
    {
      delete[] string;
      continue;
    }

    if (shapeIndex + 1 == size)
    {
      try
      {
        shapes = increaseLength(shapes, size, 10);
        size += 10;
      }
      catch (const std::bad_alloc &e)
      {
        delete[] string;
        for (size_t i = 0; i < size; i++)
        {
          delete shapes[i];
        }
        delete[] shapes;
        throw;
      }
    }
    try
    {
      shapes[shapeIndex] = inputFunc(string);
    }
    catch (const std::invalid_argument &e)
    {
      shapes[shapeIndex] = nullptr;
      delete[] string;
      continue;
    }
    catch (const std::bad_alloc &e)
    {
      for (size_t i = 0; i < size; i++)
      {
        delete shapes[i];
      }
      delete[] shapes;
      delete[] string;
      throw;
    }
    delete[] string;
    shapeIndex++;
  }
}
