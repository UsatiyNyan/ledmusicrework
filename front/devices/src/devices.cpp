#include "devices.h"
#include "ui_devices.h"
#include <QSerialPortInfo>
#include "list_devices.h"


Devices::Devices(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::Devices),
    _sound_card_list(new QStringListModel(this)),
    _ports_list(new QStringListModel(this)) {

    _ui->setupUi(this);
    load_cards();
    load_ports();
}

Devices::~Devices() {
    delete _ui;
    delete _sound_card_list;
    delete _ports_list;
}

void Devices::on_select_card_clicked() {
    emit start_capture(_ui->soundCardList->currentIndex().data().toString());
}

void Devices::on_select_port_clicked() {
    if (_ui->portsList->currentIndex().row() < QSerialPortInfo::availablePorts().count()) {
        emit start_port(QSerialPortInfo::availablePorts()[_ui->portsList->currentIndex().row()]);
    }
}

void Devices::load_ports() {
    QStringList port_string_list;
    for (const auto & port: QSerialPortInfo::availablePorts()) {
        port_string_list.push_back(port.portName());
    }
    _ports_list->setStringList(port_string_list);
    _ui->portsList->setModel(_ports_list);
}

void Devices::load_cards() {
    QStringList device_string_list;
    pa::DeviceList device_list;
    for (const auto &sink: device_list.get_sinks()) {
        device_string_list.push_back(sink.name);
    }

    for (const auto &source: device_list.get_sources()) {
        device_string_list.push_back(source.name);
    }

    _sound_card_list->setStringList(device_string_list);
    _ui->soundCardList->setModel(_sound_card_list);
}
