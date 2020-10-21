#ifndef LED_PLAYER_FRONT_SERIAL_PORT_INTERFACE_SRC_SERIAL_PORT_INTERFACE_H_
#define LED_PLAYER_FRONT_SERIAL_PORT_INTERFACE_SRC_SERIAL_PORT_INTERFACE_H_

#include <QWidget>
#include <QSerialPortInfo>

#include "serial_loop.h"
#include "color_processor.h"
#include "container.h"


class SerialPortInterface : public QWidget {
 Q_OBJECT

 public:
    explicit SerialPortInterface(QWidget *parent = nullptr, loop::LockFreeContainer *container = nullptr);
    ~SerialPortInterface() override;

 public slots:
    void on_start_port(const QSerialPortInfo &serial_port_info);

    void on_set_basic();
    void on_set_circle(geometry::Point center);
    void on_set_polygon(const std::vector<geometry::Point>& vertices, int16_t degree);
    void on_set_bpm(uint16_t bpm);
    void on_set_length_and_width(uint16_t length, uint16_t width);
 private:
    clr::RGB &_rgb;
    loop::SerialLoop *_serial_loop = nullptr;
};


#endif //LED_PLAYER_FRONT_SERIAL_PORT_INTERFACE_SRC_SERIAL_PORT_INTERFACE_H_
