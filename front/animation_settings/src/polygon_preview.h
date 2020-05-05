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
#include "presets.h"

enum class AnimationMode : int {BASIC = 0, CIRCLE = 1, POLYGON = 2};


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
    void on_new_setting();

 private:
    void push_point(geometry::Point point);
    void pop_point();

 protected:
    void paintEvent(QPaintEvent *) override;

 private:
    Ui::PolygonPreview *_ui;
    AnimationPresets *_animation_presets;
    std::vector<std::pair<std::unique_ptr<QTextEdit>, std::unique_ptr<QTextEdit>>>_text_coords;
    container::FixedQueue<clr::RGB> &_rgb_queue;
    int _mode = static_cast<int>(AnimationMode::BASIC);
    std::vector<geometry::Point> _base_vertices{{{0, 0}}};
    geometry::Point _base_center{0, 0};
    int16_t _base_degree = 0;
};


#endif //LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_POLYGON_PREVIEW_H_
