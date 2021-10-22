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

#include "tradeforsizeitem.h"


template <typename T>
class IntermediateItemLayout : public T
{
public:
    IntermediateItemLayout()
        : T()
    { }
    template <typename T1>
    IntermediateItemLayout(T1 a1)
        : T(a1)
    { }
    ~IntermediateItemLayout() override = default;

    using T::addWidget;
    template <typename T1>
    void addWidget(QWidget *widget,
                   TradeForSizeItem *(*newItem)(QLayoutItem *, T1 param),
                   T1 param);

};

template <typename T>
template <typename T1>
void IntermediateItemLayout<T>::addWidget(
        QWidget *widget,
        TradeForSizeItem *(*newItem)(QLayoutItem *, T1 param),
        T1 param)
{
    T::addWidget(widget);
    QLayoutItem *item = T::takeAt(T::count()-1);
    assert(item->widget() == widget);
    TradeForSizeItem *new_item = newItem(item, param);
    T::addItem(new_item);
}


#endif // INTERMEDIATEITEMLAYOUT_H
