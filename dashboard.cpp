#include "dashboard.h"
#include "ui_dashboard.h"
#include "sinister.h"

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_pushButton_2_clicked()
{
    sinister=new Sinister(this);
    sinister->show();
}

