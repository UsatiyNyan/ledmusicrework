//
// Created by kira on 30.04.2020.
//

#include "circle.h"

namespace geometry {
Circle::Circle(const Point &center) : _center(center) {}
Circle::Circle(const Circle &other) : _center(other._center) {}
Circle::Circle(Circle &&other) noexcept : _center(other._center) {}
void Circle::expand() {
    _radius += 8;
}
Point Circle::get_center() const {
    return _center;
}
size_t Circle::get_radius() const {
    return _radius;
}
Circles::Circles(const Point &center, size_t size)
    : _circles(size, Circle(center)) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i; j < size; ++j) {
            _circles[i].expand();
        }
    }
}
Circles::Circles(Point &&center, size_t size)
    : _circles(size, Circle(center)) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i; j < size; ++j) {
            _circles[i].expand();
        }
    }
}
Circles::Circles(Circles &&other) noexcept {
    this->_circles = std::move(other._circles);
}
Circles &Circles::operator=(Circles &&other) noexcept {
    this->_circles = std::move(other._circles);
    return *this;
}
Circle &Circles::operator[](size_t i) {
    return _circles[i];
}
}  // namespace geometry
