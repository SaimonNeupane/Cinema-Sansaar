#include "mainwindow.h"

#include <QApplication>
#include"./Database/sqlite3.h"
#include <QObject>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
