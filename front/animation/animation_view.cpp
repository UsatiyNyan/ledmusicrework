#include "animation_view.h"
#include "ui_animation_view.h"
#include <QPainter>
#include <cmath>
#include <unistd.h>


AnimationView::AnimationView(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::AnimationView),
    player(player),
    base_polygon(new Polygon(5, 0, 0, 0)),
    polygons(new fixed_queue<Polygon *, POLYGON_AMOUNT>),
    transformation_matrix(new fPoint[2]) {
    ui->setupUi(this);
    float_t phi = -0.1;
    transformation_matrix[0].x = 1.3f * std::cos(phi);
    transformation_matrix[0].y = std::sin(phi);
    transformation_matrix[1].x = -std::sin(phi);
    transformation_matrix[1].y = 1.3f * std::cos(phi);

    fPoint base_matrix[5] = {1, 0, 0.3, -0.9, -0.8, -0.6, -0.8, 0.6, 0.3, 0.9};
    base_polygon->set_items(base_matrix);
    setUpdatesEnabled(false);
}

AnimationView::~AnimationView() {
    delete ui;
    delete base_polygon;
    delete polygons;
    delete[] transformation_matrix;
}

void AnimationView::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate((float) width() / 2, (float) height() / 2);

    auto tmp = new Polygon(*base_polygon);
    tmp->color = QColor(player->rgb.r, player->rgb.g, player->rgb.b);
    polygons->push_back(tmp);

    for (unsigned kI = 0; kI < polygons->size(); ++kI) {
        auto polygon = polygons->at(kI);
        painter->setBrush(polygon->color);
        painter->setPen(polygon->color);

        if (polygon->mode == 0) {
            painter->drawPolygon(polygon->vectors->data(), polygon->vectors->size());
            *polygon *= transformation_matrix;
        } else if (polygon->mode == 1) {
            auto center = QPoint(0, 0);
            if (!base_polygon->vectors->empty()) {
                center.setX(polygon->vectors->data()->x());
                center.setY(polygon->vectors->data()->y());
            }
            painter->drawEllipse(center, (int32_t) (polygon->radius), (int32_t) (polygon->radius));
            polygon->radius *= 1.2;
        }

    }
    usleep(800000 / player->rgb_parameters.bpm);
    painter->restore();
    delete painter;
}

void AnimationView::animation_changed(int verteces, const fPoint *vectors, float radius, int mode) {
    if (mode == 2) {
        return;
    }
    delete base_polygon;
    base_polygon = new Polygon(verteces, 0, 0, 0, 10 * radius, mode);
    fPoint tmp_vectors[verteces];
    for (int kI = 0; kI < verteces; ++kI) {
        tmp_vectors[kI].x = 16 * vectors[kI].x;
        tmp_vectors[kI].y = 16 * vectors[kI].y;
    }
    base_polygon->set_items(tmp_vectors);
}

void AnimationView::rotation_changed(float rot) {
    base_polygon->rotation = rot;
    transformation_matrix[0].x = 1.3f * std::cos(rot);
    transformation_matrix[0].y = std::sin(rot);
    transformation_matrix[1].x = -std::sin(rot);
    transformation_matrix[1].y = 1.3f * std::cos(rot);
}
