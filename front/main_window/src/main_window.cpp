#include "main_window.h"
#include "ui_main_window.h"
//#include "animation_view.h"

enum Tabs {DEVICES, COLORS, SETTINGS, PREVIEW};

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    auto devices = new Devices(this);

    _ui->tabWidget->insertTab(DEVICES, devices, QString("devices"));
//    _ui->tabWidget->insertTab(COLORS, color, QString("colors"));
//    _ui->tabWidget->insertTab(SETTINGS, animation_pre_settings, QString("animation settings"));
//    _ui->tabWidget->insertTab(PREVIEW, animation_view, QString("animation preview"));
}

MainWindow::~MainWindow() {
    for (size_t i = 0; i < 4; ++i) {
        delete _ui->tabWidget->widget(i);
    }
    delete _ui;
}

void MainWindow::on_previewCheckBox_stateChanged(int arg1) {
    _ui->tabWidget->widget(PREVIEW)->setUpdatesEnabled(arg1);
}
