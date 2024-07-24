#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QSqlDatabase>

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_sendVerificationCodeButton_clicked();
    void on_verifyCodeButton_clicked();

private:
    Ui::Signup *ui;
    QNetworkAccessManager *networkManager;
    QString apiKey;
    QString mailgunDomain;
    QSqlDatabase database;
    QString verificationCode;

    void sendVerificationCode(const QString &email);
    void verifyCode(const QString &code);
    void saveInfo(const QString &email, const QString &username, const QString &password);
};

#endif // SIGNUP_H
