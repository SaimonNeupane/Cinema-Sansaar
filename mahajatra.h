#ifndef MAHAJATRA_H
#define MAHAJATRA_H

#include <QDialog>

namespace Ui {
class Mahajatra;
}

class Mahajatra : public QDialog
{
    Q_OBJECT

public:
    explicit Mahajatra(QWidget *parent = nullptr);
    ~Mahajatra();

private:
    Ui::Mahajatra *ui;
};

#endif // MAHAJATRA_H
