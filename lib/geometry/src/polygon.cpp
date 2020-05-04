//
// Created by kira on 27.11.2019.
//

#include "polygon.h"
#include "base_exception.h"
#include <cmath>

namespace geometry {
Polygon::Polygon(const std::vector<Point> &vertices)
    : _vertices(vertices.cbegin(), vertices.cend()) {
    for (auto &vertex: _vertices) {
        float sqrt_x2y2 = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y);
        float cos = vertex.x / sqrt_x2y2;
        float sin = vertex.y / sqrt_x2y2;
        _expander.push_back({(cos + vertex.x) / vertex.x , (sin + vertex.y) / vertex.y});
    }
}
void Polygon::expand(const std::vector<Point> &tr_matrix) {
    if (tr_matrix.size() != 2) {
        throw exception::Exception("wrong size of transformation matrix: " + std::to_string(tr_matrix.size()));
    }
    for (size_t i = 0; i < _vertices.size(); ++i) {
        _vertices[i].x *= _expander[i].x;
        _vertices[i].y *= _expander[i].y;
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
    for (size_t i = 1; i != size; ++i) {
        for (size_t j = i; j != size; ++j) {
            _polygons[j].expand(tr_matrix);
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
