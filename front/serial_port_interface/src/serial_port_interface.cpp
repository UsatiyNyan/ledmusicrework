#include <string>
#include "serial_port_interface.h"


SerialPortInterface::SerialPortInterface(QWidget *parent, clr::RGB *rgb) :
    QWidget(parent),
    _rgb(rgb) {
}

SerialPortInterface::~SerialPortInterface() {
    delete _serial_loop;
}

void SerialPortInterface::on_start_port(const QSerialPortInfo &serial_port_info) {
    delete _serial_loop;
    std::string serial_port(std::string("/dev/") + serial_port_info.portName().toUtf8().data());
    _serial_loop = new loop::SerialLoop(*_rgb, serial_port);
    _serial_loop->run();
}
