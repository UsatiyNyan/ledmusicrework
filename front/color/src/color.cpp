#include "color.h"
#include "ui_color.h"
#include <QtMath>
#include <QDebug>
#include <QPainter>
#include "presets.h"


Color::Color(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::color),
    player(player),
    qpoints(new QPoint[player->msg.actual_size()]),
    presets(new ColorsPresets) {
    ui->setupUi(this);
    ui->sliderBlue->setRange(0, player->msg.actual_size() - 1);
    ui->sliderGreen->setRange(0, player->msg.actual_size() - 1);
    ui->sliderRed->setRange(0, player->msg.actual_size() - 1);
    ui->sliderWidth->setRange(0, player->msg.actual_size() - 1);
    ui->nobSensitivity->setRange(-50, 50);
    ui->nobFilter->setRange(0, 400);
    ui->nobBPM->setRange(1, 240);
    ui->nobImpactR->setRange(0, 400);
    ui->nobImpactG->setRange(0, 400);
    ui->nobImpactB->setRange(0, 400);

    ui->sliderBlue->setSliderPosition(player->rgb_parameters.blue_peak);
    ui->sliderGreen->setSliderPosition(player->rgb_parameters.green_peak);
    ui->sliderRed->setSliderPosition(player->rgb_parameters.red_peak);
    ui->sliderWidth->setSliderPosition(player->rgb_parameters.width);
    ui->checkMinFilter->setCheckState(Qt::CheckState(((int) player->rgb_parameters.tweak_by_min) * 2));
    ui->nobBPM->setSliderPosition(player->rgb_parameters.bpm);
    ui->editBPM->setPlainText("100");
    ui->nobImpactR->setSliderPosition(400);
    ui->nobImpactG->setSliderPosition(400);
    ui->nobImpactB->setSliderPosition(400);

    // presets window
    QObject::connect(ui->buttonPresets, SIGNAL(clicked()), presets, SLOT(show()));
    QObject::connect(ui->buttonPresets, SIGNAL(clicked()), presets, SLOT(raise()));
    presets->set_params(&player->rgb_parameters);
    QObject::connect(presets, SIGNAL(new_setting()), this, SLOT(on_new_preset()));
}

Color::~Color() {
    delete ui;
    delete[] qpoints;
    delete presets;
}

void Color::on_sliderWidth_valueChanged(int value) {
    player->rgb_parameters.width = value;
}

void Color::on_sliderRed_valueChanged(int value) {
    player->rgb_parameters.red_peak = value;
}

void Color::on_sliderGreen_valueChanged(int value) {
    player->rgb_parameters.green_peak = value;
}

void Color::on_sliderBlue_valueChanged(int value) {
    player->rgb_parameters.blue_peak = value;
}

void Color::on_nobSensitivity_valueChanged(int value) {
    player->rgb_parameters.sensitivity = 255.f / 5000 * qPow(2, (double) value / 20); // 1..INF
}

void Color::on_nobFilter_valueChanged(int value) {
    player->rgb_parameters.filter = (float_t) value / 400;
}

void Color::on_checkMinFilter_stateChanged(int arg1) {
    player->rgb_parameters.tweak_by_min = arg1;
}

void Color::on_nobBPM_valueChanged(int value) {
    player->rgb_parameters.bpm = value;
    ui->editBPM->setPlainText(QString(std::to_string(player->rgb_parameters.bpm).c_str()));
}

void Color::on_editBPM_textChanged() {
    int tmp = (int) strtol(ui->editBPM->toPlainText().toUtf8().data(), nullptr, 10);
    if (tmp >= 1) {
        player->rgb_parameters.bpm = tmp;
    }
    ui->nobBPM->setSliderPosition(tmp);
}

void Color::on_nobImpactR_valueChanged(int value) {
    player->rgb_parameters.red_imp = (float_t) value / 400;
}

void Color::on_nobImpactG_valueChanged(int value) {
    player->rgb_parameters.green_imp = (float_t) value / 400;
}

void Color::on_nobImpactB_valueChanged(int value) {
    player->rgb_parameters.blue_imp = (float_t) value / 400;
}

void Color::on_buttonReset_clicked() {
    player->rgb_parameters.tweak(RGBParameters());
    ui->sliderBlue->setSliderPosition(player->rgb_parameters.blue_peak);
    ui->sliderGreen->setSliderPosition(player->rgb_parameters.green_peak);
    ui->sliderRed->setSliderPosition(player->rgb_parameters.red_peak);
    ui->sliderWidth->setSliderPosition(player->rgb_parameters.width);
    ui->checkMinFilter->setCheckState(Qt::CheckState(((int) player->rgb_parameters.tweak_by_min) * 2));
    ui->nobBPM->setSliderPosition(player->rgb_parameters.bpm);
    ui->editBPM->setPlainText("100");
    ui->nobImpactR->setSliderPosition(400);
    ui->nobImpactG->setSliderPosition(400);
    ui->nobImpactB->setSliderPosition(400);
}

void Color::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate(ui->sliderBlue->x(),
                       (float) (ui->sliderBlue->y() + height()) / 2);

    float rpeak = player->rgb_parameters.red_peak;
    float gpeak = player->rgb_parameters.green_peak;
    float bpeak = player->rgb_parameters.blue_peak;
    float width = player->rgb_parameters.width;
    float smpls = player->msg.actual_size();
    float snstv = player->rgb_parameters.sensitivity * 10000 / 255;

    painter->setPen(QColor(player->rgb.r, player->rgb.g, player->rgb.b));
    for (int32_t i = 0; i < player->msg.actual_size(); ++i) {
        qpoints[i] = QPoint(i * ui->sliderBlue->width() / player->msg.actual_size(),
                            -(int32_t) (player->msg.fft[i] * (float_t) i * snstv));
    }

    painter->drawPolyline(qpoints, player->msg.actual_size());
    painter->setPen(QColor(255, 0, 0));
    painter->drawLine(std::max((int32_t) ((float_t) ui->sliderBlue->width() * (rpeak - width / 2) / smpls), 0),
                      0,
                      (int32_t) ((float_t) ui->sliderBlue->width() * rpeak / smpls),
                      (int32_t) (-100 * player->rgb_parameters.red_imp));
    painter->drawLine(std::min((int32_t) ((float_t) ui->sliderBlue->width() * (rpeak + width / 2) / smpls),
                               ui->sliderBlue->width()),
                      0,
                      (int32_t) ((float_t) ui->sliderBlue->width() * rpeak / smpls),
                      (int32_t) (-100 * player->rgb_parameters.red_imp));

    painter->setPen(QColor(0, 255, 0));
    painter->drawLine(std::max((int32_t) ((float_t) ui->sliderBlue->width() * (gpeak - width / 2) / smpls), 0),
                      0,
                      (int32_t) ((float_t) ui->sliderBlue->width() * gpeak / smpls),
                      (int32_t) (-100 * player->rgb_parameters.green_imp));
    painter->drawLine(std::min((int32_t) ((float_t) ui->sliderBlue->width() * (gpeak + width / 2) / smpls),
                               ui->sliderBlue->width()),
                      0,
                      (int32_t) ((float_t) ui->sliderBlue->width() * gpeak / smpls),
                      (int32_t) (-100 * player->rgb_parameters.green_imp));

    painter->setPen(QColor(0, 0, 255));
    painter->drawLine(std::max((int32_t) ((float_t) ui->sliderBlue->width() * (bpeak - width / 2) / smpls), 0),
                      0,
                      (int32_t) ((float_t) ui->sliderBlue->width() * bpeak / smpls),
                      (int32_t) (-100 * player->rgb_parameters.blue_imp));
    painter->drawLine(std::min((int32_t) ((float_t) ui->sliderBlue->width() * (bpeak + width / 2) / smpls),
                               ui->sliderBlue->width()),
                      0,
                      (int32_t) ((float_t) ui->sliderBlue->width() * bpeak / smpls),
                      (int32_t) (-100 * player->rgb_parameters.blue_imp));

    if (player->rgb_parameters.filter) {
        painter->setPen(QColor(0, 0, 0));
        painter->drawLine(0, -(int32_t) (snstv * smpls / 8 * player->rgb_parameters.filter),
                          ui->sliderBlue->width(), -(int32_t) (snstv * smpls / 8 * player->rgb_parameters.filter));
    }
    painter->restore();
    delete painter;
}

void Color::on_new_preset() {
    ui->sliderBlue->setSliderPosition(player->rgb_parameters.blue_peak);
    ui->sliderGreen->setSliderPosition(player->rgb_parameters.green_peak);
    ui->sliderRed->setSliderPosition(player->rgb_parameters.red_peak);
    ui->sliderWidth->setSliderPosition(player->rgb_parameters.width);
    ui->checkMinFilter->setCheckState(Qt::CheckState(((int) player->rgb_parameters.tweak_by_min) * 2));
    ui->nobBPM->setSliderPosition(player->rgb_parameters.bpm);
    ui->nobSensitivity->setSliderPosition(player->rgb_parameters.sensitivity * 5000 / 255.f);
    ui->editBPM->setPlainText(std::to_string(player->rgb_parameters.bpm).data());
    ui->nobImpactR->setSliderPosition((int) (player->rgb_parameters.red_imp * 400.f));
    ui->nobImpactG->setSliderPosition((int) (player->rgb_parameters.green_imp * 400.f));
    ui->nobImpactB->setSliderPosition((int) (player->rgb_parameters.blue_imp * 400.f));
}
