#include "kabir.h"
#include "ui_kabir.h"
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>

Kabir::Kabir(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Kabir)
{
    ui->setupUi(this);
    initializeDatabase();
    colorOfTheSeats();
}

Kabir::~Kabir()
{
    delete ui;
}

void Kabir::initializeDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE", "SaimonNeupane");
    db.setDatabaseName("C:/Users/ACER/Desktop/Cinema-Sansaar/Database/Data.db");
    if (db.open()) {
        qDebug() << "Database connected successfully.";
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
    }
}

void Kabir::colorOfTheSeats() {
    QString sqlQuery = "SELECT s.seat_id, s.is_available "
                       "FROM Seats s "
                       "WHERE s.showtime_id = 3";

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

void Kabir::on_btnConfirmBooking1_clicked() {
    bool seatsSelected = false; // Flag to check if any seat is selected

    // Iterate through all seat labels to check which ones are selected for booking
    QList<QLabel *> allLabels = this->findChildren<QLabel *>(QRegularExpression("lbl\\w+"));

    QSqlQuery query(db);
    query.prepare("UPDATE Seats SET is_available = 0 WHERE seat_id = :seat_id AND showtime_id = 2");

    for (QLabel *label : allLabels) {
        if (label->styleSheet().contains("background-color: gray;")) {
            label->setStyleSheet("background-color: red;");
            seatsSelected = true; // Set flag to true if at least one seat is selected
            query.bindValue(":seat_id", label->objectName().mid(3)); // Remove 'lbl' prefix to get the seat number
            if (!query.exec()) {
                qDebug() << "Failed to update seat availability:" << query.lastError().text();
            }
        }
    }

    if (seatsSelected) {
        qDebug() << "Seats booked successfully!";
        // Optionally, you can update your database or perform other actions here
    } else {
        qDebug() << "No seats selected for booking.";
        // Optionally, show a message or handle the case where no seats are selected
    }
}
void Kabir::on_btnSelectSeat1_clicked()
{
    // Get selected seat number from combo box
    QString selectedSeat = ui->comboBoxSeatSelection->currentText();
    QLabel *selectedSeatLabel = findChild<QLabel *>("lbl" + selectedSeat);

    if (selectedSeatLabel) {
        qDebug() << "Selected seat label found: " << selectedSeatLabel->objectName();

        // Check if the seat is already booked
        if (selectedSeatLabel->styleSheet().contains("background-color: red;")) {
            QMessageBox::information(this, "Seat Unavailable", "The selected seat is already booked.");
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
