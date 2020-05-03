#ifndef LED_PLAYER_FRONT_MAIN_WINDOW_INCLUDE_MAIN_WINDOW_H_
#define LED_PLAYER_FRONT_MAIN_WINDOW_INCLUDE_MAIN_WINDOW_H_

#include <QWidget>
#include "player.h"
#include "color.h"
#include "devices.h"
#include "animationpresettings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_previewCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Player player;
    SerialThread serial_thread;
    AudioThread audio_thread;
    FFTWThread fftw_thread;
};


#endif //LED_PLAYER_FRONT_MAIN_WINDOW_INCLUDE_MAIN_WINDOW_H_
