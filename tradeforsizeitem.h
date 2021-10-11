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

#ifndef TRADEFORSIZEITEM_H
#define TRADEFORSIZEITEM_H

#include <QLayoutItem>
#include <functional>

class TradeForSizeItem : public QLayoutItem
{
public:
    typedef std::function<void(void)> InvalidateFunc;

    TradeForSizeItem(QLayoutItem *i,
                     InvalidateFunc f,
                     const QSize hs = QSize());
    ~TradeForSizeItem() override = default;

    QSize sizeHint() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    Qt::Orientations expandingDirections() const override;
    bool isEmpty() const override;
    void setGeometry(const QRect&) override;
    QRect geometry() const override;

    // TODO: remove obsoleted methods
    virtual QSize tradeForSize(const QSize& r);
    virtual bool assignSize(const QSize s);

protected:
    QLayoutItem *item;
    QSize assigned;
    InvalidateFunc invalidate_func;
};

#endif // TRADEFORSIZEITEM_H
