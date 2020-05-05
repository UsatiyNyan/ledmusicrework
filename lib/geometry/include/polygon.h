//
// Created by kira on 27.11.2019.
//

#ifndef LED_PLAYER_LIB_GEOMETRY_INCLUDE_POLYGON_H_
#define LED_PLAYER_LIB_GEOMETRY_INCLUDE_POLYGON_H_

#include "point.h"
#include <vector>

namespace geometry {
class Polygon {
 public:
    explicit Polygon(const std::vector<Point> &vertices);
    Polygon(const Polygon &other);
    Polygon(Polygon &&other) noexcept;
    void expand(const std::vector<Point> &tr_matrix);
    Point &operator[](size_t i);
    [[nodiscard]] const std::vector<Point> &get_vertices() const;
 private:
    std::vector<Point> _vertices;
    std::vector<Point> _expander;
};
class Polygons {
 public:
    Polygons(const std::vector<Point> &vertices, size_t size, const std::vector<Point> &tr_matrix);
    Polygons(std::vector<Point> &&vertices, size_t size, std::vector<Point> &&tr_matrix);
    Polygons(Polygons &&other) noexcept;
    Polygons &operator=(Polygons &&other) noexcept;
    Polygon &operator[](size_t i);
 private:
    std::vector<Polygon> _polygons;
};
}  // namespace geometry

#endif //LED_PLAYER_LIB_GEOMETRY_INCLUDE_POLYGON_H_
