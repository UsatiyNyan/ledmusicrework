#ifndef LED_PLAYER_FRONT_PRESETS_SRC_NEW_PRESET_DIALOG_H_
#define LED_PLAYER_FRONT_PRESETS_SRC_NEW_PRESET_DIALOG_H_

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class NewPresetDialog; }
QT_END_NAMESPACE

class NewPresetDialog : public QDialog {
Q_OBJECT

public:
    explicit NewPresetDialog(QWidget *parent = nullptr);
    ~NewPresetDialog() override;

signals:
    void new_filename(const QString &filename);

private slots:
    void on_buttonCancelOk_accepted();
    void on_buttonCancelOk_rejected();

private:
    Ui::NewPresetDialog *_ui;
};


#endif //LED_PLAYER_FRONT_PRESETS_SRC_NEW_PRESET_DIALOG_H_
