//
// Created by kira on 04.05.2020.
//
#include "devices.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Devices devices;
    devices.show();
    return QApplication::exec();
}
