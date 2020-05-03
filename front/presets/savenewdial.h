#ifndef SAVENEWDIAL_H
#define SAVENEWDIAL_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class SaveNewDial; }
QT_END_NAMESPACE

class SaveNewDial : public QDialog {
Q_OBJECT

public:
    explicit SaveNewDial(QWidget *parent = nullptr);
    ~SaveNewDial();

signals:
    void new_filename(QString filename);

private slots:
    void on_buttonCancelOk_accepted();
    void on_buttonCancelOk_rejected();

private:
    Ui::SaveNewDial *ui;
};


#endif // SAVENEWDIAL_H
