#ifndef HARRY_H
#define HARRY_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Harry;
}

class Harry : public QDialog
{
    Q_OBJECT

public:
    explicit Harry(QWidget *parent = nullptr);
    ~Harry();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Harry *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();

};

#endif // HARRY_H
