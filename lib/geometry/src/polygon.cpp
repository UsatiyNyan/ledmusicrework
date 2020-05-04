//
// Created by kira on 27.11.2019.
//

#include "polygon.h"
#include "base_exception.h"
#include <cmath>

namespace geometry {
Polygon::Polygon(const std::vector<Point> &vertices)
    : _vertices(vertices.cbegin(), vertices.cend()) {
    float abs = std::sqrt(_vertices[0].x * _vertices[0].x + _vertices[0].y * _vertices[0].y);
    _ind_cos = (_vertices[0].x / abs) > (_vertices[0].y / abs);
    if (_ind_cos) {  // TODO: ??????????
        _cos = _vertices[0].y / abs;
    } else {
        _cos = _vertices[0].x / abs;
    }
}
void Polygon::expand(const std::vector<Point> &tr_matrix) {
    if (tr_matrix.size() != 2) {
        throw exception::Exception("wrong size of transformation matrix");
    }
    float coef = 0;
    if (_ind_cos) {
        coef = (_vertices[0].y + _cos) / _vertices[0].y;
    } else {
        coef = (_vertices[0].x + _cos) / _vertices[0].x;
    }
    for (auto &vertex: _vertices) {
        vertex.x *= coef;
        vertex.y *= coef;
    }
    for (auto &vertex: _vertices) {
        vertex.x = tr_matrix[0].x * vertex.x + tr_matrix[1].x * vertex.y;
        vertex.y = tr_matrix[0].y * vertex.x + tr_matrix[1].y * vertex.y;
    }
}
const std::vector<Point> &Polygon::get_vertices() const {
    return _vertices;
}
Point &Polygon::operator[](size_t i) {
    return _vertices[i];
}
Polygons::Polygons(const std::vector<Point> &vertices, size_t size, const std::vector<Point> &tr_matrix)
    : _polygons(size, Polygon(vertices)) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            _polygons[i].expand(tr_matrix);
        }
    }
}
Polygons::Polygons(Polygons &&other) noexcept {
    this->_polygons = std::move(other._polygons);
}
Polygons &Polygons::operator=(Polygons &&other) noexcept {
    this->_polygons = std::move(other._polygons);
    return *this;
}
Polygon &Polygons::operator[](size_t i) {
    return _polygons[i];
}
}  // namespace geometry
