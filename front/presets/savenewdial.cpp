#include "savenewdial.h"
#include "ui_savenewdial.h"
#include <QKeyEvent>


SaveNewDial::SaveNewDial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveNewDial) {
    ui->setupUi(this);
    ui->editNewName->setPlainText("cool_edm_preset");
}

SaveNewDial::~SaveNewDial() {
    delete ui;
}

void SaveNewDial::on_buttonCancelOk_accepted() {
    emit new_filename(ui->editNewName->toPlainText());
    this->close();
}

void SaveNewDial::on_buttonCancelOk_rejected() {
    this->close();
}
