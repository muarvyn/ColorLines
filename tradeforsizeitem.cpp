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

#include <QWidget>
#include <QDebug>

#include "tradeforsizeitem.h"

bool TradeForSizeItem::isTrade = true;

TradeForSizeItem::TradeForSizeItem(QLayoutItem *i,
                                   InvalidateFunc invalidate_func,
                                   const QSize hs)
    : item(i)
    , assigned(hs)
    , invalidate_func(invalidate_func)
{
}

QSize TradeForSizeItem::sizeHint() const
{
    QString name;
    if (item->widget()) {
        name = item->widget()->objectName();
    } else {
        QObject *obj = dynamic_cast<QObject*>(item);
        if (obj) name = obj->objectName();
    }
    if (!name.isEmpty())
        qDebug() << "TradeForSizeItem::sizeHint - " << name << " :isTrade = " << isTrade;
    if (isTrade) return maximumSize();
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
    QString name;
    if (item->widget()) {
        name = item->widget()->objectName();
    } else {
        QObject *obj = dynamic_cast<QObject*>(item);
        if (obj) name = obj->objectName();
    }
    bool dbg = !name.isEmpty();

    if (dbg) qDebug() << name << "::setGeometry: rect=" << rect;

    QSize size = assigned;
    QPoint origin = rect.topLeft();
    QPoint disp = QPoint(qMax(rect.width()-size.width(),0)/2, qMax(rect.height()-size.height(),0)/2);

    origin += disp;
    if (assignSize(rect.size()) || isTrade) {
        if (dbg) qDebug() << name << ": invalidate.";
        if (item->widget()) item->widget()->updateGeometry();
    } else {
        if (invalidate_func) {
            invalidate_func();
        }
        if (dbg) qDebug()  << name << ": trade is ON.";
    }
    QRect r(origin, size.boundedTo(rect.size()));
    if (dbg) qDebug()  << name << ": item rect=" << r;
    item->setGeometry(r);
}

bool TradeForSizeItem::assignSize(const QSize s)
{
    if (assigned == s) return false;
    QSize hint = s.boundedTo(maximumSize());
    if (assigned == hint) return false;
    assigned = hint;
    return true;
}

