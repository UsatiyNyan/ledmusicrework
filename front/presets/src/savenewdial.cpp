#include "savenewdial.h"
#include "ui_savenewdial.h"
#include <QKeyEvent>


SaveNewDial::SaveNewDial(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::SaveNewDial) {
    _ui->setupUi(this);
    _ui->editNewName->setPlainText("cool_edm_preset");
}

SaveNewDial::~SaveNewDial() {
    delete _ui;
}

void SaveNewDial::on_buttonCancelOk_accepted() {
    emit new_filename(_ui->editNewName->toPlainText());
    this->close();
}

void SaveNewDial::on_buttonCancelOk_rejected() {
    this->close();
}
