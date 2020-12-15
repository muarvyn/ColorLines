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

#include "testwidgetitem.h"

class TradeForSizeItem : public QWidgetItem
{
public:
    TradeForSizeItem(QWidget *widget);
    ~TradeForSizeItem() override = default;

    QSize sizeHint() const override;
    //void setGeometry(const QRect &rect) override;
    QSize tradeForSize(const QSize& r);
    bool assignSize(const QSize s);

private:
    QSize assigned;
};

TradeForSizeItem::TradeForSizeItem(QWidget *widget)
    : QWidgetItem(widget)
{
    assigned = wid->sizeHint();
}

QSize TradeForSizeItem::sizeHint() const
{
    return assigned;
}

QSize TradeForSizeItem::tradeForSize(const QSize& s)
{
    QSize trade = s;
    trade.transpose();
    return trade.boundedTo(s);
}

bool TradeForSizeItem::assignSize(const QSize s)
{
    if (assigned == s) return false;
    assigned = s;
    return true;
}

/******** TestWidgetItem ********/

TestWidgetItem::TestWidgetItem(QLayout *l, TradeForSizeItem *item)
    : QLayoutItem()
    , centralItem(item)
    , layout(l)
{

}

void TestWidgetItem::addCentralWidget(QWidget *widget)
{
    if (centralItem) return;
    centralItem = new TradeForSizeItem(widget);
    layout->addItem(centralItem);
}

bool TestWidgetItem::isEmpty() const
{
    return layout->isEmpty();
}

Qt::Orientations TestWidgetItem::expandingDirections() const
{
    return layout->expandingDirections();
}

QSize TestWidgetItem::minimumSize() const
{
    return layout->minimumSize();
}

QSize TestWidgetItem::maximumSize() const
{
    return layout->maximumSize();
}

QSize TestWidgetItem::sizeHint() const
{
    return layout->sizeHint();
}

QRect TestWidgetItem::geometry() const
{
    return layout->geometry();
}

void TestWidgetItem::setGeometry(const QRect& r)
{
    qDebug() << "TestWidgetItem::setGeometry: " << r;
    if (centralItem) {
        QSize trade = centralItem->tradeForSize(r.size());
        if (centralItem->assignSize(trade))
        {
            layout->invalidate();
        }
    }
    layout->setGeometry(r);
}

