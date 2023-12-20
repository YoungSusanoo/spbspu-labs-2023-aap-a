#include "Polygon.hpp"

#include <stdexcept>
#include <algorithm>

zhalilov::Polygon::Polygon(point_t *points, const size_t size)
{
  if (size < 3)
  {
    throw std::invalid_argument("not enough points to describe polygon");
  }
  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = i + 1; j < size; j++)
    {
      if ((points[i].x == points[j].x)
        && (points[i].y == points[j].y))
      {
        throw std::invalid_argument("some points are equal");
      }
    }
  }
  point_t maxY = points[0], minY = points[0];
  point_t maxX = points[0], minX = points[0];
  for (size_t i = 1; i < size; i++)
  {
    if (points[i].x > maxX.x)
    {
      maxX = points[i];
    }
    if (points[i].x < minX.x)
    {
      minX = points[i];
    }
    if (points[i].y > maxY.y)
    {
      maxY = points[i];
    }
    if (points[i].y < minY.y)
    {
      minY = points[i];
    }
  }
  m_frameRect.width = maxX.x - minX.x;
  m_frameRect.height = maxY.y - minY.y;
  double width = m_frameRect.width;
  double height = m_frameRect.height;
  m_frameRect.pos = {minX.x + width / 2.0, minY.y + height / 2.0};

  double deltaX = 0.0;
  double deltaY = 0.0;
  for (size_t i = 0; i < size; i++)
  {
    deltaX += points[i].x;
    deltaY += points[i].y;
  }
  deltaX = deltaX / size;
  deltaY = deltaY / size;
  m_pos = {deltaX, deltaY};

  points = sortByX(points, size);
  point_t tempPoint = minX;
  size_t iterator = 1;
  m_square = 0.0;
  while (tempPoint.x != maxY.x)
  {
    if (points[iterator].y >= tempPoint.y)
    {
      m_square += (points[iterator].x - tempPoint.x) * (points[iterator].y + tempPoint.y) / 2.0;
      tempPoint = points[iterator];
    }
    iterator++;
  }

  while (tempPoint.x != maxX.x)
  {
    if (points[iterator].y >= maxX.y)
    {
      m_square += (points[iterator].x - tempPoint.x) * (tempPoint.y + points[iterator].y) / 2.0;
      tempPoint = points[iterator];
    }
    iterator++;
  }
  iterator = size - 1;
  while (tempPoint.x != minY.x)
  {
    if (points[iterator].y <= tempPoint.y)
    {
      m_square -= (tempPoint.x - points[iterator].x) * (points[iterator].y + tempPoint.y) / 2.0;
      tempPoint = points[iterator];
    }
    iterator--;
  }
  while (tempPoint.x != minX.x)
  {
    if (points[iterator].y >= tempPoint.y)
    {
      m_square -= (tempPoint.x - points[iterator].x) * (points[iterator].y + tempPoint.y) / 2.0;
      tempPoint = points[iterator];
    }
  }
  delete[] points;
}

zhalilov::Polygon::~Polygon()
{
}

zhalilov::point_t *zhalilov::Polygon::sortByX(point_t *points, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = 0; j < size; j++)
    {
      if (points[i].x > points[i + 1].x)
      {
        std::swap(points[i], points[i + 1]);
      }
    }
  }
  return points;
}

double zhalilov::Polygon::getArea() const
{
  return m_square;
}

zhalilov::rectangle_t zhalilov::Polygon::getFrameRect() const
{
  return m_frameRect;
}

void zhalilov::Polygon::move(const point_t &point)
{
  m_pos = point;
}

void zhalilov::Polygon::move(const double dx, const double dy)
{
  m_pos.x += dx;
  m_pos.y += dy;
}

void zhalilov::Polygon::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("ratio should be greater than zero");
  }
  point_t basePos = m_frameRect.pos;
  move(m_pos);
  m_frameRect.width *= ratio;
  m_frameRect.height *= ratio;
  double dx = (m_pos.x - basePos.x) * ratio;
  double dy = (m_pos.x - basePos.x) * ratio;
  move(-dx, -dy);
  m_square *= (ratio * ratio);
}
