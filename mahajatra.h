#ifndef MAHAJATRA_H
#define MAHAJATRA_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Mahajatra;
}

class Mahajatra : public QDialog
{
    Q_OBJECT

public:
    explicit Mahajatra(QString loggedInUser, QWidget *parent = nullptr); // Update constructor
    ~Mahajatra();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Mahajatra *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();
      QString loggedInUser;
};

#endif // MAHAJATRA_H
