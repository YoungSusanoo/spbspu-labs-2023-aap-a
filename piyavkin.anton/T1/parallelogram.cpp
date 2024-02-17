#include "parallelogram.hpp"
#include "base-function.hpp"

namespace piyavkin
{
  Parallelogram::Parallelogram(point_t p1, point_t p2, point_t p3):
    a_(p1),
    b_(p2),
    c_(p3)
  {
    double ab = getLength(a_, b_);
    double ac = getLength(a_, c_);
    double bc = getLength(c_, b_);
    if ((a_.y != c_.y && a_.y != b_.y && b_.y != c_.y) || ab >= ac + bc || bc >= ab + ac || ac >= ab + bc)
    {
      throw std::logic_error("It is not parallelogram");
    }
  }
  double Parallelogram::getArea() const
  {
    double a = 0;
    double h = (a_.y == c_.y) ? std::abs(b_.y - a_.y) : std::abs(a_.y - c_.y);
    if (b_.y == c_.y)
    {
      a = std::abs(b_.x - c_.x);
    }
    else
    {
      a = (a_.y == c_.y) ? std::abs(a_.x - c_.x) : std::abs(a_.x - b_.x);
    }
    return a * h;
  }
  rectangle_t Parallelogram::getFrameRect() const
  {
    double height = 0;
    double width = 0;
    point_t pos = {0, 0};
    if (a_.y == c_.y)
    {
      height = std::abs(b_.y - a_.y);
      width = std::max(std::max((std::abs(a_.x - c_.x) + b_.x), a_.x), c_.x) - std::min(std::min(a_.x, c_.x), b_.x);
      pos = {(b_.x + std::max(a_.x, c_.x)) / 2, (b_.y + c_.y) / 2};
    }
    else
    {
      height = std::abs(a_.y - c_.y);
      if (b_.y == c_.y)
      {
        width = std::max(std::max((std::abs(b_.x - c_.x) + a_.x), b_.x), c_.x) - std::min(std::min(a_.x, c_.x), b_.x);
        pos = {(a_.x + std::max(c_.x, b_.x)) / 2, (a_.y + c_.y) / 2};
      }
      else
      {
        width = std::max(std::max((std::abs(a_.x - b_.x) + c_.x), a_.x), b_.x) - std::min(std::min(a_.x, c_.x), b_.x);
        pos = {(std::max(a_.x, b_.x) + c_.x) / 2, (b_.y + c_.y) / 2};
      }
    }
    return {width, height, pos};
  }
  void Parallelogram::move(const point_t& bias)
  {
    point_t pos = {(b_.x + c_.x) / 2, (b_.y + c_.y) / 2};
    move(bias.x - pos.x, bias.y - pos.y);
  }
  void Parallelogram::move(double dx, double dy)
  {
    a_ = addShift(a_, dx, dy);
    b_ = addShift(b_, dx, dy);
    c_ = addShift(c_, dx, dy);
  }
  void Parallelogram::scaleFigure(double k)
  {
    point_t pos = {(b_.x + c_.x) / 2, (b_.y + c_.y) / 2};
    a_ = scalePoint(a_, pos, k);
    b_ = scalePoint(b_, pos, k);
    c_ = scalePoint(c_, pos, k);
  }
  Shape* Parallelogram::clone() const
  {
    return new Parallelogram(*this);
  }
}
