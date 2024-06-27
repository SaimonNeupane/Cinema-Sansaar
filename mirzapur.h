#ifndef MIRZAPUR_H
#define MIRZAPUR_H

#include <QDialog>

namespace Ui {
class Mirzapur;
}

class Mirzapur : public QDialog
{
    Q_OBJECT

public:
    explicit Mirzapur(QWidget *parent = nullptr);
    ~Mirzapur();

private:
    Ui::Mirzapur *ui;
};

#endif // MIRZAPUR_H
