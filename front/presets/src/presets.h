#ifndef LED_PLAYER_FRONT_PRESETS_SRC_PRESETS_H_
#define LED_PLAYER_FRONT_PRESETS_SRC_PRESETS_H_

#include <QWidget>
#include "color_settings.h"
#include "polygon.h"
#include "savenewdial.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Presets; }
QT_END_NAMESPACE

class Presets : public QWidget {
Q_OBJECT
public:
    explicit Presets(QWidget *parent = nullptr);
    ~Presets() override;
    [[nodiscard]] virtual QString identifier() const = 0;
    void showEvent(QShowEvent *) override;
protected slots:
    virtual void dispatch_filename(QString filename);
    virtual void on_buttonApply_clicked() = 0;
    virtual void parse_files();
protected:
    virtual QString get_param_string() = 0;
    Ui::Presets *_ui;
private:
    SaveNewDial *_dialog;
};


class ColorsPresets : public Presets {
Q_OBJECT
public:
    void set_params(RGBParameters *params);
    [[nodiscard]] QString identifier() const override;
signals:
    void new_setting();
protected slots:
    void on_buttonApply_clicked() override;
protected:
    QString get_param_string() override;
private:
    RGBParameters *_params;
};


class AnimationPresets : public Presets {
Q_OBJECT
public:
    void set_params(Polygon *params);
    [[nodiscard]] QString identifier() const override;
signals:
    void new_setting();
protected slots:
    void on_buttonApply_clicked() override;
protected:
    QString get_param_string() override;
private:
    Polygon *_params;
};


#endif //LED_PLAYER_FRONT_PRESETS_SRC_PRESETS_H_
