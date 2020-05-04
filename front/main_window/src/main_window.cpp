#include "main_window.h"
#include "ui_main_window.h"
#include "color_settings.h"
#include <chrono>

using namespace std::chrono_literals;


MainWindow::MainWindow(QWidget *parent, loop::LockFreeContainer *container) :
    QWidget(parent),
    _ui(new Ui::MainWindow),
    _updater(new QTimer(this)) {
    _ui->setupUi(this);
    auto devices = new Devices(this);
    auto color_settings = new ColorSettings(this, &container->get_fft(), &container->get_rgb());

// TODO: QObject::connect(_ui->buttonSubmit, SIGNAL(clicked()), &animation_pre_settings->animation_, SLOT(on_buttonSubmit_clicked()));


    _ui->tabWidget->insertTab(DEVICES, devices, QString("devices"));
    _ui->tabWidget->insertTab(COLOR_SETTINGS, color_settings, QString("color_settings"));
//    _ui->tabWidget->insertTab(SETTINGS, animation_settings, QString("animation settings"));
//    _ui->tabWidget->insertTab(PREVIEW, animation_view, QString("animation preview"));

    widgets.assign({
        devices,
        color_settings
        });

    QObject::connect(_updater, SIGNAL(timeout()), color_settings, SLOT(update()));
    _updater->start(50);
}

MainWindow::~MainWindow() {
    for (QWidget *widget: widgets) {
        delete widget;
    }
    delete _ui;
}

void MainWindow::on_previewCheckBox_stateChanged(int arg1) {
    _ui->tabWidget->widget(ANIMATION_PREVIEW)->setUpdatesEnabled(arg1);
}
