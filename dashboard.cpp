#include "dashboard.h"
#include "ui_dashboard.h"
#include "seatselection.h"
#include "sinister.h"
#include "kabir.h"
#include "mirzapur.h"
#include "sanju.h"
#include "harry.h"
#include "mahajatra.h"
#include "thor.h"


Dashboard::Dashboard(const QString &loggedInUser, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
    , loggedInUsername(loggedInUser)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_pushButton_2_clicked()
{
    seatselect=new SeatSelection(loggedInUsername, 2,this);
    seatselect->show();
}


void Dashboard::on_pushButton_clicked()
{
    kabir=new Kabir(loggedInUsername,this);
    kabir->show();
}


void Dashboard::on_pushButton_3_clicked()
{
    thor=new Thor(loggedInUsername,this);
    thor->show();
}


void Dashboard::on_pushButton_4_clicked()
{
    sanju=new Sanju(loggedInUsername,this);
    sanju->show();
}


void Dashboard::on_pushButton_5_clicked()
{
    mahajatra=new Mahajatra(loggedInUsername,this);
    mahajatra->show();
}


void Dashboard::on_pushButton_6_clicked()
{
    harry=new Harry(loggedInUsername,this);
    harry->show();
}


void Dashboard::on_pushButton_7_clicked()
{
    mirzapur=new Mirzapur(loggedInUsername,this);
    mirzapur->show();
}

