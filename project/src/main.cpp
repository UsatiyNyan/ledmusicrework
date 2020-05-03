//
// Created by kira on 04.05.2020.
//
#include "main_window.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.showMaximized();
    return QApplication::exec();
}
