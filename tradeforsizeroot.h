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

#ifndef TRADEFORSIZEROOT_H
#define TRADEFORSIZEROOT_H

#include <QDebug>

#include "intermediateitemlayout.h"


template <typename T>
class TradeForSizeLayout : public IntermediateItemLayout<T>
{
public:
    TradeForSizeLayout()
        : IntermediateItemLayout<T>()
        , dirty(true)
    {}
    template <typename T1>
    TradeForSizeLayout(T1 a1)
        : IntermediateItemLayout<T>(a1)
        , dirty(true)
    {}
    ~TradeForSizeLayout() = default;

    void setGeometry(const QRect& rect) override {
        if (TradeForSizeItem::isTrade) {
            T::invalidate();
            dirty = false;
        }
        T::setGeometry(rect);
    }
    void invalidateGeom() {
        dirty = true;
    }

protected:
    bool dirty; //TOFIX: on need it
};


template <typename T>
class TradeForSizeRoot : public TradeForSizeLayout<T>
{
public:
    TradeForSizeRoot()
        : TradeForSizeLayout<T>()
        , size(QSize())
        , call_i(0)
    {}
    template <typename T1>
    TradeForSizeRoot(T1 a1)
        : TradeForSizeLayout<T>(a1)
        , size(QSize())
        , call_i(0)
    {}
    ~TradeForSizeRoot() = default;

    void setGeometry(const QRect& rect) override;

private:
    QSize size;
    int call_i;
};

template <typename T>
void TradeForSizeRoot<T>::setGeometry(const QRect& rect)
{
    bool diff = rect.size() != size;
    qDebug() << "TradeForSizeRoot::setGeometry. <<--Entry " << call_i
             << "; rect = " << rect << "; size = " << size;

    if (diff) {
        T::invalidate();
        TradeForSizeItem::isTrade = true;
        T::setGeometry(rect);
        TradeForSizeItem::isTrade = false;
        if (TradeForSizeLayout<T>::dirty) {
            T::invalidate();
            qDebug() << "TradeForSizeRoot::setGeometry. Second call setGeometry";
            T::setGeometry(rect);
        }
    } else {
        T::setGeometry(rect);
    }
    size = rect.size();
    TradeForSizeLayout<T>::dirty = false;
    ++call_i;
    qDebug() << "TradeForSizeRoot::setGeometry. -->>Exit; size = " << size;

}


#endif // TRADEFORSIZEROOT_H
