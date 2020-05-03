#ifndef LED_PLAYER_FRONT_MAIN_WINDOW_SRC_MAIN_WINDOW_H_
#define LED_PLAYER_FRONT_MAIN_WINDOW_SRC_MAIN_WINDOW_H_

#include <QWidget>
#include "devices.h"
//#include "player.h"
//#include "color.h"
//#include "animationpresettings.h"


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
    Ui::MainWindow *_ui;
};


#endif //LED_PLAYER_FRONT_MAIN_WINDOW_SRC_MAIN_WINDOW_H_
