#ifndef MIRZAPUR_H
#define MIRZAPUR_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Mirzapur;
}

class Mirzapur : public QDialog
{
    Q_OBJECT

public:
    explicit Mirzapur(QString loggedInUser, QWidget *parent = nullptr); // Update constructor
    ~Mirzapur();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Mirzapur *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();
      QString loggedInUser;
};

#endif // MIRZAPUR_H
