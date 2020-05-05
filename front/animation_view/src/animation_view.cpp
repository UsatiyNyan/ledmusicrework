#include "animation_view.h"
#include "ui_animation_view.h"
#include <QPainter>
#include <cmath>


AnimationView::AnimationView(QWidget *parent, container::FixedQueue<clr::RGB> *rgb_queue) :
    QWidget(parent),
    _ui(new Ui::AnimationView),
    _circles({0, 0}, rgb_queue->size()),
    _polygons(
        {{0, 2}, {1, -1}, {-1, -1}},
        rgb_queue->size(),
        {{1.3, 0}, {0, 1.3}}),
    _rgb_queue(*rgb_queue) {
    _ui->setupUi(this);
    setUpdatesEnabled(false);
}

AnimationView::~AnimationView() {
    delete _ui;
}

void AnimationView::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate(QPoint{width() / 2, height() / 2});

    _rgb_queue.update();
    for (size_t i = 0; i < _rgb_queue.size(); ++i) {
        auto rgb = _rgb_queue[i];
        auto color = QColor(
            static_cast<int>(rgb.r),
            static_cast<int>(rgb.g),
            static_cast<int>(rgb.b)
            );
        painter->setBrush(color);
        painter->setPen(color);
        if (_is_circle) {
            auto &circle = _circles[i];
            QPointF center{
                circle.get_center().x,
                circle.get_center().y
            };
            painter->drawEllipse(center, circle.get_radius(), circle.get_radius());
        } else {
            auto &vertices = _polygons[i].get_vertices();
            QPolygon polygon{static_cast<int>(vertices.size())};
            for (const auto &vertex: vertices) {
                polygon.push_back(QPoint(
                    static_cast<int>(vertex.x),
                    static_cast<int>(vertex.y)
                ));
            }
            painter->drawPolygon(polygon);
        }
    }
    painter->restore();
    delete painter;
}
void AnimationView::on_set_circle(geometry::Point center) {
    _circles = geometry::Circles(center, _rgb_queue.size());
    _is_circle = true;
}
void AnimationView::on_set_polygon(const std::vector<geometry::Point> &vertices, int16_t degree) {
    float radian = static_cast<float>(degree + 180) *
        static_cast<float>(M_PI) / 180;
    std::vector<geometry::Point> tr_matrix{
        { std::cos(radian), std::sin(radian)},
        {-std::sin(radian), std::cos(radian)}
    };
    _polygons = geometry::Polygons{vertices, _rgb_queue.size(), tr_matrix};
    _is_circle = false;
}

