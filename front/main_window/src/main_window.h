#ifndef LED_PLAYER_FRONT_MAIN_WINDOW_SRC_MAIN_WINDOW_H_
#define LED_PLAYER_FRONT_MAIN_WINDOW_SRC_MAIN_WINDOW_H_

#include <QWidget>
#include <QTimer>

#include "devices.h"
#include "container.h"
#include <vector>
#include <thread>

enum Tabs {DEVICES, COLOR_SETTINGS, ANIMATION_SETTINGS, ANIMATION_PREVIEW};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
 Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = nullptr, loop::LockFreeContainer *container = nullptr);
    ~MainWindow() override;

 private slots:
    void on_previewCheckBox_stateChanged(int arg1);

 public:
    std::vector<QWidget *> widgets;

 private:
    Ui::MainWindow *_ui;
    QTimer *_updater;
};


#endif //LED_PLAYER_FRONT_MAIN_WINDOW_SRC_MAIN_WINDOW_H_
