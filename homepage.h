#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>
#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include "imagebutton.h"
#include <QSqlDatabase>

namespace Ui {
class homepage;
}

class homepage : public QDialog
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = nullptr);
    ~homepage();
private:
    Ui::homepage *ui;
    QFrame *frame;
    QPushButton *firstButton, *secondButton;
    QSqlDatabase db;  // Database connection
    //widgets
    void setupFirstWidgetLayout();
    //database
    bool connectToDatabase();
    void closeDatabase();
    //resize functions;
    void resizeEvent(QResizeEvent *event);
    void centerFrame();
};

#endif // HOMEPAGE_H
