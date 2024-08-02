#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(ui->checkBox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->lineEdit_2->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void MainWindow::on_Login_clicked()
{
    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    sqlitedb.setDatabaseName("C:/Users/ACER/Desktop/Cinema-Sansaar/Database/Data.db");

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;

    if (sqlitedb.open()) {
        qDebug() << "Database opened successfully";

        QSqlQuery query(sqlitedb);
        query.prepare("SELECT * FROM User WHERE username = :username AND password = :password");

        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (query.exec()) {
            qDebug() << "Query executed successfully";

            if (query.next()) {

                qDebug() << "Login Successful";
                hide();
                dashboard = new Dashboard(this);
                dashboard->showMaximized();
            } else {
                qDebug() << "No user exists with those credentials";
            }
        } else {
            QString errorMsg = "Database error: " + query.lastError().text();
            qDebug() << errorMsg;
        }

        sqlitedb.close();
        qDebug() << "Database connection closed";
    } else {
        QString errorMsg = "Cannot connect with database: " + sqlitedb.lastError().text();
        qDebug() << errorMsg;
    }
}

void MainWindow::on_Signup_clicked()
{
    signup = new Signup(this);
        signup->show();
}

