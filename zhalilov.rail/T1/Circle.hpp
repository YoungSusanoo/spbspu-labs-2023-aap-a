#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

namespace zhalilov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &center, const double radius);
    virtual ~Circle();
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(const point_t &point);
    virtual void move(const double dx, const double dy);
    virtual void scale(const double ratio);
  private:
    rectangle_t m_frameRect;
  };
}

#endif
