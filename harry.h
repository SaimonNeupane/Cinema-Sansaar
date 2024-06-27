#ifndef HARRY_H
#define HARRY_H

#include <QDialog>

namespace Ui {
class Harry;
}

class Harry : public QDialog
{
    Q_OBJECT

public:
    explicit Harry(QWidget *parent = nullptr);
    ~Harry();

private:
    Ui::Harry *ui;
};

#endif // HARRY_H
