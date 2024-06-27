#include "mirzapur.h"
#include "ui_mirzapur.h"

Mirzapur::Mirzapur(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mirzapur)
{
    ui->setupUi(this);
}

Mirzapur::~Mirzapur()
{
    delete ui;
}
