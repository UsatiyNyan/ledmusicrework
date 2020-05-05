#include "polygon_preview.h"
#include "ui_polygon_preview.h"
#include <QPainter>


PolygonPreview::PolygonPreview(QWidget *parent, container::FixedQueue<clr::RGB> *rgb_queue) :
    QWidget(parent),
    _ui(new Ui::PolygonPreview),
    _animation_presets(new AnimationPresets(nullptr, &_mode, &_base_vertices, &_base_center, &_base_degree)),
    _rgb_queue(*rgb_queue) {
    _ui->setupUi(this);

    QObject::connect(_ui->buttonPresets, SIGNAL(clicked()), _animation_presets, SLOT(show()));
    QObject::connect(_ui->buttonPresets, SIGNAL(clicked()), _animation_presets, SLOT(raise()));
    QObject::connect(_animation_presets, SIGNAL(new_setting()), this, SLOT(on_new_setting()));
    QObject::connect(_animation_presets, SIGNAL(new_setting()), parent, SLOT(on_new_setting()));
    emit on_spinBox_valueChanged(1);
}

PolygonPreview::~PolygonPreview() {
    delete _ui;
    delete _animation_presets;
}

void PolygonPreview::on_buttonSubmit_clicked() {
    switch (static_cast<AnimationMode>(_mode)) {
        case AnimationMode::BASIC: {
            emit set_basic();
            break;
        }
        case AnimationMode::CIRCLE: {
            emit set_circle(_base_center);
            break;
        }
        case AnimationMode::POLYGON: {
            emit set_polygon(_base_vertices, _base_degree);
            break;
        }
    }
}

void PolygonPreview::on_new_mode(int mode) {
    _mode = mode;
    switch (static_cast<AnimationMode>(_mode)) {
        case AnimationMode::BASIC: {
            _ui->spinBox->setDisabled(true);
            _ui->editRotation->setDisabled(true);
            for (auto &coord : _text_coords) {
                coord.first->setDisabled(true);
                coord.second->setDisabled(true);
            }
            break;
        }
        case AnimationMode::CIRCLE: {
            _ui->editRotation->setDisabled(true);
            _text_coords[0].first->setEnabled(true);
            _text_coords[0].second->setEnabled(true);
            _text_coords[0].first->update();
            _text_coords[0].second->update();
            for (size_t i = 1; i < _text_coords.size(); ++i) {
                _text_coords[i].first->setDisabled(true);
                _text_coords[i].second->setDisabled(true);
            }
            break;
        }
        case AnimationMode::POLYGON: {
            _ui->spinBox->setEnabled(true);
            _ui->editRotation->setEnabled(true);
            for (auto &coord : _text_coords) {
                coord.first->setEnabled(true);
                coord.second->setEnabled(true);
            }
            break;
        }
    }
}

void PolygonPreview::on_spinBox_valueChanged(int arg1) {
    while (arg1 > _text_coords.size()) {
        push_point({0, 0});
    }
    while (arg1 < _text_coords.size()) {
        pop_point();
    }
}

void PolygonPreview::on_value_changed() {
    std::vector<geometry::Point> tmp_vertices;
    for (auto &coord : _text_coords) {
        if (coord.first->toPlainText().toFloat() > 20) {
            coord.first->setText("20");
        } else if (coord.first->toPlainText().toFloat() < -20) {
            coord.first->setText("-20");
        }
        if (coord.second->toPlainText().toFloat() > 20) {
            coord.second->setText("20");
        } else if (coord.second->toPlainText().toFloat() < -20) {
            coord.second->setText("-20");
        }
        tmp_vertices.push_back({
            coord.first->toPlainText().toFloat(),
            coord.second->toPlainText().toFloat()
        });
    }
    _base_center = tmp_vertices[0];
    _base_vertices = std::move(tmp_vertices);
}

void PolygonPreview::paintEvent(QPaintEvent *) {
    auto painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate(QPoint{_ui->spinBox->x() / 2, height() / 2});

    auto rgb = _rgb_queue.back();
    auto color = QColor(
        static_cast<int>(rgb.r),
        static_cast<int>(rgb.g),
        static_cast<int>(rgb.b)
    );
    painter->setBrush(color);
    painter->setPen(color);

    switch (static_cast<AnimationMode>(_mode)) {
        case AnimationMode::BASIC: {
            break;
        }
        case AnimationMode::CIRCLE: {
            painter->drawEllipse(QPointF{_base_center.x, _base_center.y}, 64, 64);
            break;
        }
        case AnimationMode::POLYGON: {
            std::vector<QPointF> q_points;
            for (const auto &vertex: _base_vertices) {
                q_points.emplace_back(vertex.x * 64, vertex.y * 64);
            }
            painter->drawPolygon(q_points.data(), q_points.size());
            break;
        }
    }
    painter->setBrush(Qt::white);
    painter->setPen(Qt::white);
    painter->drawEllipse(QPoint(0, 0), 2, 2);

    painter->restore();
    delete painter;
}

void PolygonPreview::on_editRotation_textChanged() {
    auto text_tmp = _ui->editRotation->toPlainText();
    if (text_tmp != "") {
        auto degree = static_cast<int16_t>(text_tmp.toFloat());
        if (degree > 100) {
            _ui->editRotation->setText("100");
        } else if (degree < -100) {
            _ui->editRotation->setText("-100");
        }
        _base_degree = degree;
    }
}

void PolygonPreview::on_new_setting() {
    on_new_mode(_mode);
    while (!_text_coords.empty()) {
        pop_point();
    }
    for (const auto &vertex: _base_vertices) {
        push_point(vertex);
    }
    _ui->editRotation->setPlainText(QString::number(_base_degree));
    _ui->spinBox->setValue(_base_vertices.size());
    on_buttonSubmit_clicked();
}

void PolygonPreview::push_point(geometry::Point point) {
    auto tx = std::make_unique<QTextEdit>();
    auto ty = std::make_unique<QTextEdit>();
    tx->setFixedSize(71, 27);
    ty->setFixedSize(71, 27);
    tx->setPlainText(QString::number(point.x));
    ty->setPlainText(QString::number(point.y));
    QObject::connect(tx.get(), SIGNAL(textChanged()), this, SLOT(on_value_changed()));
    QObject::connect(ty.get(), SIGNAL(textChanged()), this, SLOT(on_value_changed()));
    _ui->mainLayout->addWidget(tx.get(), static_cast<int>(_text_coords.size()) + 4, 0);
    _ui->mainLayout->addWidget(ty.get(), static_cast<int>(_text_coords.size()) + 4, 1);
    _text_coords.emplace_back(std::move(tx), std::move(ty));
    _base_vertices.push_back({0, 0});
}

void PolygonPreview::pop_point() {
    _text_coords.pop_back();
    _base_vertices.pop_back();
}
