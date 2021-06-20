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

#include "tradeforsizeitem.h"


TradeForSizeItem::TradeForSizeItem(QLayoutItem *i, const QSize hs)
    : item(i)
    , assigned(hs)
{
}

QSize TradeForSizeItem::sizeHint() const
{
    qDebug() << "TradeForSizeItem::sizeHint: " << assigned;
    return assigned;
}

bool TradeForSizeItem::isEmpty() const
{
    return item->isEmpty();
}

Qt::Orientations TradeForSizeItem::expandingDirections() const
{
    return item->expandingDirections();
}

QSize TradeForSizeItem::minimumSize() const
{
    return item->minimumSize();
}

QSize TradeForSizeItem::maximumSize() const
{
    qDebug() << "TradeForSizeItem::maximumSize:" << item->maximumSize();
    return item->maximumSize();
}

QRect TradeForSizeItem::geometry() const
{
    return item->geometry();
}

void TradeForSizeItem::setGeometry(const QRect &rect)
{
    qDebug() << "TradeForSizeItem::setGeometry of object" << this << "rect:" << rect;
    QSize size = assigned;
    QPoint origin = rect.topLeft();
    QPoint disp = QPoint(qMax(rect.width()-size.width(),0)/2, qMax(rect.height()-size.height(),0)/2);
    qDebug() << "Origin displacement:" << disp;
    origin += disp;
    item->setGeometry(QRect(origin, size.boundedTo(rect.size())));
}

QSize TradeForSizeItem::tradeForSize(const QSize& s)
{
    QSize trade = s;
    return trade.boundedTo(item->maximumSize());
}

bool TradeForSizeItem::assignSize(const QSize s)
{
    if (assigned == s) return false;
    QSize hint = s.boundedTo(item->maximumSize());
    if (assigned == hint) return false;
    assigned = hint;
    return true;
}

