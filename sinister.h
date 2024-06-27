#ifndef SINISTER_H
#define SINISTER_H

#include <QDialog>

namespace Ui {
class Sinister;
}

class Sinister : public QDialog
{
    Q_OBJECT

public:
    explicit Sinister(QWidget *parent = nullptr);
    ~Sinister();

private:
    Ui::Sinister *ui;
};

#endif // SINISTER_H
