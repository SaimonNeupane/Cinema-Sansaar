#include "dashboard.h"
#include "ui_dashboard.h"
#include "seatselection.h"


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
    seatselect=new SeatSelection(loggedInUsername, 3,this);
    seatselect->show();
}


void Dashboard::on_pushButton_3_clicked()
{
    seatselect=new SeatSelection(loggedInUsername, 4,this);
    seatselect->show();
}


void Dashboard::on_pushButton_4_clicked()
{
    seatselect=new SeatSelection(loggedInUsername, 5,this);
    seatselect->show();
}


void Dashboard::on_pushButton_5_clicked()
{
    seatselect=new SeatSelection(loggedInUsername, 6,this);
    seatselect->show();
}


void Dashboard::on_pushButton_6_clicked()
{
    seatselect=new SeatSelection(loggedInUsername, 1,this);
    seatselect->show();
}


void Dashboard::on_pushButton_7_clicked()
{
    seatselect=new SeatSelection(loggedInUsername, 7,this);
    seatselect->show();
}

