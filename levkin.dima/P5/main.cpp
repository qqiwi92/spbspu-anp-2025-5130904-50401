#include <iostream>

namespace levkin {

struct point_t {
  double x, y;
};
struct rectangle_t {
  double width, height;
  point_t pos;
};
class Shape {
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t dest) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double k) = 0;
};

class Rectangle : public Shape {
  rectangle_t data_fields;

  Rectangle(point_t center, double width, double height)
      : data_fields{width, height, center} {}
  double getArea() const override {
    return data_fields.height * data_fields.width;
  }
  virtual rectangle_t getFrameRect() const override { return data_fields; }
  virtual void move(point_t dest) override {
    data_fields.pos = {dest.x, dest.y};
  }
  virtual void move(double dx, double dy) override {
    move({data_fields.pos.x + dx, data_fields.pos.y + dy});
  }
  virtual void scale(double k) override {
    data_fields.width *= k;
    data_fields.height *= k;
  }
};

class Diamond : public Shape {
  rectangle_t data_fields;

  Diamond(point_t center, double width, double height)
      : data_fields{width, height, center} {}
  double getArea() const override {
    return .5 * data_fields.height * data_fields.width;
  }
  virtual rectangle_t getFrameRect() const override { return data_fields; }
  virtual void move(point_t dest) override {
    data_fields.pos = {dest.x, dest.y};
  }
  virtual void move(double dx, double dy) override {
    move({data_fields.pos.x + dx, data_fields.pos.y + dy});
  }
  virtual void scale(double k) override {
    data_fields.width *= k;
    data_fields.height *= k;
  }
};

} // namespace levkin
int main() {}
