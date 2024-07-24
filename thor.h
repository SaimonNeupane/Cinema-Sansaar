#ifndef THOR_H
#define THOR_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Thor;
}

class Thor : public QDialog
{
    Q_OBJECT

public:
    explicit Thor(QWidget *parent = nullptr);
    ~Thor();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Thor *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();

};

#endif // THOR_H
