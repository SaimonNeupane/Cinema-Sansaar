#include "seatselection.h"
#include "ui_seatselection.h"
#include <QDebug>
#include <QMessageBox>
#include <QLabel>

SeatSelection::SeatSelection(const QString &loggedInUser, int showtimeId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SeatSelection)
    , loggedInUser(loggedInUser)
    , showtimeId(showtimeId)
{
    ui->setupUi(this);
    initialize();
}

SeatSelection::~SeatSelection()
{
    delete ui;
}

void SeatSelection::initialize()
{
    if (!db.openDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to open the database.");
        return;
    }
    colorOfTheSeats();
}

void SeatSelection::colorOfTheSeats() {
    QSqlQuery query = db.executeSeatQuery(showtimeId);
    if (!query.isActive()) {
        return;
    }

    processSeatQueryResults(query);
}

void SeatSelection::updateSeatLabel(const QString &seatNumber, bool isAvailable) {
    const QString labelObjectName = "lbl" + seatNumber;
    QLabel *seatLabel = findChild<QLabel *>(labelObjectName);

    if (seatLabel) {
        db.setSeatColor(seatLabel, isAvailable);
    } else {
        qDebug() << "Label" << labelObjectName << "not found.";
    }
}

void SeatSelection::processSeatQueryResults(QSqlQuery &query) {
    int rowCount = 0;
    while (query.next()) {
        rowCount++;
        const QString seatNumber = query.value(0).toString();
        const bool isAvailable = query.value(1).toBool();

        updateSeatLabel(seatNumber, isAvailable);

        qDebug() << "Row" << rowCount << ":";
        qDebug() << "Seat:" << seatNumber << "Available:" << (isAvailable ? "Yes" : "No");
    }
    if (rowCount == 0) {
        qDebug() << "No seats found for the specified showtime.";
    }
}

void SeatSelection::showConfirmationMessage(const QStringList &bookedSeats, const QList<int> &bookingIds) {
    // Create a message string
    QStringList bookingDetails;
    for (int i = 0; i < bookingIds.size(); ++i) {
        bookingDetails.append(QString("Booking ID %1: Seat %2").arg(bookingIds[i]).arg(bookedSeats[i]));
    }
    QString message = QString("Your booking is confirmed!\n%1\nPlease remember these IDs and take a screenshot.")
                          .arg(bookingDetails.join("\n"));

    // Show the message box
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Booking Confirmation");
    msgBox.setText(message);
    msgBox.setStyleSheet(
        "QLabel{"
        "background:none;"
        "}"
        "QPushButton {"
        "    background-color: #c0c0c0;"
        "    border: 1px solid #a0a0a0;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "    height:15px;"
        "    width:30px;"
        "background:none;"
        "}"
        "QPushButton:hover {"
        "    background-color: #b0b0b0;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #a0a0a0;"
        "}"
        );
    msgBox.exec();
}

void SeatSelection::calculateAndDisplayTotalPrice() {
    int selectedSeatCount = 0;
    QList<QLabel *> allLabels = this->findChildren<QLabel *>(QRegularExpression("lbl\\w+"));

    for (QLabel *label : allLabels) {
        if (label->styleSheet().contains("background-color: gray;")) {
            selectedSeatCount++;
        }
    }

    int seatPrice = 250; // Rs 250 per seat
    int totalPrice = seatPrice * selectedSeatCount;

    ui->lblTotal->setText(QString::number(totalPrice));

    qDebug() << "Total Price: Rs" << totalPrice;
}

void SeatSelection::on_btnConfirmBooking1_clicked() {
    bool seatsSelected = false;
    QStringList bookedSeats;
    QList<int> bookingIds;

    QList<QLabel *> allLabels = this->findChildren<QLabel *>(QRegularExpression("lbl\\w+"));

    for (QLabel *label : allLabels) {
        if (label->styleSheet().contains("background-color: gray;")) {
            QString seatId = label->objectName().mid(3);

            if (db.updateSeatAvailability(seatId, showtimeId)) {
                if (db.insertBooking(loggedInUser, showtimeId, seatId)) {
                    int bookingId = db.retrieveLastBookingId();
                    if (bookingId != -1) {
                        bookedSeats.append(seatId);
                        bookingIds.append(bookingId);
                        seatsSelected = true;
                        label->setStyleSheet("background-color: red;");
                    }
                }
            }
        }
    }

    if (seatsSelected) {
        showConfirmationMessage(bookedSeats, bookingIds);
    } else {
        qDebug() << "No seats selected for booking.";
    }
}
void SeatSelection::on_btnSelectSeat1_clicked() {
    QString selectedSeat = ui->comboBoxSeatSelection->currentText();
    QLabel *selectedSeatLabel = findChild<QLabel *>("lbl" + selectedSeat);

    if (selectedSeatLabel) {
        if (!db.isSeatAvailable(selectedSeat, showtimeId)) {
            QString msg = "The seat is already booked.";
            // Apply custom stylesheet to QMessageBox
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Seat Unavailable");
            msgBox.setText(msg);
            msgBox.setStyleSheet(
                "QLabel{"
                "background:none;"
                "}"
                "QPushButton {"
                "    background-color: #c0c0c0;"
                "    border: 1px solid #a0a0a0;"
                "    border-radius: 5px;"
                "    padding: 10px;"
                "    height:15px;"
                "    width:30px;"
                "background:none;"
                "}"
                "QPushButton:hover {"
                "    background-color: #b0b0b0;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #a0a0a0;"
                "}"
                );
            msgBox.exec();
            return;
        }

        db.updateSeatUI(selectedSeatLabel, showtimeId); // Call with QLabel*
        calculateAndDisplayTotalPrice();
    } else {
        qDebug() << "Selected seat label not found: " << selectedSeat;
    }
}

