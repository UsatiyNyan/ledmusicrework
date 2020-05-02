//
// Created by kira on 27.11.2019.
//

#ifndef PLAYER_LIB_PLAYER_POLYGON_H_
#define PLAYER_LIB_PLAYER_POLYGON_H_

#include "point.h"
#include <vector>

namespace geometry {
class Polygon {
 public:
    explicit Polygon(const std::vector<Point> &vertices);
    void expand(const std::vector<Point> &tr_matrix);
    Point &operator[](size_t i);
    [[nodiscard]] const std::vector<Point> &get_vertices() const;
 private:
    std::vector<Point> _vertices;
    float _cos = 0;
    bool _ind_cos = false;
};
class Polygons {
 public:
    Polygons(const std::vector<Point> &vertices, size_t size, const std::vector<Point> &tr_matrix);
    Polygons(Polygons &&other) noexcept;
    Polygons &operator=(Polygons &&other) noexcept;
    Polygon &operator[](size_t i);
 private:
    std::vector<Polygon> _polygons;
};
}  // namespace geometry

#endif //PLAYER_LIB_PLAYER_POLYGON_H_
