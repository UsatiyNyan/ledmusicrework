#ifndef COLOR_H
#define COLOR_H

#include <QWidget>
#include "player.h"
#include "presets.h"


QT_BEGIN_NAMESPACE
namespace Ui { class color; }
QT_END_NAMESPACE

class Color : public QWidget {
Q_OBJECT

public:
    explicit Color(QWidget *parent = nullptr, Player *player = nullptr);
    ~Color() override;
public slots:
    void on_new_preset();
private slots:
    void on_buttonReset_clicked();
    void on_sliderWidth_valueChanged(int value);
    void on_sliderRed_valueChanged(int value);
    void on_sliderGreen_valueChanged(int value);
    void on_sliderBlue_valueChanged(int value);
    void on_nobSensitivity_valueChanged(int value);
    void on_nobFilter_valueChanged(int value);
    void on_checkMinFilter_stateChanged(int arg1);
    void on_nobBPM_valueChanged(int value);
    void on_editBPM_textChanged();
    void on_nobImpactR_valueChanged(int value);
    void on_nobImpactG_valueChanged(int value);
    void on_nobImpactB_valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::color *ui;
    Player *player;
    QPoint *qpoints;
    ColorsPresets *presets;
};


#endif // COLOR_H
