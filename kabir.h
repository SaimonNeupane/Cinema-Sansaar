#ifndef KABIR_H
#define KABIR_H

#include <QDialog>

namespace Ui {
class Kabir;
}

class Kabir : public QDialog
{
    Q_OBJECT

public:
    explicit Kabir(QWidget *parent = nullptr);
    ~Kabir();

private:
    Ui::Kabir *ui;
};

#endif // KABIR_H
