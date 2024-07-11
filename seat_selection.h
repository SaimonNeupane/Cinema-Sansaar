#ifndef SEAT_SELECTION_H
#define SEAT_SELECTION_H

#include <QDialog>

namespace Ui {
class Seat_selection;
}

class Seat_selection : public QDialog
{
    Q_OBJECT

public:
    explicit Seat_selection(const QString &movieName, QWidget *parent = nullptr);
    ~Seat_selection();

private:
    Ui::Seat_selection *ui;
};

#endif // SEAT_SELECTION_H
