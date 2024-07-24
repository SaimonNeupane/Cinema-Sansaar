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
    explicit Sinister(QWidget *parent = nullptr);
    ~Sinister();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Sinister *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();

};

#endif // SINISTER_H
