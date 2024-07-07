#include "harry.h"
#include "ui_harry.h"
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QLabel>

Harry::Harry(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Harry)
{
    ui->setupUi(this);
    initializeDatabase();
    colorOfTheSeats();
}

Harry::~Harry()
{
    delete ui;
}

void Harry::initializeDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE", "SaimonNeupane");
    db.setDatabaseName("C:/Users/ACER/Desktop/Cinema-Sansaar/Database/Data.db");
    if(db.open()){
        qDebug() << "Database connected successfully.";
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
    }
}

void Harry::colorOfTheSeats(){
    QString sqlQuery = "SELECT m.movie_id, sh.showtime_id, s.seat_id, s.is_available "
                       "FROM Seats s "
                       "JOIN Showtimes sh ON s.showtime_id = sh.showtime_id "
                       "JOIN Movies m ON sh.movie_id = m.movie_id";

    QSqlQuery query(db);  // Associate the query with the open database connection

    qDebug() << "Executing SQL query: " << sqlQuery;  // Log the SQL query

    if (query.exec(sqlQuery)) {
        qDebug() << "SQL query executed successfully.";  // Log query success

        int rowCount = 0;
        while (query.next()) {
            rowCount++;
            int movieId = query.value(0).toInt();             // Retrieve movie_id
            int showtimeId = query.value(1).toInt();          // Retrieve showtime_id
            QString seatNumber = query.value(2).toString();   // Retrieve seat_id
            bool isAvailable = query.value(3).toBool();       // Retrieve is_available

            // Find the corresponding QLabel based on seatNumber
            QString labelObjectName = "lbl" + seatNumber;  // Assuming seat labels are named lblSeat1, lblSeat2, etc.
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

            // Display seat and movie information
            qDebug() << "Row" << rowCount << ":";
            qDebug() << "Movie ID:" << movieId;
            qDebug() << "Showtime ID:" << showtimeId;
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
void Harry::on_btnConfirmBooking1_clicked() {
    // Implementation for button click event
    // Example: qDebug() << "Button clicked!";
}
