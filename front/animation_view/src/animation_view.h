#ifndef LED_PLAYER_FRONT_ANIMATION_VIEW_SRC_ANIMATION_VIEW_H_
#define LED_PLAYER_FRONT_ANIMATION_VIEW_SRC_ANIMATION_VIEW_H_

#include <QOpenGLWidget>

#include "rgb.h"
#include "polygon.h"
#include "circle.h"
#include "fixed_queue.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AnimationView; }
QT_END_NAMESPACE

class AnimationView : public QOpenGLWidget {
Q_OBJECT

public:
    explicit AnimationView(QWidget *parent = nullptr, container::FixedQueue<clr::RGB> *rgb_queue = nullptr);
    ~AnimationView() override;

public slots:
    void on_set_circle(geometry::Point center);
    void on_set_polygon(const std::vector<geometry::Point>& vertices, int16_t degree);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::AnimationView *_ui;
    geometry::Circles _circles;
    geometry::Polygons _polygons;
    container::FixedQueue<clr::RGB> &_rgb_queue;
    bool _is_circle = true;
};


#endif //LED_PLAYER_FRONT_ANIMATION_VIEW_SRC_ANIMATION_VIEW_H_
