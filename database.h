#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Database {
public:
    Database();
    ~Database();

    bool openDatabase();
    void closeDatabase();
    bool authenticateUser(const QString &username, const QString &password);//login
    bool saveUserInfo(const QString &email, const QString &username, const QString &password);//signup
    bool changeUserInfo(const QString &email, const QString &password);//forgot pass

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
