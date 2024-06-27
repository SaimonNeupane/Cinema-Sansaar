#ifndef SANJU_H
#define SANJU_H

#include <QDialog>

namespace Ui {
class Sanju;
}

class Sanju : public QDialog
{
    Q_OBJECT

public:
    explicit Sanju(QWidget *parent = nullptr);
    ~Sanju();

private:
    Ui::Sanju *ui;
};

#endif // SANJU_H
