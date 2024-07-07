#include "sanju.h"
#include "ui_sanju.h"
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QCheckBox>

// Custom delegate class for QComboBox items
class CheckBoxDelegate : public QItemDelegate
{
public:
    CheckBoxDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {}

    // Corrected paint function without extra qualification
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyleOptionViewItem opt = option;

        const QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
        style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

        // Draw checkbox next to item text
        QRect checkboxRect = style->subElementRect(QStyle::SE_ItemViewItemCheckIndicator, &opt);
        checkboxRect.moveTopLeft(QPoint(opt.rect.left() + 5, opt.rect.center().y() - checkboxRect.height() / 2));

        QCheckBox checkbox;
        checkbox.setChecked(true); // Adjust as needed
        checkbox.render(painter, checkboxRect.topLeft());
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QSize size = QItemDelegate::sizeHint(option, index);
        size.setWidth(size.width() + 20); // Adjust width to accommodate checkbox
        return size;
    }
};

Sanju::Sanju(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sanju)
{
    ui->setupUi(this);

    // Set custom delegate to the comboBox
    ui->comboBox->setItemDelegate(new CheckBoxDelegate(ui->comboBox));

    // Populate the comboBox with items A1 to I10 (excluding specific combinations)
    for (char c = 'A'; c <= 'I'; c++) {
        for (int i = 1; i <= 10; i++) {
            if (!((c == 'C' && (i == 9 || i == 10)) || (c == 'I' && (i == 1 || i == 2 || i == 9 || i == 10)))) {
                QString item = QString("%1%2").arg(c).arg(i);
                ui->comboBox->addItem(item);
            }
        }
    }
}

Sanju::~Sanju()
{
    delete ui;
}
