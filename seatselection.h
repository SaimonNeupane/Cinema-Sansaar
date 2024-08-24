#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include <QDialog>
#include <QSqlQuery>
#include "database.h"
#include <QLabel>

namespace Ui {
class SeatSelection;
}

class SeatSelection : public QDialog
{
    Q_OBJECT

public:
    explicit SeatSelection(const QString &loggedInUser, int showtimeId, QWidget *parent = nullptr);
    ~SeatSelection();

private:
    Ui::SeatSelection *ui;
    QString loggedInUser;
    Database db;
    int showtimeId;  // Variable for movie showtime ID

    void initialize();
    void colorOfTheSeats();
    void updateSeatLabel(const QString &seatNumber, bool isAvailable);
    void processSeatQueryResults(QSqlQuery &query);
    void showConfirmationMessage(const QStringList &bookedSeats, const QList<int> &bookingIds);
    void calculateAndDisplayTotalPrice();

private slots:
    void on_btnConfirmBooking1_clicked();
    void on_btnSelectSeat1_clicked();
};

#endif // SEATSELECTION_H
