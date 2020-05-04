#ifndef LED_PLAYER_FRONT_SERIAL_PORT_INTERFACE_SRC_SERIAL_PORT_INTERFACE_H_
#define LED_PLAYER_FRONT_SERIAL_PORT_INTERFACE_SRC_SERIAL_PORT_INTERFACE_H_

#include <QWidget>
#include <QSerialPortInfo>

#include "serial_loop.h"
#include "color.h"


class SerialPortInterface : public QWidget {
 Q_OBJECT

 public:
    explicit SerialPortInterface(QWidget *parent = nullptr, clr::RGB *rgb = nullptr);
    ~SerialPortInterface() override;

 public slots:
    void on_start_port(const QSerialPortInfo &serial_port_info);

 private:
    clr::RGB *_rgb;
    loop::SerialLoop *_serial_loop = nullptr;
};


#endif //LED_PLAYER_FRONT_SERIAL_PORT_INTERFACE_SRC_SERIAL_PORT_INTERFACE_H_
