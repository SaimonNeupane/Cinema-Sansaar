#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "sinister.h"
#include "mirzapur.h"
#include "thor.h"
#include "kabir.h"

#include "sanju.h"
#include "mahajatra.h"
#include "harry.h"



namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(const QString &username, QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Dashboard *ui;
    Sinister *sinister;
    Mirzapur *mirzapur;
    Thor *thor;
    Kabir *kabir;
    Sanju *sanju;
    Mahajatra *mahajatra;
    Harry *harry;
    QString loggedInUsername;




};

#endif // DASHBOARD_H
