#ifndef LED_PLAYER_FRONT_PRESETS_SRC_SAVENEWDIAL_H_
#define LED_PLAYER_FRONT_PRESETS_SRC_SAVENEWDIAL_H_

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class SaveNewDial; }
QT_END_NAMESPACE

class SaveNewDial : public QDialog {
Q_OBJECT

public:
    explicit SaveNewDial(QWidget *parent = nullptr);
    ~SaveNewDial() override;

signals:
    void new_filename(QString filename);

private slots:
    void on_buttonCancelOk_accepted();
    void on_buttonCancelOk_rejected();

private:
    Ui::SaveNewDial *_ui;
};


#endif //LED_PLAYER_FRONT_PRESETS_SRC_SAVENEWDIAL_H_
