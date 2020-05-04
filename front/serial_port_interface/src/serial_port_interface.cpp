#include <string>
#include "serial_port_interface.h"


SerialPortInterface::SerialPortInterface(QWidget *parent, loop::LockFreeContainer *container) :
    QWidget(parent),
    _rgb(container->get_rgb()) {
}

SerialPortInterface::~SerialPortInterface() {
    delete _serial_loop;
}

void SerialPortInterface::on_start_port(const QSerialPortInfo &serial_port_info) {
    delete _serial_loop;
    std::string serial_port(std::string("/dev/") + serial_port_info.portName().toUtf8().data());
    _serial_loop = new loop::SerialLoop(_rgb, serial_port);
    _serial_loop->run();
}
void SerialPortInterface::on_set_basic() {
    _serial_loop->set_basic();
}
void SerialPortInterface::on_set_circle(geometry::Point center) {
    _serial_loop->set_circle(center);
}
void SerialPortInterface::on_set_polygon(const std::vector<geometry::Point> &vertices) {
    _serial_loop->set_polygon(vertices);
}
void SerialPortInterface::on_set_bpm(uint16_t bpm) {
    _serial_loop->set_bpm(bpm);
}
void SerialPortInterface::on_set_rotation(uint8_t degree) {
    _serial_loop->set_rotation(degree);
}
void SerialPortInterface::on_set_length_and_width(uint16_t length, uint16_t width) {
    _serial_loop->set_length_and_width(length, width);
}
