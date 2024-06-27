#ifndef THOR_H
#define THOR_H

#include <QDialog>

namespace Ui {
class Thor;
}

class Thor : public QDialog
{
    Q_OBJECT

public:
    explicit Thor(QWidget *parent = nullptr);
    ~Thor();

private:
    Ui::Thor *ui;
};

#endif // THOR_H
