#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "database.h"

#include <QRandomGenerator>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , apiKey("")
    , mailgunDomain("")
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
    // Button pointers
    widget_index[0] = ui->Signup;
    widget_index[1] = ui->login_goBack; // already have an account button
    widget_index[2] = ui->Forgot;
    widget_index[3] = ui->login_goBack_2;
    connect(widget_index[0], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(1); // Switch to second page, signup page
    });
    connect(widget_index[1], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(0); // Switch to first page, login
    });
    connect(widget_index[2], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(2); // Switch to third page, forgot page
    });
    connect(widget_index[3], &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(0); // Switch to first page, login page
    });
    // Show the first widget initially
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::connect_checkbox()
{
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
}

// For login page
void MainWindow::on_Login_clicked()
{
    QString username = ui->lineEdit1_1->text();
    QString password = ui->lineEdit2_1->text();

    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;
    if (db.openDatabase() && db.authenticateUser(username, password)) {
        hide();
        dashboard = new Dashboard(username, this);
        dashboard->show();
        db.closeDatabase();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}


// For sending verification code
void MainWindow::sendVerificationCode(const QString &email)
{
    QString postData = QString("from=Saimon <mailgun@%1>&to=%2&subject=Verification Code&text=Your verification code is: %3")
                           .arg(mailgunDomain).arg(email).arg(verificationCode);

    QNetworkRequest request(QUrl("https://api.mailgun.net/v3/" + mailgunDomain + "/messages"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("api:%1").arg(apiKey).toUtf8().toBase64()));

    QNetworkReply *reply = networkManager->post(request, postData.toUtf8());

    connect(reply, &QNetworkReply::finished, [=]() {
        qDebug() << "Reply URL:" << reply->url();
        qDebug() << "Reply status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Reply response:" << reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Verification", "Verification code sent successfully!");
        } else {
            QMessageBox::warning(this, "Verification", "Failed to send verification code: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::on_SendVerificationCode_clicked()
{
    QString email = ui->lineEdit3_2->text();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email address cannot be empty.");
        return;
    }
    if (!db.openDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to open the database.");
        return;
    }

    if (db.doesEmailExist(email)==true) {
        // Email already exists
        QMessageBox::warning(this, "Email Exists", "The email address is already registered.");
    } else {
        // Email does not exist, proceed to send verification code
        sendVerificationCode(email);
        verify = new Verification(verificationCode, this);
        if (verify->exec() == QDialog::Accepted) {
            // Verification successful
            QString username = ui->lineEdit2_1->text();
            QString password = ui->lineEdit2_2->text();
            if (db.saveUserInfo(email, username, password)) {
                QMessageBox::information(this, "Signup", "Account created successfully.");
            } else {
                QMessageBox::critical(this, "Database Error", "Failed to save user information.");
            }
        }
        delete verify; // Clean up the verification dialog
    }
    db.closeDatabase(); // Ensure the database is closed after operations
}

void MainWindow::on_SendVerificationCode_2_clicked()
{
    QString email = ui->lineEdit3_3->text();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email address cannot be empty.");
        return;
    }
    if (!db.openDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to open the database.");
        return;
    }

    if (db.doesEmailExist(email)==true) {
        // Email is registered, send verification code
        sendVerificationCode(email);
        verify = new Verification(verificationCode, this);
        if (verify->exec() == QDialog::Accepted) {
            // Verification successful
            new_pass = new Change_pass(this);
            if (new_pass->exec() == QDialog::Accepted) {
                QString password = new_pass->getNewPassword(); // Get the new password from the dialog
                if (db.changeUserInfo(email, password)) {
                    QMessageBox::information(this, "Success", "Password has been changed successfully.");
                } else {
                    QMessageBox::critical(this, "Database Error", "Failed to update the password.");
                }
            }
            delete new_pass; // Clean up the dialog
        }
        delete verify; // Clean up the verification dialog
    } else {
        QMessageBox::warning(this, "Email Not Found", "The email address is not registered.");
    }

    db.closeDatabase(); // Ensure the database is closed after operations
}
