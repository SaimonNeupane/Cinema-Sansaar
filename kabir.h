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
    explicit Kabir(QWidget *parent = nullptr);
    ~Kabir();

private slots:
    void on_btnConfirmBooking1_clicked();

    void on_btnSelectSeat1_clicked();

private:
    Ui::Kabir *ui;
    QSqlDatabase db;
    void initializeDatabase();
    void colorOfTheSeats();

};

#endif // KABIR_H
