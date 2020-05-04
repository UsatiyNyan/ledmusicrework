//
// Created by kira on 14.11.2019.
//

#include "serial_thread.h"
#include <QDebug>

SerialThread::SerialThread(Player *player)
    : player(player), serial_port(), isConnected(false), serial_port_info(new QSerialPortInfo()) {}

void SerialThread::run() {
    serial_port = new QSerialPort();
    serial_port->setPort(*serial_port_info);
    isConnected = serial_port->open(QSerialPort::WriteOnly);
    qDebug() << serial_port->errorString();
    if (isConnected) {
        serial_port->setBaudRate(QSerialPort::Baud19200);
        serial_port->setDataBits(QSerialPort::Data8);
        serial_port->setParity(QSerialPort::NoParity);
        serial_port->setStopBits(QSerialPort::StopBits::);
        serial_port->setFlowControl(QSerialPort::NoFlowControl);
    }
    QByteArray send_data;
    while (isConnected) {
        usleep(player->delay);
        if (serial_port->write(player->msg.text.c_str()) > 0) {
            serial_port->waitForBytesWritten(10);
//            qDebug() << player->msg.text.c_str() << serial_port->bytesToWrite();
        }
    }
    delete serial_port;
}

SerialThread::~SerialThread() {
    delete serial_port_info;
}

void SerialThread::start_port(const QSerialPortInfo &q_serial_port) {
    isConnected = false;
    *serial_port_info = q_serial_port;
    this->start();
}
