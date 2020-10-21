#ifndef LED_PLAYER_FRONT_PRESETS_SRC_PRESETS_H_
#define LED_PLAYER_FRONT_PRESETS_SRC_PRESETS_H_

#include <QWidget>
#include "color_processor.h"
#include "new_preset_dialog.h"
#include "polygon.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Presets; }
QT_END_NAMESPACE

class Presets : public QWidget {
 Q_OBJECT

 public:
    explicit Presets(QWidget *parent = nullptr);
    ~Presets() override;

    void showEvent(QShowEvent *) override;

 protected slots:
    void dispatch_filename(const QString &filename);
    virtual void parse_files();
    virtual void on_buttonApply_clicked() = 0;
 protected:
    [[nodiscard]] virtual QString identifier() const = 0;
    virtual QString get_param_string() = 0;

 protected:
    Ui::Presets *_ui;
 private:
    NewPresetDialog *_dialog;
};


class ColorPresets : public Presets {
 Q_OBJECT

 public:
    explicit ColorPresets(QWidget *parent = nullptr, clr::RGBParameters *params = nullptr);

 signals:
    void new_setting();

 protected slots:
    void on_buttonApply_clicked() override;

 protected:
    [[nodiscard]] QString identifier() const override;
    QString get_param_string() override;

 private:
    clr::RGBParameters &_params;
};


class AnimationPresets : public Presets {
 Q_OBJECT

 public:
    explicit AnimationPresets(QWidget *parent = nullptr, int *mode = nullptr, std::vector<geometry::Point> *base_vertices = nullptr,
                              geometry::Point *base_center = nullptr, int16_t *base_degree = nullptr);

 signals:
    void new_setting();

 protected slots:
    void on_buttonApply_clicked() override;

 protected:
    [[nodiscard]] QString identifier() const override;
    QString get_param_string() override;

 private:
    int &_mode;
    std::vector<geometry::Point> &_base_vertices;
    geometry::Point &_base_center;
    int16_t &_base_degree;
};


#endif //LED_PLAYER_FRONT_PRESETS_SRC_PRESETS_H_
