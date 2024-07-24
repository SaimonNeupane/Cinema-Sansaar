#ifndef SANJU_H
#define SANJU_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Sanju;
}

class Sanju : public QDialog
{
    Q_OBJECT

public:
    explicit Sanju(QWidget *parent = nullptr);
    ~Sanju();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Sanju *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();

};

#endif // SANJU_H
