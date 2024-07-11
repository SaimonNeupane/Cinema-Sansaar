#include "seat_selection.h"
#include "ui_seat_selection.h"

Seat_selection::Seat_selection(const QString &movieName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Seat_selection)
{
    ui->setupUi(this);
    setWindowTitle(movieName);
}

Seat_selection::~Seat_selection()
{
    delete ui;
}
