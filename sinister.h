#ifndef SINISTER_H
#define SINISTER_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Sinister;
}

class Sinister : public QDialog
{
    Q_OBJECT

public:
    explicit Sinister(QString loggedInUser, QWidget *parent = nullptr); // Update constructor
    ~Sinister();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Sinister *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();
      QString loggedInUser;
};

#endif // SINISTER_H
