#include "verification.h"
#include "ui_verification.h"
#include <QMessageBox>

Verification::Verification(const QString &verificationCode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Verification)
{
    ui->setupUi(this);
    connect(ui->verifyCodeButton, &QPushButton::clicked, this, &Verification::on_verifyCodeButton_clicked);
}

Verification::~Verification()
{
    delete ui;
}

void Verification::on_verifyCodeButton_clicked()
{
    QString code = ui->lineEdit->text();
    verifyCode(code);
}

void Verification::verifyCode(const QString &code)
{
    if (code == verificationCode) {
        QMessageBox::information(this, "Verification", "Verification successful!");
        accept();  // Close the dialog and return true

    } else {
        QMessageBox::warning(this, "Verification", "Verification failed. Please try again.");
    }
}
