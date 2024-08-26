#include "verification.h"
#include "ui_verification.h"
#include <QMessageBox>
#include <QDebug>

Verification::Verification(const QString &verificationCode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Verification)
    , verificationCode(verificationCode)
{
    ui->setupUi(this);
    connect(ui->verifyCodeButton, &QPushButton::clicked, this, &Verification::on_verifyCodeButton_clicked);
    qDebug()<<"code:" <<verificationCode;
}

Verification::~Verification()
{
    delete ui;
}

bool Verification::on_verifyCodeButton_clicked()
{
    QString code = ui->lineEdit->text();
    if (code == verificationCode) {
        QMessageBox::information(this, "Verification", "Verification successful!");
        qDebug()<<"verification true";
        accept();
        // return true;  // Close the dialog and return true
    } else{
        QMessageBox::warning(this, "Verification", "Verification failed. Please try again.");
        qDebug()<<"verification false";
        return false;
    }
}
