#ifndef LED_PLAYER_FRONT_DEVICES_SRC_DEVICES_H_
#define LED_PLAYER_FRONT_DEVICES_SRC_DEVICES_H_

#include <QWidget>
#include <QtCore/QStringListModel>
#include <QSerialPort>

#include "list_devices.h"
#include <map>


QT_BEGIN_NAMESPACE
namespace Ui { class Devices; }
QT_END_NAMESPACE

class Devices : public QWidget {
 Q_OBJECT

 public:
    explicit Devices(QWidget *parent = nullptr);
    ~Devices() override;

 signals:
    void start_capture(const pa::Device &audio_device);
    void start_port(const QSerialPortInfo &serial_port_info);

 private:
    void load_ports();
    void load_cards();

 private slots:
    void on_select_card_clicked();
    void on_select_port_clicked();

 private:
    Ui::Devices *_ui;
    QStringListModel *_sound_card_list;
    QStringListModel *_ports_list;
    std::map<std::string, pa::Device> _name_device_map;
};


#endif //LED_PLAYER_FRONT_DEVICES_SRC_DEVICES_H_
