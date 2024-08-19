#include "mahajatra.h"
#include "ui_mahajatra.h"
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>

Mahajatra::Mahajatra(QString loggedInUser,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mahajatra)
    , loggedInUser(loggedInUser)
{
    ui->setupUi(this);
    initializeDatabase();
    colorOfTheSeats();
}

Mahajatra::~Mahajatra()
{
    delete ui;
}

void Mahajatra::initializeDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE", "SaimonNeupane");
    db.setDatabaseName("C:/Users/ACER/Desktop/Cinema-Sansaar/Database/Data.db");
    if (db.open()) {
        qDebug() << "Database connected successfully.";
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
    }
}

void Mahajatra::colorOfTheSeats() {
    QString sqlQuery = "SELECT s.seat_id, s.is_available "
                       "FROM Seats s "
                       "WHERE s.showtime_id = 6";

    QSqlQuery query(db);  // Associate the query with the open database connection

    qDebug() << "Executing SQL query: " << sqlQuery;  // Log the SQL query

    if (query.exec(sqlQuery)) {
        qDebug() << "SQL query executed successfully.";  // Log query success

        int rowCount = 0;
        while (query.next()) {
            rowCount++;
            QString seatNumber = query.value(0).toString();   // Retrieve seat_id
            bool isAvailable = query.value(1).toBool();       // Retrieve is_available

            // Find the corresponding QLabel based on seatNumber
            QString labelObjectName = "lbl" + seatNumber;  // Assuming seat labels are named lblA1, lblA2, etc.
            QLabel *seatLabel = findChild<QLabel *>(labelObjectName);

            if (seatLabel) {
                // Set the color based on availability
                if (isAvailable) {
                    seatLabel->setStyleSheet("background-color: green;");
                } else {
                    seatLabel->setStyleSheet("background-color: red;");
                }
            } else {
                qDebug() << "Label" << labelObjectName << "not found.";
            }

            // Display seat information
            qDebug() << "Row" << rowCount << ":";
            qDebug() << "Seat:" << seatNumber << "Available:" << (isAvailable ? "Yes" : "No");
        }
        if (rowCount == 0) {
            qDebug() << "No rows returned.";
        }
    } else {
        // Handle query execution error
        qDebug() << "Error executing SQL query:" << query.lastError().text();
    }
}
void Mahajatra::on_btnConfirmBooking1_clicked() {
    bool seatsSelected = false;
    int showtimeId = 6;
    QStringList bookedSeats;
    QList<int> bookingIds; // To store booking IDs

    QList<QLabel *> allLabels = this->findChildren<QLabel *>(QRegularExpression("lbl\\w+"));

    QSqlQuery updateQuery(db);
    updateQuery.prepare("UPDATE Seats SET is_available = 0 WHERE seat_id = :seat_id AND showtime_id = :showtime_id");

    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO Bookings (user_id, showtime_id, seat_id) "
                        "VALUES (:user_id, :showtime_id, :seat_id)");

    QSqlQuery selectLastIdQuery(db);
    selectLastIdQuery.prepare("SELECT last_insert_rowid()");

    for (QLabel *label : allLabels) {
        if (label->styleSheet().contains("background-color: gray;")) {
            QString seatId = label->objectName().mid(3);

            // Update seat availability
            updateQuery.bindValue(":seat_id", seatId);
            updateQuery.bindValue(":showtime_id", showtimeId);
            if (!updateQuery.exec()) {
                qDebug() << "Failed to update seat availability:" << updateQuery.lastError().text();
            } else {
                label->setStyleSheet("background-color: red;"); // Ensure UI reflects change
                seatsSelected = true;

                // Insert the booking into the Bookings table
                insertQuery.bindValue(":user_id", loggedInUser);
                insertQuery.bindValue(":showtime_id", showtimeId);
                insertQuery.bindValue(":seat_id", seatId);
                if (!insertQuery.exec()) {
                    qDebug() << "Failed to insert booking:" << insertQuery.lastError().text();
                } else {
                    // Retrieve the booking ID
                    if (selectLastIdQuery.exec() && selectLastIdQuery.next()) {
                        int bookingId = selectLastIdQuery.value(0).toInt();
                        bookedSeats.append(seatId);
                        bookingIds.append(bookingId);
                        qDebug() << "Booking inserted for seat:" << seatId << "with Booking ID:" << bookingId;
                    } else {
                        qDebug() << "Failed to retrieve last booking ID.";
                    }
                }
            }
        }
    }

    if (seatsSelected) {
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
    } else {
        qDebug() << "No seats selected for booking.";
    }
}

void Mahajatra::on_btnSelectSeat1_clicked()
{
    // Get selected seat number from combo box
    QString selectedSeat = ui->comboBoxSeatSelection->currentText();
    QLabel *selectedSeatLabel = findChild<QLabel *>("lbl" + selectedSeat);

    if (selectedSeatLabel) {
        qDebug() << "Selected seat label found: " << selectedSeatLabel->objectName();

        // Check if the seat is already booked
        if (selectedSeatLabel->styleSheet().contains("background-color: red;")) {
            QString msg = "The seat is already booked";

            // Create and customize the QMessageBox
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Seat Unavailable");
            msgBox.setText(msg);

            // Apply custom stylesheet to QMessageBox
            msgBox.setStyleSheet(
                "QMessageBox {"
                "    background: transparent;"
                "}"
                "QLabel {"
                "    background: transparent;"
                "}"
                "QPushButton {"
                "    background-color: #c0c0c0;"
                "    border: 1px solid #a0a0a0;"
                "    border-radius: 5px;"
                "    padding: 5px 10px;"
                "    min-width: 80px;"
                "    height:20px;"
                "}"
                "QPushButton:hover {"
                "    background-color: #b0b0b0;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #a0a0a0;"
                "}"
                );

            // Show the message box
            msgBox.exec();

            qDebug() << "Seat already booked: " << selectedSeat;
            return; // Exit the function if the seat is already booked
        }


        // Set the background color to gray to indicate selection
        selectedSeatLabel->setStyleSheet("background-color: gray;");
        qDebug() << "Seat selected: " << selectedSeat << " set to gray.";

        // Calculate the total number of selected seats
        int selectedSeatCount = 0;
        QList<QLabel *> allLabels = this->findChildren<QLabel *>(QRegularExpression("lbl\\w+"));

        for (QLabel *label : allLabels) {
            if (label->styleSheet().contains("background-color: gray;")) {
                selectedSeatCount++;
            }
        }

        // Calculate price (assuming Rs 250 per seat)
        int seatPrice = 250; // Rs 250 per seat
        int totalPrice = seatPrice * selectedSeatCount;

        // Update lblTotal with the total price
        ui->lblTotal->setText(QString::number(totalPrice));

        // Log the selected seat and the total price
        qDebug() << "Selected Seat: " << selectedSeat;
        qDebug() << "Total Price: Rs" << totalPrice;
    } else {
        qDebug() << "Selected seat label not found: " << selectedSeat;
    }
}
