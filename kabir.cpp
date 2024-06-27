#include "kabir.h"
#include "ui_kabir.h"

Kabir::Kabir(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Kabir)
{
    ui->setupUi(this);
}

Kabir::~Kabir()
{
    delete ui;
}
