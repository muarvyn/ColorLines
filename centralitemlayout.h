/*

Copyright (C) 2020-2021 Volodymyr Kryachko

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

#ifndef CENTRALITEMLAYOUT_H
#define CENTRALITEMLAYOUT_H

#include <QDebug>

#include "tradeforsizeitem.h"

template <typename T>
class CentralItemLayout : public T
{
public:
    CentralItemLayout() : T(), centralItem(nullptr) { }
    ~CentralItemLayout() override = default;

    void setGeometry(const QRect&) override;
    void addCentralWidget(QWidget *widget, TradeForSizeItem *(*newItem)(QLayoutItem *));
    void addCentralLayout(QLayout *layout);

protected:
    TradeForSizeItem *centralItem;
};

template <typename T>
void CentralItemLayout<T>::addCentralWidget(QWidget *widget, TradeForSizeItem *(*newItem)(QLayoutItem *))
{
    if (centralItem) return;

    T::addWidget(widget);
    QLayoutItem *item = T::takeAt(T::count()-1);
    assert(item->widget() == widget);
    centralItem = newItem(item);
    T::addItem(centralItem);
}
/*
template <typename T>
void CentralItemLayout<T>::addCentralLayout(QLayout *layout)
{
    if (centralItem) {
        qWarning() << "CentralItemLayout::addCentralLayout: centralItem is already set.";
        return;
    }
    centralItem = new TradeForSizeItem(layout);
    T::addItem(centralItem);
}
*/
template <typename T>
void CentralItemLayout<T>::setGeometry(const QRect& rect)
{
    qDebug() << "CentralItemLayout::setGeometry: " << rect;
    if (centralItem) {
        QSize trade = centralItem->tradeForSize(rect.size());
        if (centralItem->assignSize(trade))
        {
            qDebug() << "CentralItemLayout::setGeometry - Central Item size:" << trade;
            T::invalidate();
        }
    }
    T::setGeometry(rect);
}


#endif // CENTRALITEMLAYOUT_H
