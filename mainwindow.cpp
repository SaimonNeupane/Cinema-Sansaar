#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "database.h"

#include <QRandomGenerator>
#include <QSqlError>
#include <QNetworkRequest>
#include <QNetworkReply>
#include<QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , apiKey("") //Mailgun API key here
    , mailgunDomain("") //Mailgun domain here
    , verificationCode(QString::number(QRandomGenerator::global()->bounded(100000, 999999)))
{
    ui->setupUi(this);
    connect_stackedWidget();
    connect_checkbox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_stackedWidget()
{
    // Access the QStackedWidget from the UI
    QStackedWidget *stackedWidget = ui->stackedWidget;
    //button pointers
    widget_index[0]= ui->Signup;
    widget_index[1]= ui->login_goBack;//already have an account button
    widget_index[2]= ui->Forgot;
    // widget_index[3]= ui->;
    connect(widget_index[0], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(1); // Switch to second page,signup page
    });
    connect(widget_index[1], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(0); // Switch to first page,login
    });
    connect(widget_index[2], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(2); // Switch to third page,forgot page
    });
    // connect(widget_index[3], &QPushButton::clicked, this, [=]() {
    //     stackedWidget->setCurrentIndex(0); // Switch to first page,login page
    // });
    // Show the first widget initially
    stackedWidget->setCurrentIndex(0);
}

//checkbox connection
void MainWindow::connect_checkbox(){
    struct {
        QCheckBox *checkbox;
        QLineEdit *lineEdit;
    } checkboxLineEditPairs[] = {
        { ui->checkBox_1, ui->lineEdit2_1 },
        { ui->checkBox_2, ui->lineEdit2_2 }
    };
    for (const auto &pair : checkboxLineEditPairs) {
        pair.lineEdit->setEchoMode(pair.checkbox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);
        connect(pair.checkbox, &QCheckBox::clicked, this, [=](bool checked) {
            pair.lineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
        });
    }
    // connect(ui->SendVerificationCode, &QPushButton::clicked, this, &MainWindow::on_SendVerificationCode_clicked);
}

//for login page
void MainWindow::on_Login_clicked()
{
    QString username = ui->lineEdit1_1->text();
    QString password = ui->lineEdit2_1->text();

    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;

    Database db;
    if (db.openDatabase() && db.authenticateUser(username, password)) {
        hide();
        dashboard = new Dashboard(this);
        dashboard->show();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::on_SendVerificationCode_clicked()
{
    QString email = ui->lineEdit3_2->text();
    sendVerificationCode(email);
    verify = new Verification(verificationCode, this);
    if (verify->exec() == QDialog::Accepted) {
        // Verification successful
        QString username =ui->lineEdit2_1->text();
        QString password =ui->lineEdit2_2->text();
        Database db;
        db.saveUserInfo(email, username, password);//(email,username,password)
    }
}
//for sending verification coded
void MainWindow::sendVerificationCode(const QString &email)
{
    QString postData = QString("from=Saimon <mailgun@%1>&to=%2&subject=Verification Code&text=Your verification code is: %3")
                           .arg(mailgunDomain).arg(email).arg(verificationCode);

    QNetworkRequest request(QUrl("https://api.mailgun.net/v3/" + mailgunDomain + "/messages"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("api:%1").arg(apiKey).toUtf8().toBase64()));

    QNetworkReply *reply = networkManager->post(request, postData.toUtf8());

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Verification", "Verification code sent successfully!");
        } else {
            QMessageBox::warning(this, "Verification", "Failed to send verification code: " + reply->errorString());
        }
        reply->deleteLater();
    });
}



