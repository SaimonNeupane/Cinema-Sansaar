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

bool Database::openDatabase() {
    if (!dbConnection.isOpen() && !dbConnection.open()) {
        qDebug() << "Error: connection with database failed" << dbConnection.lastError().text();
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

void Database::closeDatabase() {
    if (dbConnection.isOpen()) {
        dbConnection.close();
        qDebug() << "Database: connection closed";
    } else {
        qDebug() << "Database: connection nil";
    }
}

//for login
bool Database::authenticateUser(const QString &username, const QString &password) {
    if (!dbConnection.isOpen() && !openDatabase()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(dbConnection);
    query.prepare("SELECT * FROM User WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Database error: " << query.lastError().text();
        closeDatabase();
        return false;
    }

    if (query.next()) {
        qDebug() << "Login Successful";
        closeDatabase();
        return true;
    } else {
        qDebug() << "No user exists with those credentials";
        closeDatabase();
        return false;
    }
}

//for signup
bool Database::saveUserInfo(const QString &email, const QString &username, const QString &password) {
    if (!dbConnection.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }
    QSqlQuery query(dbConnection);
    query.prepare("INSERT OR REPLACE INTO User (email, username, password) VALUES (:email, :username, :password)");
    query.bindValue(":email", email);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    return query.exec();
}

bool Database::changeUserInfo(const QString &email, const QString &new_password) {
    if (!dbConnection.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }
    QSqlQuery query(dbConnection);
    query.prepare("UPDATE User SET password = :password WHERE email = :email");
    query.bindValue(":email", email);
    query.bindValue(":password", new_password);
    return query.exec();
}

QSqlDatabase Database::getDatabase() const {
    return dbConnection;
}


//SeatSelection
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
    QSqlQuery query(dbConnection);
    query.prepare("UPDATE Seats SET is_available = 0 WHERE seat_id = :seat_id AND showtime_id = :showtime_id");
    query.bindValue(":seat_id", seatId);
    query.bindValue(":showtime_id", showtimeId);

    if (!query.exec()) {
        qDebug() << "Failed to update seat availability:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::insertBooking(const QString &userId, int showtimeId, const QString &seatId) {
    QSqlQuery query(dbConnection);
    query.prepare("INSERT INTO Bookings (user_id, showtime_id, seat_id) VALUES (:user_id, :showtime_id, :seat_id)");
    query.bindValue(":user_id", userId);
    query.bindValue(":showtime_id", showtimeId);
    query.bindValue(":seat_id", seatId);

    if (!query.exec()) {
        qDebug() << "Failed to insert booking:" << query.lastError().text();
        return false;
    }
    return true;
}

int Database::retrieveLastBookingId() {
    QSqlQuery query(dbConnection);
    query.prepare("SELECT last_insert_rowid()");

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Failed to retrieve last booking ID.";
        return -1;
    }
}

bool Database::isSeatAvailable(const QString &seatId, int showtimeId) {
    QSqlQuery query(dbConnection);
    query.prepare("SELECT is_available FROM Seats WHERE seat_id = :seat_id AND showtime_id = :showtime_id");
    query.bindValue(":seat_id", seatId);
    query.bindValue(":showtime_id", showtimeId);

    if (query.exec() && query.next()) {
        return query.value(0).toBool();
    } else {
        qDebug() << "Failed to check seat availability:" << query.lastError().text();
        return false;
    }
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
