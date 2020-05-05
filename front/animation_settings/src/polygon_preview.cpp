#include "polygon_preview.h"
#include "ui_polygon_preview.h"
#include <QPainter>
#include <memory>


PolygonPreview::PolygonPreview(QWidget *parent, container::FixedQueue<clr::RGB> *rgb_queue) :
    QWidget(parent),
    _ui(new Ui::PolygonPreview),
//    _animation_presets(new AnimationPresets),
    _rgb_queue(*rgb_queue) {
    _ui->setupUi(this);
    // presets window
//    QObject::connect(_animation_presets, SIGNAL(new_setting()), parent, SLOT(on_new_setting()));
//    QObject::connect(_ui->buttonPresets, SIGNAL(clicked()), _animation_presets, SLOT(show()));
//    QObject::connect(_ui->buttonPresets, SIGNAL(clicked()), _animation_presets, SLOT(raise()));
//    QObject::connect(_animation_presets, SIGNAL(new_setting()), this, SLOT(update_settings()));
//    _animation_presets->set_params(base_polygon);
    emit on_spinBox_valueChanged(1);
}

PolygonPreview::~PolygonPreview() {
    delete _ui;
//    delete _animation_presets;
}

void PolygonPreview::on_buttonSubmit_clicked() {
    switch (_mode) {
        case BASIC: {
            emit set_basic();
        }
        case CIRCLE: {
            emit set_circle(_base_center);
        }
        case POLYGON: {
            emit set_polygon(_base_verices, _base_degree);
        }
    }
}

void PolygonPreview::on_new_mode(int mode) {
    _mode = mode;
    switch (_mode) {
        case BASIC: {
            _ui->spinBox->setDisabled(true);
            _ui->editRotation->setDisabled(true);
            for (auto &coord : _text_coords) {
                coord.first->setDisabled(true);
                coord.second->setDisabled(true);
            }
        }
        case CIRCLE: {
            _ui->editRotation->setDisabled(true);
            _text_coords[0].first->setEnabled(true);
            _text_coords[0].second->setEnabled(true);
            _text_coords[0].first->update();
            _text_coords[0].second->update();
            for (size_t i = 1; i < _text_coords.size(); ++i) {
                _text_coords[i].first->setDisabled(true);
                _text_coords[i].second->setDisabled(true);
            }
        }
        case POLYGON: {
            _ui->spinBox->setEnabled(true);
            _ui->editRotation->setEnabled(true);
            for (auto &coord : _text_coords) {
                coord.first->setEnabled(true);
                coord.second->setEnabled(true);
            }
        }
    }
}

void PolygonPreview::on_spinBox_valueChanged(int arg1) {
    while (arg1 > _text_coords.size()) {
        push_point({0, 0});
        _base_verices.push_back({0, 0});
    }
    while (arg1 < _text_coords.size()) {
        pop_point();
        _base_verices.pop_back();
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
    _base_verices = std::move(tmp_vertices);
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

    switch (_mode) {
        case BASIC: {
            break;
        }
        case CIRCLE: {
            painter->drawEllipse(QPointF{_base_center.x, _base_center.y}, 64, 64);
            break;
        }
        case POLYGON: {
            std::vector<QPointF> q_points;
            for (const auto &vertex: _base_verices) {
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

//void PolygonPreview::update_settings() {
//    _ui->editRotation->setPlainText(QString::number(base_polygon->rotation));
//    on_new_mode(base_polygon->mode);
//    while (!vertices->empty()) {
//        pop_point();
//    }
//    for (auto &real_vector: *base_polygon->real_vectors) {
//        push_point(real_vector);
//    }
//    for (auto kI = 0; kI < vertices->size(); ++kI) {
//        vertices->at(kI).first->setPlainText(QString::number(base_polygon->real_vectors->at(kI).x));
//        vertices->at(kI).second->setPlainText(QString::number(base_polygon->real_vectors->at(kI).y));
//    }
//    on_buttonSubmit_clicked();
//    _ui->spinBox->setValue(base_polygon->real_vectors->size());
//}

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
}

void PolygonPreview::pop_point() {
    _text_coords.pop_back();
}