//
// Created by kira on 04.05.2020.
//
#include "main_window.h"
#include "serial_port_interface.h"
#include "audio_loop_interface.h"
#include "container.h"

#include <QApplication>



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    loop::LockFreeContainer container(1024);

    MainWindow main_window(nullptr, &container);
    main_window.showMaximized();

    SerialPortInterface serial_port_interface(nullptr, &container);
    QObject::connect(main_window.widgets[DEVICES], SIGNAL(start_port(const QSerialPortInfo &)),
                     &serial_port_interface, SLOT(on_start_port(const QSerialPortInfo &)));
    QObject::connect(main_window.widgets[COLOR_SETTINGS], SIGNAL(set_bpm(uint16_t)),
                     &serial_port_interface, SLOT(on_set_bpm(uint16_t)));

    AudioLoopInterface audio_loop_interface(nullptr, &container, 1024);
    QObject::connect(main_window.widgets[DEVICES], SIGNAL(start_capture(const pa::Device &)),
        &audio_loop_interface, SLOT(on_start_capture(const pa::Device &)));
    QObject::connect(main_window.widgets[COLOR_SETTINGS], SIGNAL(set_params(const clr::RGBParameters &)),
        &audio_loop_interface, SLOT(on_set_params(const clr::RGBParameters &)));

    return QApplication::exec();
}
