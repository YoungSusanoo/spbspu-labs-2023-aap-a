#include "Rectangle.hpp"

#include <stdexcept>

zhalilov::Rectangle::Rectangle(const point_t &leftCorner, const point_t &rightCorner)
{
  if ((leftCorner.x >= rightCorner.x)
    || (leftCorner.y >= rightCorner.y))
  {
    throw std::invalid_argument("invalid rectangle source");
  }
  m_frameRect.width = rightCorner.x - leftCorner.x;
  m_frameRect.height = rightCorner.y - leftCorner.y;
  double posX = leftCorner.x + m_frameRect.width / 2;
  double posY = leftCorner.y + m_frameRect.height / 2;
  m_frameRect.pos = {posX, posY};
}

zhalilov::Rectangle::~Rectangle()
{
}

double zhalilov::Rectangle::getArea() const
{
  return m_frameRect.width * m_frameRect.height;
}

zhalilov::rectangle_t zhalilov::Rectangle::getFrameRect() const
{
  return m_frameRect;
}

void zhalilov::Rectangle::move(const point_t &point)
{
  m_frameRect.pos = point;
}

void zhalilov::Rectangle::move(const double dx, const double dy)
{
  m_frameRect.pos = {m_frameRect.pos.x + dx, m_frameRect.pos.y + dy};
}

void zhalilov::Rectangle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("scaling ratio should be more than zero");
  }
  m_frameRect.width *= ratio;
  m_frameRect.height *= ratio;
}
