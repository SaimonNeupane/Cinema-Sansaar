#include "mahajatra.h"
#include "ui_mahajatra.h"

Mahajatra::Mahajatra(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mahajatra)
{
    ui->setupUi(this);
}

Mahajatra::~Mahajatra()
{
    delete ui;
}
