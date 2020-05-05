#include "main_window.h"
#include "ui_main_window.h"
#include "color_settings.h"
#include "animation_view.h"
#include "animation_settings.h"


MainWindow::MainWindow(QWidget *parent, loop::LockFreeContainer *container) :
    QWidget(parent),
    _ui(new Ui::MainWindow),
    _updater(new QTimer(this)) {
    _ui->setupUi(this);
    auto devices = new Devices(this);
    auto color_settings = new ColorSettings(this, &container->get_fft(), &container->get_rgb());
    auto animation_view = new AnimationView(this, &container->get_rgb_queue());
    auto animation_settings = new AnimationSettings(this, &container->get_rgb_queue());
    auto polygon_preview = animation_settings->get_polygon_preview();

    QObject::connect(_ui->buttonSubmit, SIGNAL(clicked()), polygon_preview, SLOT(on_buttonSubmit_clicked()));
    QObject::connect(polygon_preview, SIGNAL(set_circle(geometry::Point)),
        animation_view, SLOT(on_set_circle(geometry::Point)));
    QObject::connect(polygon_preview, SIGNAL(set_polygon(const std::vector<geometry::Point> &, int16_t)),
        animation_view, SLOT(on_set_polygon(const std::vector<geometry::Point> &, int16_t)));


    _ui->tabWidget->insertTab(DEVICES, devices, "devices");
    _ui->tabWidget->insertTab(COLOR_SETTINGS, color_settings, "color_settings");
    _ui->tabWidget->insertTab(ANIMATION_VIEW, animation_view, "animation preview");
    _ui->tabWidget->insertTab(ANIMATION_SETTINGS, animation_settings, "animation settings");

    widgets.assign({
        devices,
        color_settings,
        animation_view,
        animation_settings,
        polygon_preview
        });

    QObject::connect(_updater, SIGNAL(timeout()), color_settings, SLOT(update()));
    QObject::connect(_updater, SIGNAL(timeout()), animation_view, SLOT(update()));
    QObject::connect(_updater, SIGNAL(timeout()), polygon_preview, SLOT(update()));
    _updater->start(50);
}

MainWindow::~MainWindow() {
    for (QWidget *widget: widgets) {
        delete widget;
    }
    delete _ui;
}

void MainWindow::on_previewCheckBox_stateChanged(int arg1) {
    _ui->tabWidget->widget(ANIMATION_VIEW)->setUpdatesEnabled(arg1);
}
