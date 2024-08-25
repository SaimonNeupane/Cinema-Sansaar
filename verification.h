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
    bool on_verifyCodeButton_clicked();

private:
    Ui::Verification *ui;
    QString verificationCode;
};

#endif // VERIFICATION_H
