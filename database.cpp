#include "database.h"

Database::Database() {
    QString dbPath = QString(DATABASE_PATH);
    // Check if the connection already exists, otherwise create it
    if (!QSqlDatabase::contains("CinemaSansaarConnection")) {
        dbConnection = QSqlDatabase::addDatabase("QSQLITE", "CinemaSansaarConnection");
    } else {
        dbConnection = QSqlDatabase::database("CinemaSansaarConnection");
    }
    dbConnection.setDatabaseName(dbPath);
}

Database::~Database() {
    closeDatabase();
}

bool Database::openConnection() {
    if (!dbConnection.isOpen()) {
        if (!dbConnection.open()) {
            qDebug() << "Database error:" << dbConnection.lastError().text();
            return false;
        }
    }
    return true;
}

bool Database::closeConnection() {
    if (dbConnection.isOpen()) {
        dbConnection.close();
        qDebug() << "Database: connection closed";
        return true;
    }
    qDebug() << "Database: connection nil";
    return false;
}

bool Database::openDatabase() {
    return openConnection();
}

void Database::closeDatabase() {
    closeConnection();
}

bool Database::doesEmailExist(const QString &email) {
    if (!openDatabase()) {
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("SELECT COUNT(*) FROM User WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Database query error:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    closeDatabase();
    if(count>0){
        return true;
    } else{
        return false;
    }
}

// For login
bool Database::authenticateUser(const QString &username, const QString &password) {
    if (!openDatabase()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("SELECT COUNT(*) FROM User WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Database error: " << query.lastError().text();
        closeDatabase();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    closeDatabase();
    return count > 0;
}

// For signup
bool Database::saveUserInfo(const QString &email, const QString &username, const QString &password) {
    if (!openDatabase()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("INSERT OR REPLACE INTO User (email, username, password) VALUES (:email, :username, :password)");
    query.bindValue(":email", email);
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Database error: " << query.lastError().text();
    }
    closeDatabase();
    return result;
}

bool Database::changeUserInfo(const QString &email, const QString &new_password) {
    if (!openDatabase()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("UPDATE User SET password = :password WHERE email = :email");
    query.bindValue(":email", email);
    query.bindValue(":password", new_password);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Database error: " << query.lastError().text();
    }
    closeDatabase();
    return result;
}

QSqlDatabase Database::getDatabase() const {
    return dbConnection;
}

// SeatSelection
QSqlQuery Database::executeSeatQuery(int showtimeId) {
    QSqlQuery query(dbConnection);
    query.prepare("SELECT seat_id, is_available FROM Seats WHERE showtime_id = :showtimeId");
    query.bindValue(":showtimeId", showtimeId);

    if (!query.exec()) {
        qDebug() << "Error executing seat query:" << query.lastError().text();
    }

    return query;
}

bool Database::updateSeatAvailability(const QString &seatId, int showtimeId) {
    if (!openDatabase()) {
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("UPDATE Seats SET is_available = 0 WHERE seat_id = :seat_id AND showtime_id = :showtime_id");
    query.bindValue(":seat_id", seatId);
    query.bindValue(":showtime_id", showtimeId);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Failed to update seat availability:" << query.lastError().text();
    }
    closeDatabase();
    return result;
}

bool Database::insertBooking(const QString &userId, int showtimeId, const QString &seatId, int &bookingId) {
    if (!openDatabase()) {
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("INSERT INTO Bookings (user_id, showtime_id, seat_id) VALUES (:user_id, :showtime_id, :seat_id)");
    query.bindValue(":user_id", userId);
    query.bindValue(":showtime_id", showtimeId);
    query.bindValue(":seat_id", seatId);

    bool result = query.exec();
    if (result) {
        // Retrieve the last inserted row ID
        bookingId = query.lastInsertId().toInt();
    } else {
        qDebug() << "Failed to insert booking:" << query.lastError().text();
        bookingId = -1; // Indicate failure
    }

    closeDatabase();
    return result;
}


int Database::retrieveLastBookingId() {
    if (openDatabase()) {
        QSqlQuery query(dbConnection);
        query.prepare("SELECT last_insert_rowid()");

        int bookingId = -1;
        if (query.exec() && query.next()) {
            bookingId = query.value(0).toInt();
        } else {
            qDebug() << "Failed to retrieve last booking ID.";
        }
        closeDatabase();
        return bookingId;
    }
    return -1;
}

bool Database::isSeatAvailable(const QString &seatId, int showtimeId) {
    if (!openDatabase()) {
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("SELECT is_available FROM Seats WHERE seat_id = :seat_id AND showtime_id = :showtime_id");
    query.bindValue(":seat_id", seatId);
    query.bindValue(":showtime_id", showtimeId);

    bool isAvailable = false;
    if (query.exec() && query.next()) {
        isAvailable = query.value(0).toBool();
    } else {
        qDebug() << "Failed to check seat availability:" << query.lastError().text();
    }
    closeDatabase();
    return isAvailable;
}

void Database::updateSeatUI(QLabel *seatLabel, int showtimeId) {
    QString seatId = seatLabel->objectName().mid(3);
    bool isAvailable = isSeatAvailable(seatId, showtimeId);

    if (isAvailable) {
        seatLabel->setStyleSheet("background-color: gray;");
    } else {
        seatLabel->setStyleSheet("background-color: red;");
    }
}

void Database::setSeatColor(QLabel *seatLabel, bool isAvailable) {
    seatLabel->setStyleSheet(isAvailable ? "background-color: green;" : "background-color: red;");
}
