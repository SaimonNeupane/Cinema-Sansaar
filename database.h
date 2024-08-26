#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QLabel>

class Database {
public:
    Database();
    ~Database();
    bool testConnection();
    bool closeConnection();
    bool openDatabase();
    void closeDatabase();
    bool authenticateUser(const QString &username, const QString &password);//login
    bool saveUserInfo(const QString &email, const QString &username, const QString &password);//signup
    bool changeUserInfo(const QString &email, const QString &password);//forgot pass
    QSqlDatabase getDatabase() const;
    bool doesEmailExist(const QString &email);//email duplication check

    //Seat Selection
    QSqlQuery executeSeatQuery(int showtimeId);
    bool updateSeatAvailability(const QString &seatId, int showtimeId);
    bool insertBooking(const QString &userId, int showtimeId, const QString &seatId, int &bookingId);
    int retrieveLastBookingId();

    bool isSeatAvailable(const QString &seatId, int showtimeId);
    void updateSeatUI(QLabel *seatLabel, int showtimeId);
    void setSeatColor(QLabel *seatLabel, bool isAvailable);
private:
    QSqlDatabase dbConnection;
    int showtimeId;
};

#endif // DATABASE_H
