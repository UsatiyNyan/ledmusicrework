//
// Created by kira on 14.11.2019.
//

#ifndef PLAYER_QTHREAD_H
#define PLAYER_QTHREAD_H

#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include "player.h"

class SerialThread : public QThread {
    Q_OBJECT
 public:
    explicit SerialThread(Player *player);
    ~SerialThread() override;
    void run() override;

 public
    slots:
        void
    start_port(const QSerialPortInfo &);

 public:
    Player *player;
    QSerialPort *serial_port;
    QSerialPortInfo *serial_port_info;
    bool isConnected;
};

#endif //PLAYER_QTHREAD_H
