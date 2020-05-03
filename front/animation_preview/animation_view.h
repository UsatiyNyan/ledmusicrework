#ifndef ANIMATION_VIEW_H
#define ANIMATION_VIEW_H

#include <QWidget>
#include "player.h"
#include "polygon.h"
#include "fixed_queue.h"


#define POLYGON_AMOUNT 30

QT_BEGIN_NAMESPACE
namespace Ui { class AnimationView; }
QT_END_NAMESPACE

class AnimationView : public QWidget {
Q_OBJECT

public:
    explicit AnimationView(QWidget *parent = nullptr, Player *player = nullptr);
    ~AnimationView() override;

public slots:
    void animation_changed(int verteces, const fPoint *vectors, float radius, int mode);
    void rotation_changed(float rot);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::AnimationView *ui;
    Player *player;
    Polygon *base_polygon;
    fixed_queue<Polygon *, POLYGON_AMOUNT> *polygons;
    fPoint *transformation_matrix;
};


#endif // ANIMATION_VIEW_H
