#ifndef LED_PLAYER_FRONT_COLOR_SETTINGS_SRC_COLOR_SETTINGS_H_
#define LED_PLAYER_FRONT_COLOR_SETTINGS_SRC_COLOR_SETTINGS_H_

#include <QWidget>
#include "rgb.h"
#include <vector>
//#include "presets.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ColorSettings; }
QT_END_NAMESPACE

class ColorSettings : public QWidget {
 Q_OBJECT

 public:
    explicit ColorSettings(QWidget *parent = nullptr,
                           std::vector<float> *fft = nullptr,
                           clr::RGB *rgb = nullptr);
    ~ColorSettings() override;
 signals:
    void set_params(const clr::RGBParameters &prms);
    void set_bpm(uint16_t bpm);
 public slots:
    void on_new_preset();

 private slots:
    void on_buttonReset_clicked();
    void on_sliderWidth_valueChanged(int value);
    void on_sliderRed_valueChanged(int value);
    void on_sliderGreen_valueChanged(int value);
    void on_sliderBlue_valueChanged(int value);
    void on_nobSensitivity_valueChanged(int value);
    void on_nobFilter_valueChanged(int value);
    void on_checkMinFilter_stateChanged(int arg1);
    void on_nobBPM_valueChanged(int value);
    void on_editBPM_textChanged();
    void on_nobImpactR_valueChanged(int value);
    void on_nobImpactG_valueChanged(int value);
    void on_nobImpactB_valueChanged(int value);

 private:
    void setup_nobs();

 protected:
    void paintEvent(QPaintEvent *) override;

 private:
    Ui::ColorSettings *_ui;
//    ColorsPresets *_colors_presets;
    clr::RGB &_rgb;
    clr::RGBParameters _prms;
    std::vector<float> &_fft;
};


#endif //LED_PLAYER_FRONT_COLOR_SETTINGS_SRC_COLOR_SETTINGS_H_
