#include "signup.h"
#include "ui_signup.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

Signup::Signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);

    // Initialize network manager
    networkManager = new QNetworkAccessManager(this);

    // Set your Mailgun API key and domain
    apiKey = "API KEY";
    mailgunDomain = "DOMAIN";

    // Initialize SQLite database
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/Users/ACER/Desktop/Ram.db");
    if (!database.open()) {
        qDebug() << "Error: Failed to open database:" << database.lastError();
    }
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS verification (email TEXT PRIMARY KEY, code TEXT)");
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
    QString email = ui->emailLineEdit->text();
    QString code = ui->codeLineEdit->text();
    verifyCode(email, code);
}

void Signup::sendVerificationCode(const QString &email)
{
    // Generate verification code
    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));

    // Save verification code in database
    saveVerificationCode(email, code);

    // Send verification email using Mailgun API
    QUrl url("https://api.mailgun.net/v3/" + mailgunDomain + "/messages");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postData;
    postData.append("from=Saimon Neupane <mailgun@" + mailgunDomain.toUtf8() + ">");
    postData.append("&to=" + email.toUtf8());
    postData.append("&subject=Verification Code");
    postData.append("&text=Your verification code is: " + code.toUtf8());

    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("api:%1").arg(apiKey).toUtf8().toBase64()));

    qDebug() << "Sending verification email to:" << email;
    qDebug() << "Verification code:" << code;

    // Send the network request
    QNetworkReply *reply = networkManager->post(request, postData);

    // Connect signals for debugging
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Verification", "Verification code sent successfully!");
        } else {
            QMessageBox::warning(this, "Verification", "Failed to send verification code. Error: " + reply->errorString());
        }

        qDebug() << "Response status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Response body:" << reply->readAll();

        reply->deleteLater(); // Clean up the reply object
    });
}

void Signup::verifyCode(const QString &email, const QString &code)
{
    // Check if the code matches the one saved in the database
    QSqlQuery query;
    query.prepare("SELECT * FROM verification WHERE email = :email AND code = :code");
    query.bindValue(":email", email);
    query.bindValue(":code", code);
    query.exec();

    if (query.next()) {
        QMessageBox::information(this, "Verification", "Verification successful!");
    } else {
        QMessageBox::warning(this, "Verification", "Verification failed. Please try again.");
    }
}

void Signup::saveVerificationCode(const QString &email, const QString &code)
{
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO verification (email, code) VALUES (:email, :code)");
    query.bindValue(":email", email);
    query.bindValue(":code", code);
    query.exec();
}
