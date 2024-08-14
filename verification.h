#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QDialog>
#include <QString>

namespace Ui {
class Verification;
}

class Verification : public QDialog
{
    Q_OBJECT

public:
    explicit Verification(const QString &verificationCode, QWidget *parent = nullptr);
    ~Verification();

private slots:
    void on_verifyCodeButton_clicked();

private:
    Ui::Verification *ui;
    QString verificationCode;
    void verifyCode(const QString &code);

};

#endif // VERIFICATION_H
