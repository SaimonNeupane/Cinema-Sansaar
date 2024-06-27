#include "thor.h"
#include "ui_thor.h"

Thor::Thor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Thor)
{
    ui->setupUi(this);
}

Thor::~Thor()
{
    delete ui;
}
