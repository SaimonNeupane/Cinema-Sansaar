#ifndef KABIR_H
#define KABIR_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Kabir;
}

class Kabir : public QDialog
{
    Q_OBJECT

public:
    explicit Kabir(QString loggedInUser, QWidget *parent = nullptr); // Update constructor
    ~Kabir();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Kabir *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();
      QString loggedInUser;
};

#endif // KABIR_H
