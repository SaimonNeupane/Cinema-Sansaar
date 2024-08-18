#include "database.h"

Database::Database() {
    QString dbPath = QString(DATABASE_PATH);
    // Check if the connection already exists, otherwise create it
    if (!QSqlDatabase::contains("CinemaSansaarConnection")) {
        db = QSqlDatabase::addDatabase("QSQLITE", "CinemaSansaarConnection");
    } else {
        db = QSqlDatabase::database("CinemaSansaarConnection");
    }
    db.setDatabaseName(dbPath);
}

Database::~Database() {
    closeDatabase();
}

bool Database::openDatabase() {
    if (!db.isOpen() && !db.open()) {
        qDebug() << "Error: connection with database failed" << db.lastError().text();
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

void Database::closeDatabase() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database: connection closed";
    } else {
        qDebug() << "Database: connection nil";
    }
}

//for login
bool Database::authenticateUser(const QString &username, const QString &password) {
    if (!db.isOpen() && !openDatabase()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);
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
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO User (email, username, password) VALUES (:email, :username, :password)");
    query.bindValue(":email", email);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    return query.exec();
}

bool Database::changeUserInfo(const QString &email, const QString &new_password) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("UPDATE User SET password = :password WHERE email = :email");
    query.bindValue(":email", email);
    query.bindValue(":password", new_password);
    return query.exec();
}

