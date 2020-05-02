//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_POLYGON_INCLUDE_CIRCLE_H_
#define RPI_LED_LIB_POLYGON_INCLUDE_CIRCLE_H_

#include "point.h"
#include <vector>

namespace geometry {
class Circle {
 public:
    explicit Circle(const Point &center);
    void expand();
    [[nodiscard]] Point get_center() const;
    [[nodiscard]] size_t get_radius() const;
 private:
    Point _center;
    size_t _radius = 0;
};
class Circles {
 public:
    Circles(const Point &center, size_t size);
    Circles(Circles &&other) noexcept;
    Circles &operator=(Circles &&other) noexcept;
    Circle &operator[](size_t i);
 private:
    std::vector<Circle> _circles;
};
}  // namespace geometry

#endif //RPI_LED_LIB_POLYGON_INCLUDE_CIRCLE_H_
