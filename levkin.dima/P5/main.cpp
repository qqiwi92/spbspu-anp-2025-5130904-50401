#include <iostream>
struct point_t {
  double x, y;
};
struct rectangle_t { 
    double width, height;
    point_t pos; 
};
class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t dest) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double k) = 0;
};

int main ()
{
}

