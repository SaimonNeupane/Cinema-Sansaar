#include "imagebutton.h"
#include <QDebug>
#include <QResizeEvent>

ImageButton::ImageButton(const QString &imagePath, QWidget *parent)
    : QPushButton(parent), m_pixmap(imagePath) {
    if (m_pixmap.isNull()) {
        qDebug() << "Failed to load image:" << imagePath;
    } else {
        setIcon(QIcon(m_pixmap));
        setIconSize(size());
        // setStyleSheet("QPushButton { border: none; }"); // Remove border
    }
}

void ImageButton::resizeEvent(QResizeEvent *event) {
    QPushButton::resizeEvent(event);
    setIconSize(size()); // Update the icon size to match the button size
}
