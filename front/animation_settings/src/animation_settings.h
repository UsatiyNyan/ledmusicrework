#ifndef LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_ANIMATION_SETTINGS_H_
#define LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_ANIMATION_SETTINGS_H_

#include <QWidget>
#include "polygon_preview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AnimationSettings; }
QT_END_NAMESPACE

class AnimationSettings : public QWidget {
 Q_OBJECT

 public:
    explicit AnimationSettings(QWidget *parent = nullptr, container::FixedQueue<clr::RGB> *rgb_queue = nullptr);
    ~AnimationSettings() override;

    PolygonPreview *get_polygon_preview();

 signals:
    void new_mode(int mode);
    void set_length_and_width(uint16_t length, uint16_t width);

 private slots:
    void on_buttonSetWL_clicked();
    void on_selectMode_currentIndexChanged(int index);
    void on_new_setting();

 private:
    PolygonPreview _polygon_preview;
    Ui::AnimationSettings *_ui;
};


#endif //LED_PLAYER_FRONT_ANIMATION_SETTINGS_SRC_ANIMATION_SETTINGS_H_
