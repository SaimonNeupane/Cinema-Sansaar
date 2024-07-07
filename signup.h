#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSqlDatabase>
#include <QSqlQuery>

#include<QFrame>

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
   void sendVerificationCode(const QString &email);
   void verifyCode(const QString &email, const QString &code);
   void saveVerificationCode(const QString &email, const QString &code);

   //resize functions;
   void resizeEvent(QResizeEvent *event);
   void centerFrame();
   QFrame *frame;
};




#endif // SIGNUP_H
