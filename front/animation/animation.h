#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"
#include "polygon.h"
#include "presets.h"
#include <QWidget>
#include <utility>
#include <QTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class animation; }
QT_END_NAMESPACE

class Animation : public QWidget {
Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr, Player *player = nullptr);
    ~Animation() override;

signals:
    void change_verteces(int verteces, const fPoint *vectors, float radius, int mode);
    void change_rotation(float rot);

public slots:
    void on_buttonSubmit_clicked();
    void on_new_mode(int mode);
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_value_changed();
    void on_editRadius_textChanged();
    void on_editRotation_textChanged();
    void update_settings();
private:
    void push_point(fPoint point);
    void pop_point();

protected:
    void paintEvent(QPaintEvent *) override;

public:
    Polygon *base_polygon;
private:
    Ui::animation *ui;
    Player *player;
    std::vector<std::pair<QTextEdit *, QTextEdit *>> *vertices;
public:
    AnimationPresets *presets;
};


#endif // ANIMATION_H
