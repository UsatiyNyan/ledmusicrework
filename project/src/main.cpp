//
// Created by kira on 04.05.2020.
//
#include "main_window.h"
#include <QApplication>
#include "serial_port_interface.h"
#include "audio_loop_interface.h"
#include "container.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.showMaximized();

    loop::LockFreeContainer container(1024);
    clr::RGBParameters parameters{
        128,
        0,
        1024,
        512,
        1,
        1,
        1,
        0,
        1,
        true
    };

    clr::RGB &rgb = container.get_rgb();
    std::vector<float> &fft = container.get_fft();

    SerialPortInterface serial_port_interface(nullptr, &rgb);
    AudioLoopInterface audio_loop_interface(nullptr, &container, &parameters, 1024);

    QObject::connect(main_window.widgets[DEVICES], SIGNAL(start_port(const QSerialPortInfo &)),
        &serial_port_interface, SLOT(on_start_port(const QSerialPortInfo &)));
    QObject::connect(main_window.widgets[DEVICES], SIGNAL(start_capture(const pa::Device &)),
        &audio_loop_interface, SLOT(on_start_capture(const pa::Device &)));


    return QApplication::exec();
}
