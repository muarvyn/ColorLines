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

#include <QDebug>

#include "aspectratioitem.h"


AspectRatioItem::AspectRatioItem(QLayoutItem *i,
                                 TradeForSizeItem::InvalidateFunc invalidate_func,
                                 float r,
                                 const QSize hs)
    : TradeForSizeItem(i, invalidate_func, hs)
    , ratio(r)
{
}

QSize AspectRatioItem::minimumSize() const
{
    QSize minsize = item->minimumSize();
    return minsize.expandedTo(QSize(qIntCast(minsize.height()/ratio),
                                    qIntCast(minsize.width()*ratio)));
}

QSize AspectRatioItem::maximumSize() const
{
    QSize maxsize = item->maximumSize();
    return maxsize.boundedTo(QSize(qIntCast(maxsize.height()/ratio),
                                  qIntCast(maxsize.width()*ratio)));
}
/*
void AspectRatioItem::setGeometry(const QRect &rect)
{
    QSize size = adjustSize(rect.size());
    QPoint origin = rect.topLeft();
    origin += QPoint((rect.width()-size.width())/2, (rect.height()-size.height())/2);

    qDebug() << "AspectRatioItem::setGeometry final size,origin:" << size << origin ;
    item->setGeometry(QRect(origin, size));
}
*/
bool AspectRatioItem::assignSize(const QSize s)
{
    if (assigned == s) return false;
    QSize hint = s.boundedTo(item->maximumSize());
    if (assigned == hint) return false;
    assigned = adjustSize(hint);
    return true;
}
