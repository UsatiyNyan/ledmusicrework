#include "color_settings.h"
#include "ui_color_settings.h"
#include <QPainter>
//#include "presets.h"


ColorSettings::ColorSettings(QWidget *parent, std::vector<float> *fft, clr::RGB *rgb) :
    QWidget(parent),
    _ui(new Ui::ColorSettings),
//    _colors_presets(new ColorsPresets),
    _fft(*fft),
    _rgb(*rgb) {
    _ui->setupUi(this);
    _ui->sliderBlue->setRange(0, static_cast<int>(_fft.size()) - 1);
    _ui->sliderGreen->setRange(0, static_cast<int>(_fft.size()) - 1);
    _ui->sliderRed->setRange(0, static_cast<int>(_fft.size()) - 1);
    _ui->sliderWidth->setRange(0, static_cast<int>(_fft.size() / 2) - 1);
    _ui->nobSensitivity->setRange(0, 1000);
    _ui->nobFilter->setRange(0, 1600);
    _ui->nobBPM->setRange(1, 240);
    _ui->nobImpactR->setRange(0, 400);
    _ui->nobImpactG->setRange(0, 400);
    _ui->nobImpactB->setRange(0, 400);

    _prms = clr::RGBParameters{};
    setup_nobs();

    // presets window TODO
//    QObject::connect(_ui->buttonPresets, SIGNAL(clicked()), presets, SLOT(show()));
//    QObject::connect(_ui->buttonPresets, SIGNAL(clicked()), presets, SLOT(raise()));
//    presets->set_params(_prms);
//    QObject::connect(presets, SIGNAL(new_setting()), this, SLOT(on_new_preset()));
}

ColorSettings::~ColorSettings() {
    delete _ui;
//    delete presets;
}

void ColorSettings::on_sliderWidth_valueChanged(int value) {
    _prms.half_width = value;
    emit set_params(_prms);
}

void ColorSettings::on_sliderRed_valueChanged(int value) {
    _prms.red_peak = value;
    emit set_params(_prms);
}

void ColorSettings::on_sliderGreen_valueChanged(int value) {
    _prms.green_peak = value;
    emit set_params(_prms);
}

void ColorSettings::on_sliderBlue_valueChanged(int value) {
    _prms.blue_peak = value;
    emit set_params(_prms);
}

void ColorSettings::on_nobSensitivity_valueChanged(int value) {
    _prms.sensitivity = static_cast<float>(value) / 500; // 0..1
    emit set_params(_prms);
}

void ColorSettings::on_nobFilter_valueChanged(int value) {
    _prms.filter = static_cast<float>(value) / 6400;
    emit set_params(_prms);
}

void ColorSettings::on_checkMinFilter_stateChanged(int arg1) {
    _prms.tweak_by_min = arg1;
    emit set_params(_prms);
}

void ColorSettings::on_nobBPM_valueChanged(int value) {
    _prms.bpm = value;
    _ui->editBPM->setPlainText(QString(std::to_string(value).c_str()));
    emit set_bpm(value);
}

void ColorSettings::on_editBPM_textChanged() {
    int value = static_cast<int>(strtol(_ui->editBPM->toPlainText().toUtf8().data(), nullptr, 10));
    if (value >= 1) {
        _prms.bpm = value;
        _ui->nobBPM->setSliderPosition(value);
        emit set_bpm(value);
    }
}

void ColorSettings::on_nobImpactR_valueChanged(int value) {
    _prms.red_imp = static_cast<float>(value) / 400;
    emit set_params(_prms);
}

void ColorSettings::on_nobImpactG_valueChanged(int value) {
    _prms.green_imp = static_cast<float>(value) / 400;
    emit set_params(_prms);
}

void ColorSettings::on_nobImpactB_valueChanged(int value) {
    _prms.blue_imp = static_cast<float>(value) / 400;
    emit set_params(_prms);
}

void ColorSettings::on_buttonReset_clicked() {
    _prms = clr::RGBParameters();
    setup_nobs();
}

void ColorSettings::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate(_ui->sliderBlue->x(),
                       static_cast<float>(_ui->sliderBlue->y() + height()) / 2);

    auto rpeak = static_cast<float>(_prms.red_peak);
    auto gpeak = static_cast<float>(_prms.green_peak);
    auto bpeak = static_cast<float>(_prms.blue_peak);
    auto width = static_cast<float>(_prms.half_width * 2);
    auto smpls = static_cast<float>(_fft.size());
    auto snstv = _prms.sensitivity;
    auto blue_slider_width = static_cast<float>(_ui->sliderBlue->width());
    float height = 200;

    painter->setPen(QColor(
        static_cast<int>(_rgb.r),
        static_cast<int>(_rgb.g),
        static_cast<int>(_rgb.b)
        ));
    std::vector<QPoint> pts{_fft.size()};
    for (size_t i = 0; i < _fft.size(); ++i) {
        pts[i] = QPoint(
            static_cast<int>(i * blue_slider_width / _fft.size()),
            -static_cast<int>(_fft[i] * i * snstv));
    }
    painter->drawPolyline(pts.data(), pts.size());

    // red ----------------------------------------------
    painter->setPen(QColor(255, 0, 0));
    painter->drawLine(std::max(static_cast<int>(blue_slider_width * (rpeak - width / 2) / smpls), 0),
                      0,
                      static_cast<int>(blue_slider_width * rpeak / smpls),
                      static_cast<int>(-height * _prms.red_imp));
    painter->drawLine(std::min(blue_slider_width * (rpeak + width / 2) / smpls,
                               blue_slider_width),
                      0,
                      static_cast<int>(blue_slider_width * rpeak / smpls),
                      static_cast<int>(-height * _prms.red_imp));

    // green --------------------------------------------
    painter->setPen(QColor(0, 255, 0));
    painter->drawLine(std::max(static_cast<int>(blue_slider_width * (gpeak - width / 2) / smpls), 0),
                      0,
                      static_cast<int>(blue_slider_width * gpeak / smpls),
                      static_cast<int>(-height * _prms.green_imp));
    painter->drawLine(std::min(blue_slider_width * (gpeak + width / 2) / smpls,
                               blue_slider_width),
                      0,
                      static_cast<int>(blue_slider_width * gpeak / smpls),
                      static_cast<int>(-height * _prms.green_imp));

    // blue ---------------------------------------------
    painter->setPen(QColor(0, 0, 255));
    painter->drawLine(std::max(static_cast<int>(blue_slider_width * (bpeak - width / 2) / smpls), 0),
                      0,
                      static_cast<int>(blue_slider_width * bpeak / smpls),
                      static_cast<int>(-height * _prms.blue_imp));
    painter->drawLine(std::min(blue_slider_width * (bpeak + width / 2) / smpls,
                               blue_slider_width),
                      0,
                      static_cast<int>(blue_slider_width * bpeak / smpls),
                      static_cast<int>(-height * _prms.blue_imp));

    if (_prms.filter > 0) {
        painter->setPen(QColor(0, 0, 0));
        painter->drawLine(0, -static_cast<int>(snstv * smpls * _prms.filter),
                          blue_slider_width, -static_cast<int>(snstv * smpls * _prms.filter));
    }
    painter->restore();
    delete painter;
}

void ColorSettings::on_new_preset() {
    setup_nobs();
}
void ColorSettings::setup_nobs() {
    _ui->sliderBlue->setSliderPosition(_prms.blue_peak);
    _ui->sliderGreen->setSliderPosition(_prms.green_peak);
    _ui->sliderRed->setSliderPosition(_prms.red_peak);
    _ui->sliderWidth->setSliderPosition(_prms.half_width);
    _ui->checkMinFilter->setCheckState(Qt::CheckState(static_cast<int>(_prms.tweak_by_min) * 2));
    _ui->nobBPM->setSliderPosition(_prms.bpm);
    _ui->nobSensitivity->setSliderPosition(static_cast<int>(_prms.sensitivity * 500));
    _ui->editBPM->setPlainText(std::to_string(_prms.bpm).c_str());
    _ui->nobImpactR->setSliderPosition(static_cast<int>(_prms.red_imp * 400.f));
    _ui->nobImpactG->setSliderPosition(static_cast<int>(_prms.green_imp * 400.f));
    _ui->nobImpactB->setSliderPosition(static_cast<int>(_prms.blue_imp * 400.f));
    emit set_bpm(_prms.bpm);
    emit set_params(_prms);
}
