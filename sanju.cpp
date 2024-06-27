#include "sanju.h"
#include "ui_sanju.h"

Sanju::Sanju(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sanju)
{
    ui->setupUi(this);
}

Sanju::~Sanju()
{
    delete ui;
}
