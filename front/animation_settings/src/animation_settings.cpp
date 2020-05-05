#include "ui_animation_settings.h"
#include "animation_settings.h"


AnimationSettings::AnimationSettings(QWidget *parent, container::FixedQueue<clr::RGB> *rgb_queue) :
    QWidget(parent),
    _ui(new Ui::AnimationSettings),
    _polygon_preview(this, rgb_queue) {
    _ui->setupUi(this);
    _ui->gridLayout->addWidget(&_polygon_preview, 6, 0);
    QObject::connect(this, SIGNAL(new_mode(int)), &_polygon_preview, SLOT(on_new_mode(int)));
}

AnimationSettings::~AnimationSettings() {
    delete _ui;
}

PolygonPreview *AnimationSettings::get_polygon_preview() {
    return &_polygon_preview;
}

void AnimationSettings::on_buttonSetWL_clicked() {
    auto width = _ui->editWidth->toPlainText().toInt();
    auto length = _ui->editLength->toPlainText().toInt();
    if (length > 0 && width > 0) {
        emit set_length_and_width(length, width);
    }
}

void AnimationSettings::on_selectMode_currentIndexChanged(int index) {
    if (index >= 0 && index <= 2) {
        emit new_mode(index);
    }
}
void AnimationSettings::on_new_setting() {
    _ui->selectMode->setCurrentIndex(_polygon_preview._mode);
}
