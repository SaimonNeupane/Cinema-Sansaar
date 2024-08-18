#ifndef CHANGE_PASS_H
#define CHANGE_PASS_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Change_pass;
}

class Change_pass : public QDialog
{
    Q_OBJECT

public:
    explicit Change_pass(QWidget *parent = nullptr);
    ~Change_pass();

    QString getNewPassword() const;

private slots:
    void on_confirmButton_clicked();
    void showEmptyPasswordError(); // Slot to show the error message

private:
    Ui::Change_pass *ui;
    QString newPassword;
    QTimer *errorTimer; // Timer to handle placeholder text reverting
};

#endif // CHANGE_PASS_H
