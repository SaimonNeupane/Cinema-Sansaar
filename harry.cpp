#include "harry.h"
#include "ui_harry.h"

Harry::Harry(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Harry)
{
    ui->setupUi(this);
}

Harry::~Harry()
{
    delete ui;
}
