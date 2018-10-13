#include <QtDebug>
#include "fixedaspectratioitem.h"

FixedAspectRatioLayout::FixedAspectRatioLayout(QWidget *parent)
    : QLayout(parent)
    , item(nullptr)
{
}

FixedAspectRatioLayout::FixedAspectRatioLayout()
    : QLayout()
    , item(nullptr)

{
}

FixedAspectRatioLayout::~FixedAspectRatioLayout()
{
    delete this->item;
}

void FixedAspectRatioLayout::addItem(QLayoutItem *item)
{
    if (item != nullptr) {
        delete this->item;
        this->item = item;
    }
}

int FixedAspectRatioLayout::count() const
{
    return item != nullptr ? 1 : 0;
}

QLayoutItem *FixedAspectRatioLayout::itemAt(int index) const
{
    return index == 0 ? item : nullptr;
}

QLayoutItem *FixedAspectRatioLayout::takeAt(int index)
{
    QLayoutItem * cached_item = item;
    if (index == 0) {
        item = nullptr;
        return cached_item;
    } else
        return nullptr;
}

void FixedAspectRatioLayout::setGeometry(const QRect &r)
{
    QLayout::setGeometry(r);
    qDebug() << "setGeometry of object" << this << "rect:" << r << "\n";
    if (item != nullptr) {
        int size = std::min(r.height(), r.width());
        QPoint origin = r.topLeft();
        origin += QPoint((r.width()-size)/2, (r.height()-size)/2);
        item->setGeometry(QRect(origin, QSize(size,size)));
    }
}

QSize FixedAspectRatioLayout::sizeHint() const
{
    QSize s = item != nullptr ? item->sizeHint() : QSize();
    qDebug() << "sizeHint - Layout item:" << item << "has size:" << s;
    return s;
}

QSize FixedAspectRatioLayout::minimumSize() const
{
    QSize s = item != nullptr ? item->minimumSize() : QSize();
    qDebug() << "minimumSize - Layout item:" << item << "has size:" << s;
    return s;
}
