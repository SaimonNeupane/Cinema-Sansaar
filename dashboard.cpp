#include "dashboard.h"
#include "ui_dashboard.h"
#include "sinister.h"
#include "kabir.h"
#include "mirzapur.h"
#include "sanju.h"
#include "harry.h"
#include "mahajatra.h"
#include "thor.h"


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


void Dashboard::on_pushButton_clicked()
{
    kabir=new Kabir(this);
    kabir->show();
}


void Dashboard::on_pushButton_3_clicked()
{
    thor=new Thor(this);
    thor->show();
}


void Dashboard::on_pushButton_4_clicked()
{
    sanju=new Sanju(this);
    sanju->show();
}


void Dashboard::on_pushButton_5_clicked()
{
    mahajatra=new Mahajatra(this);
    mahajatra->show();
}


void Dashboard::on_pushButton_6_clicked()
{
    harry=new Harry(this);
    harry->show();
}


void Dashboard::on_pushButton_7_clicked()
{
    mirzapur=new Mirzapur(this);
    mirzapur->show();
}

