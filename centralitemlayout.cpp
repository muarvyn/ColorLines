/*

Copyright (C) 2020 Volodymyr Kryachko

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
#include <QLayout>
#include <QWidget>

#include "fixedaspectratioitem.h"
#include "centralitemlayout.h"


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
    return item->maximumSize();
}

QRect TradeForSizeItem::geometry() const
{
    return item->geometry();
}

void TradeForSizeItem::setGeometry(const QRect &rect)
{
    qDebug() << "FixedAspectRatioItem::setGeometry of object" << this << "rect:" << rect << "\n";
    QSize size = rect.size().boundedTo(QSize(rect.height(), rect.width()));
    QPoint origin = rect.topLeft();
    origin += QPoint((rect.width()-size.width())/2, (rect.height()-size.height())/2);
    item->setGeometry(QRect(origin, size));
}

QSize TradeForSizeItem::tradeForSize(const QSize& s)
{
    QSize trade = s;
    trade.transpose();
    return trade.boundedTo(s).expandedTo(QSize(80,80));
}

bool TradeForSizeItem::assignSize(const QSize s)
{
    if (assigned == s) return false;
    assigned = s;
    return true;
}

