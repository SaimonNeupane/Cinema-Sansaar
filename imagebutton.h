#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>
#include <QPixmap>

class ImageButton : public QPushButton {
    Q_OBJECT

public:
    explicit ImageButton(const QString &imagePath, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap m_pixmap;
};

#endif // IMAGEBUTTON_H
