#include "change_pass.h"
#include "ui_change_pass.h"

Change_pass::Change_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_pass),
    errorTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Connect the confirm button to the slot
    connect(ui->confirmButton, &QPushButton::clicked, this, &Change_pass::on_confirmButton_clicked);
    connect(errorTimer, &QTimer::timeout, this, &Change_pass::showEmptyPasswordError);

    // Set the timeout interval for placeholder text to revert
    errorTimer->setInterval(2000); // 2 seconds
}

Change_pass::~Change_pass()
{
    delete ui;
}

QString Change_pass::getNewPassword() const
{
    return newPassword;
}

void Change_pass::on_confirmButton_clicked()
{
    newPassword = ui->lineEdit->text();

    if (newPassword.isEmpty()) {
        // Set the placeholder text to show the error message
        ui->lineEdit->setPlaceholderText("Password cannot be empty");

        // Start the timer to revert the placeholder text
        errorTimer->start();

        return;
    }else{
        accept();
    }
}

void Change_pass::showEmptyPasswordError()
{
    // Revert the placeholder text
    ui->lineEdit->setPlaceholderText("Enter new password");

    // Stop the timer
    errorTimer->stop();
}
