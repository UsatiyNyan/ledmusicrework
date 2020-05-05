#include "presets.h"
#include "ui_presets.h"
#include <QDir>
#include <sstream>

Presets::Presets(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::Presets),
    _dialog(new NewPresetDialog(this)) {
    _ui->setupUi(this);
    QObject::connect(_ui->buttonSaveNew, SIGNAL(clicked()), _dialog, SLOT(show()));
    QObject::connect(_dialog, SIGNAL(new_filename(const QString &)),
                     this, SLOT(dispatch_filename(const QString &)));
}

Presets::~Presets() {
    delete _ui;
    delete _dialog;
}

void Presets::dispatch_filename(const QString &filename) {
    QString params = get_param_string();
    QFile presets_file("presets/" + filename + identifier());
    presets_file.open(QIODevice::WriteOnly);
    presets_file.write(params.toUtf8());
    parse_files();
    presets_file.close();
}

void Presets::parse_files() {
    QString path("presets/");
    QDir presets_dir(path);
    if (!presets_dir.exists()) {
        presets_dir.mkpath(presets_dir.absolutePath());
    }
    QStringList filter;
    filter << "*" + identifier();
    presets_dir.setNameFilters(filter);
    _ui->listCfgs->clear();
    _ui->listCfgs->addItems(presets_dir.entryList());
}

void Presets::showEvent(QShowEvent *event) {
    parse_files();
    QWidget::showEvent(event);
}

ColorPresets::ColorPresets(QWidget *parent, clr::RGBParameters *params) : Presets(parent), _params(*params) {}

void ColorPresets::on_buttonApply_clicked() {
    QStringList param_list;
    QString filename = _ui->listCfgs->currentItem()->text();
    QFile presets_file("presets/" + filename);
    presets_file.open(QIODevice::ReadOnly);
    _params.half_width = QString(presets_file.readLine()).toInt();
    _params.red_peak = QString(presets_file.readLine()).toInt();
    _params.green_peak = QString(presets_file.readLine()).toInt();
    _params.blue_peak = QString(presets_file.readLine()).toInt();
    _params.bpm = QString(presets_file.readLine()).toInt();
    _params.red_imp = QString(presets_file.readLine()).toFloat();
    _params.green_imp = QString(presets_file.readLine()).toFloat();
    _params.blue_imp = QString(presets_file.readLine()).toFloat();
    _params.filter = QString(presets_file.readLine()).toFloat();
    _params.sensitivity = QString(presets_file.readLine()).toFloat();
    _params.tweak_by_min = QString(presets_file.readLine()).toInt();
    emit new_setting();
}

QString ColorPresets::identifier() const {
    return ".clrcfg";
}

QString ColorPresets::get_param_string() {
    std::stringstream stream;
    stream << _params.half_width << std::endl
           << _params.red_peak << std::endl
           << _params.green_peak << std::endl
           << _params.blue_peak << std::endl
           << _params.bpm << std::endl
           << _params.red_imp << std::endl
           << _params.green_imp << std::endl
           << _params.blue_imp << std::endl
           << _params.filter << std::endl
           << _params.sensitivity << std::endl
           << _params.tweak_by_min << std::endl;
    return QString(stream.str().c_str());
}

AnimationPresets::AnimationPresets(QWidget *parent, int *mode, std::vector<geometry::Point> *base_vertices,
                                   geometry::Point *base_center, int16_t *base_degree)
                                   : Presets(parent),
                                   _mode(*mode),
                                   _base_vertices(*base_vertices),
                                   _base_center(*base_center),
                                   _base_degree(*base_degree) {}

void AnimationPresets::on_buttonApply_clicked() {
    QStringList param_list;
    QString filename = _ui->listCfgs->currentItem()->text();
    QFile presets_file("presets/" + filename);
    presets_file.open(QIODevice::ReadOnly);
    _mode = QString(presets_file.readLine()).toInt();
    int vertices_amount = QString(presets_file.readLine()).toInt();
    std::vector<geometry::Point> tmp_vertices;
    for (int i = 0; i < vertices_amount; ++i) {
        auto tmp_x = QString(presets_file.readLine()).toFloat();
        auto tmp_y = QString(presets_file.readLine()).toFloat();
        tmp_vertices.push_back({tmp_x, tmp_y});
    }
    _base_vertices.assign(tmp_vertices.begin(), tmp_vertices.end());
    auto tmp_x = QString(presets_file.readLine()).toFloat();
    auto tmp_y = QString(presets_file.readLine()).toFloat();
    _base_center = {tmp_x, tmp_y};
    _base_degree = QString(presets_file.readLine()).toFloat();
    presets_file.close();
    emit new_setting();
}

QString AnimationPresets::identifier() const {
    return ".anicfg";
}

QString AnimationPresets::get_param_string() {
    std::stringstream stream;
    stream << _mode << std::endl;
    stream << _base_vertices.size() << std::endl;
    for (const auto &real_vector: _base_vertices) {
        stream << real_vector.x << std::endl;
        stream << real_vector.y << std::endl;
    }
    stream << _base_center.x << std::endl
           << _base_center.y << std::endl
           << _base_degree << std::endl;
    return QString(stream.str().c_str());
}
