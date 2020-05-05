#ifndef LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_POLYGON_PREVIEW_H_
#define LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_POLYGON_PREVIEW_H_

#include "polygon.h"
#include <QWidget>
#include <QTextEdit>
#include <vector>
#include <memory>
#include "polygon.h"
#include "circle.h"
#include "fixed_queue.h"
#include "rgb.h"
//#include "presets.h"


enum AnimationMode : int {POLYGON = 0, CIRCLE = 1, BASIC = 2};

QT_BEGIN_NAMESPACE
namespace Ui { class PolygonPreview; }
QT_END_NAMESPACE

class PolygonPreview : public QWidget {
 Q_OBJECT
 friend class AnimationSettings;

 public:
    explicit PolygonPreview(QWidget *parent = nullptr, container::FixedQueue<clr::RGB> *rgb_queue = nullptr);
    ~PolygonPreview() override;

 signals:
    void set_basic();
    void set_circle(geometry::Point center);
    void set_polygon(const std::vector<geometry::Point>& vertices, int16_t degree);

 public slots:
    void on_buttonSubmit_clicked();  // buttonSubmit is in main window
    void on_new_mode(int mode);

 private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_value_changed();
    void on_editRotation_textChanged();
//    void update_settings();

 private:
    void push_point(geometry::Point point);
    void pop_point();

 protected:
    void paintEvent(QPaintEvent *) override;

 private:
    Ui::PolygonPreview *_ui;
    int _mode = BASIC;
    std::vector<geometry::Point> _base_verices{{{0, 0}}};
    geometry::Point _base_center{0, 0};
    int16_t _base_degree = 0;
    std::vector<std::pair<std::unique_ptr<QTextEdit>, std::unique_ptr<QTextEdit>>>_text_coords;
    container::FixedQueue<clr::RGB> &_rgb_queue;
//    AnimationPresets *_animation_presets;
};


#endif //LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_POLYGON_PREVIEW_H_