/*

Copyright (C) 2021 Volodymyr Kryachko

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

#ifndef INTERMEDIATEITEMLAYOUT_H
#define INTERMEDIATEITEMLAYOUT_H

#include <QBoxLayout>
#include <QDebug>

#include "tradeforsizeitem.h"


template <typename T>
class IntermediateItemLayout : public T
{
public:
    IntermediateItemLayout() : T(), dirty(false) { }
    ~IntermediateItemLayout() override = default;

    void setGeometry(const QRect&) override;
    void addWidget(QWidget *widget,
                   TradeForSizeItem *(*newItem)(QLayoutItem *,
                                                TradeForSizeItem::InvalidateFunc));
    void invalidateGeom() { dirty = true; };

private:
    bool dirty;

};

template <typename T>
void IntermediateItemLayout<T>::addWidget(
        QWidget *widget,
        TradeForSizeItem *(*newItem)(QLayoutItem *, TradeForSizeItem::InvalidateFunc))
{
    T::addWidget(widget);
    QLayoutItem *item = T::takeAt(T::count()-1);
    assert(item->widget() == widget);
    TradeForSizeItem *new_item = newItem(item, [this](void){ this->invalidateGeom(); });
    T::addItem(new_item);
}

template <typename T>
void IntermediateItemLayout<T>::setGeometry(const QRect& rect)
{
    if (dirty) {
        T::invalidate();
        // TODO: protect from infinite loop
        dirty = false;
        qDebug() << "IntermediateItemLayout::setGeometry: invalidated";
    }
    T::setGeometry(rect);
}

template <>
IntermediateItemLayout<QBoxLayout>::IntermediateItemLayout()
    : QBoxLayout(QBoxLayout::LeftToRight)
{
}

#endif // INTERMEDIATEITEMLAYOUT_H
