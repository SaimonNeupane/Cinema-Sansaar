#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "sinister.h"


namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Dashboard *ui;
    Sinister *sinister;

};

#endif // DASHBOARD_H
