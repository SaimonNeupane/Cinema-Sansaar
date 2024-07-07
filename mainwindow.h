#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<Qtsql>
#include<QSqlDatabase>
#include "homepage.h"
#include "signup.h"
#include<QFrame>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_checkBox_clicked(bool checked);

    void on_Login_clicked();

    void on_Signup_clicked();

private:
    Ui::MainWindow *ui;
    homepage *Homepage;
    Signup *signup;

    //resize functions;
    void resizeEvent(QResizeEvent *event);
    void centerFrame();
    QFrame *frame;
};
#endif // MAINWINDOW_H
