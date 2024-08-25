#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include"./Database/sqlite3.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Database *db= new Database;
    if (db->testConnection()) {
        delete db;
        w.show();
        return a.exec();
    } else {
        delete db;
        // Handle the error appropriately
        qCritical() << "Failed to open database. Application will exit.";
        return -1;  // Exit the application with an error code
    }
    // w.showMaximized();
    // return a.exec();
}
