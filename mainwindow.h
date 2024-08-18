#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<Qtsql>
#include<QSqlDatabase>
#include<QPushButton>
#include "dashboard.h"
// #include "signup.h"
#include "database.h"
#include "verification.h"
#include "change_pass.h"
#include<QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connect_stackedWidget();//button connection for stacked widget
    void connect_checkbox();//checkbox of show password
    void on_Login_clicked();//login page->login button
    void on_SendVerificationCode_clicked();//to open dialog box
    void sendVerificationCode(const QString &email);
    void on_SendVerificationCode_2_clicked();

private:
    Ui::MainWindow *ui;
    Dashboard *dashboard;
    Verification *verify;
    Change_pass *new_pass;
    Database db;
    QPushButton *widget_index[4];//for button connection for stacked widget

    // Signup related members
    QNetworkAccessManager *networkManager;
    QString apiKey;
    QString mailgunDomain;
    QString verificationCode;

};
#endif // MAINWINDOW_H
