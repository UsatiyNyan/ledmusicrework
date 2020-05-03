#ifndef ANIMATIONPRESETTINGS_H
#define ANIMATIONPRESETTINGS_H

#include <QWidget>
#include "animation.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AnimationPreSettings; }
QT_END_NAMESPACE

class AnimationPreSettings : public QWidget {
Q_OBJECT

public:
    explicit AnimationPreSettings(QWidget *parent = nullptr, Player *player = nullptr);
    ~AnimationPreSettings() override;

signals:
    void new_mode(int mode);

private slots:
    void on_buttonSetWL_clicked();
    void on_selectMode_currentIndexChanged(int index);
    void on_new_setting();

public:
    Animation animation_;
private:
    Ui::AnimationPreSettings *ui;
    Player *_player;
};


#endif // ANIMATIONPRESETTINGS_H
