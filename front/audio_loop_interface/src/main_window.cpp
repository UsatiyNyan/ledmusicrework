#include "main_window.h"
#include "ui_main_window.h"
#include "animation_view.h"


#define DELAY 5000

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabbableMainWindow),
    player(Player(DELAY)),
    serial_thread(&player),
    audio_thread(&player),
    fftw_thread(&player) {
    ui->setupUi(this);
    auto devices = new Devices(this, &player);
    auto color = new Color(this, &player);
    auto animation_pre_settings = new AnimationPreSettings(this, &player);
    auto animation_view = new AnimationView(this, &player);

    QObject::connect(devices, SIGNAL(start_capture()), &audio_thread, SLOT(start()));
    QObject::connect(devices, SIGNAL(start_capture()), &fftw_thread, SLOT(start()));
    QObject::connect(devices, SIGNAL(start_port(
                                         const QSerialPortInfo &)),
                     &serial_thread, SLOT(start_port(
                                              const QSerialPortInfo &)));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), color, SLOT(update()));
    QObject::connect(&fftw_thread, SIGNAL(new_data()),
                     &animation_pre_settings->animation_, SLOT(update()));
    QObject::connect(ui->buttonSubmit, SIGNAL(clicked()),
                     &animation_pre_settings->animation_, SLOT(on_buttonSubmit_clicked()));
    QObject::connect(&fftw_thread, SIGNAL(new_data()), animation_view, SLOT(update()));
    QObject::connect(&animation_pre_settings->animation_, SIGNAL(change_verteces(int,
                                                                     const fPoint *, float, int)),
                     animation_view, SLOT(animation_changed(int,
                                              const fPoint *, float, int)));
    QObject::connect(&animation_pre_settings->animation_, SIGNAL(change_rotation(float)),
                     animation_view, SLOT(rotation_changed(float)));

    ui->tabWidget->insertTab(0, devices, QString("devices"));
    ui->tabWidget->insertTab(1, color, QString("colors"));
    ui->tabWidget->insertTab(2, animation_pre_settings, QString("animation settings"));
    ui->tabWidget->insertTab(3, animation_view, QString("animation preview"));
}

MainWindow::~MainWindow() {
    delete ui;
    for (int kI = 0; kI < 3; ++kI) {
        delete ui->tabWidget->widget(kI);
    }
}

void MainWindow::on_previewCheckBox_stateChanged(int arg1) {
    ui->tabWidget->widget(3)->setUpdatesEnabled(arg1);
}
