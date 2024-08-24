#ifndef SANJU_H
#define SANJU_H

#include <QDialog>
#include <QSqlDatabase>
#include "database.h"
namespace Ui {
class Sanju;
}

class Sanju : public QDialog
{
    Q_OBJECT

public:
    explicit Sanju(QString loggedInUser, QWidget *parent = nullptr); // Update constructor
    ~Sanju();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Sanju *ui;
    QString loggedInUser;
    Database db;

    void initialize();
    QSqlQuery executeSeatQuery(int showtimeId);
    void updateSeatLabel(const QString &seatNumber, bool isAvailable);
    void processSeatQueryResults(QSqlQuery &query);
    void colorOfTheSeats();
};

#endif // SANJU_H
