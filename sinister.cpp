#include "sinister.h"
#include "ui_sinister.h"

Sinister::Sinister(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sinister)
{
    ui->setupUi(this);
}

Sinister::~Sinister()
{
    delete ui;
}
