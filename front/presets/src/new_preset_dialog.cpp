#include "new_preset_dialog.h"
#include "ui_new_preset_dialog.h"
#include <QKeyEvent>


NewPresetDialog::NewPresetDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewPresetDialog) {
    _ui->setupUi(this);
    _ui->editNewName->setPlainText("cool_edm_preset");
}

NewPresetDialog::~NewPresetDialog() {
    delete _ui;
}

void NewPresetDialog::on_buttonCancelOk_accepted() {
    emit new_filename(_ui->editNewName->toPlainText());
    this->close();
}

void NewPresetDialog::on_buttonCancelOk_rejected() {
    this->close();
}
