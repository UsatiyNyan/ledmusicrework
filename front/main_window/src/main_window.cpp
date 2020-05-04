#include "main_window.h"
#include "ui_main_window.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    auto devices = new Devices(this);

//    QObject::connect(_ui->buttonSubmit, SIGNAL(clicked()),
//                     &animation_pre_settings->animation_, SLOT(on_buttonSubmit_clicked()));


    _ui->tabWidget->insertTab(DEVICES, devices, QString("devices"));
//    _ui->tabWidget->insertTab(COLORS, color, QString("colors"));
//    _ui->tabWidget->insertTab(SETTINGS, animation_pre_settings, QString("animation settings"));
//    _ui->tabWidget->insertTab(PREVIEW, animation_view, QString("animation preview"));

    widgets.assign({devices});
}

MainWindow::~MainWindow() {
    for (QWidget *widget: widgets) {
        delete widget;
    }
    delete _ui;
}

void MainWindow::on_previewCheckBox_stateChanged(int arg1) {
    _ui->tabWidget->widget(PREVIEW)->setUpdatesEnabled(arg1);
}
