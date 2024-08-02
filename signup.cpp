#include "signup.h"
#include "ui_signup.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QSqlError>
#include <QNetworkRequest>
#include <QNetworkReply>
#include<QSqlQuery>

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);
    apiKey = "8c6b7606bc7d7268ec49e03317f774e6-6fafb9bf-c6973a64";
    mailgunDomain = "sandbox8f3585a674ed428b964dcbe043be6515.mailgun.org";
    verificationCode = QString::number(QRandomGenerator::global()->bounded(100000, 999999));

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/Users/ACER/Desktop/Cinema-Sansaar/Database/Data.db");

    if (!database.open()) {
        QMessageBox::warning(this, "Error", "Failed to open database: " + database.lastError().text());
    }
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_sendVerificationCodeButton_clicked()
{
    QString email = ui->emailLineEdit->text();
    sendVerificationCode(email);
}

void Signup::on_verifyCodeButton_clicked()
{
    QString code = ui->codeLineEdit->text();
    verifyCode(code);
}

void Signup::sendVerificationCode(const QString &email)
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

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    saveInfo(email, username, password);
}

void Signup::verifyCode(const QString &code)
{
    if (code == verificationCode) {
        QMessageBox::information(this, "Verification", "Verification successful!");
        hide();
    } else {
        QMessageBox::warning(this, "Verification", "Verification failed. Please try again.");
    }
}

void Signup::saveInfo(const QString &email, const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO User (email, username, password) VALUES (:email, :username, :password)");
    query.bindValue(":email", email);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
}
