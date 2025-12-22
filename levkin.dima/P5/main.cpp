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

class Polygon : public Shape {
  point_t *points;
  size_t len;
  point_t anchor = {0, 0};
  Polygon(point_t *points, size_t len) : points(points), len(len) {}
  double getArea() const override {
    double area = .0;
    for (size_t i = 0; i < len; ++i) {
      const point_t &p1 = points[i];
      const point_t &p2 = points[(1 + i) % len];
      area += (p1.x * p2.y) - (p2.x * p1.y);
    }
    return (area > 0 ? area : -area) / 2.0;
  }
  virtual rectangle_t getFrameRect() const override {
    if (len == 0) {
      return {0, 0, {0, 0}};
    }

    double min_x = points[0].x;
    double max_x = points[0].x;
    double min_y = points[0].y;
    double max_y = points[0].y;

    for (size_t i = 1; i < len; ++i) {
      const point_t &point = points[i];
      if (point.x < min_x) {
        min_x = point.x;
      }
      if (point.x > max_x) {
        max_x = point.x;
      }
      if (point.y < min_y) {
        min_y = point.y;
      }
      if (point.y > max_y) {
        max_y = point.y;
      }
    }

    double width = max_x - min_x;
    double height = max_y - min_y;
    point_t center = {min_x + width / 2, min_y + height / 2};
    return {width, height, center};
  }
  virtual void move(point_t dest) override {
    double dx = dest.x - anchor.x;
    double dy = dest.y - anchor.y;
    move(dx, dy);
  }
  virtual void move(double dx, double dy) override {
    for (size_t i = 0; i < len; ++i) {
      point_t &point = points[i];
      point.x += dx;
      point.y += dy;
    }
    anchor.x += dx;
    anchor.y += dy;
  }
  virtual void scale(double k) override {}
  ~Polygon() { delete points; }
  Polygon(const Polygon &poly) = default;
  Polygon(Polygon &&poly) = default;
  Polygon &operator=(const Polygon &poly) = default;
  Polygon &operator=(Polygon &&poly) = default;
  point_t find_center() const {}
};
} // namespace levkin


int main() {}
