#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , frame(nullptr)

{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(ui->checkBox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);

    // move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());//centering the main window
    //centering the frame
    frame = ui->frame;
    centerFrame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->lineEdit_2->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}
// on login click check
void MainWindow::on_Login_clicked()
{
    QSqlDatabase sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    sqlitedb.setDatabaseName("C:/Users/DELL/Desktop/program test/Cinema-Sansaar/Database/Data.db");
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
                ui->label_3->setText("Login Successful");
                qDebug() << "Login Successful";
                hide();
                Homepage = new homepage(this);
                Homepage->showFullScreen();

            } else {
                ui->label_3->setText("No user exists with those credentials");
                qDebug() << "No user exists with those credentials";
            }
        } else {
            QString errorMsg = "Database error: " + query.lastError().text();
            ui->label_3->setText(errorMsg);
            qDebug() << errorMsg;
        }

        sqlitedb.close();
        qDebug() << "Database connection closed";
    } else {
        QString errorMsg = "Cannot connect with database: " + sqlitedb.lastError().text();
        ui->label_3->setText(errorMsg);
        qDebug() << errorMsg;
    }
}
// on clicking signup shows signup page
void MainWindow::on_Signup_clicked()
{
    signup = new Signup(this);
    signup->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    centerFrame();  // Ensure the frame stays centered when the window is resized
}
// frame centering (window size - 2*frame size)/2 to determine the top left (x,y) position
void MainWindow::centerFrame()
{
    if (frame) {
        int x = (width() - frame->width()) / 2;
        int y = (height() - frame->height()) / 2;
        frame->move(x, y);
    }
}
