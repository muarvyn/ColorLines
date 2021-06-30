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

#include "fixedaspectratioitem2.h"


FixedAspectRatioItem::FixedAspectRatioItem(QLayoutItem *i, const QSize hs)
    : TradeForSizeItem(i, hs)
    , scale(0.5)
{
}

QSize FixedAspectRatioItem::minimumSize() const
{
    QSize minsize = item->minimumSize();
    return minsize.expandedTo(QSize(qIntCast(minsize.height()/scale),
                                    qIntCast(minsize.width()*scale)));
}

QSize FixedAspectRatioItem::maximumSize() const
{
    return assigned.boundedTo(item->maximumSize());
}


void FixedAspectRatioItem::setGeometry(const QRect &rect)
{
    QSize size = adjustSize(rect.size());
    QPoint origin = rect.topLeft();
    origin += QPoint((rect.width()-size.width())/2, (rect.height()-size.height())/2);

    qDebug() << "FixedAspectRatioItem::setGeometry final size,origin:" << size << origin ;
    item->setGeometry(QRect(origin, size));
}

QSize FixedAspectRatioItem::tradeForSize(const QSize& s)
{
    QSize trade = s;
    qDebug() << "FixedAspectRatioItem::tradeForSize: suggested size " << s;
    QSize minsize = item->minimumSize();
    trade = trade.expandedTo(QSize(qIntCast(minsize.height()/scale),
                                   qIntCast(minsize.width()*scale)));

    trade = trade.boundedTo(
        QSize(qIntCast(trade.height()/scale), qIntCast(trade.width()*scale)));

    QSize maxsize = item->maximumSize();
    trade = trade.boundedTo(QSize(qIntCast(maxsize.height()/scale),
                                  qIntCast(maxsize.width()*scale)));
    qDebug() << "FixedAspectRatioItem::tradeForSize: final size " << trade;
    return trade; //.boundedTo(QSize(qIntCast(s.height()/scale), qIntCast(s.width()*scale)));
}

