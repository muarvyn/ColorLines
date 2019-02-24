/*

Copyright (C) 2018 Volodymyr Kryachko

This file is part of ColorLines.

ColorLines is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

ColorLines is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with ColorLines; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

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

void FixedAspectRatioLayout::addItem(QLayoutItem *layout_item)
{
    if (this->item != nullptr) {
        delete this->item;
    }
    this->item = layout_item;
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
