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

#ifndef ASPECTRATIOITEM_H
#define ASPECTRATIOITEM_H

#include "tradeforsizeitem.h"


class AspectRatioItem : public TradeForSizeItem
{
public:
    AspectRatioItem(QLayoutItem *i, TradeForSizeItem::InvalidateFunc,
                    float r=1.0f, const QSize hs = QSize());

    QSize minimumSize() const override;
    QSize maximumSize() const override;
    bool assignSize(const QSize s) override;

private:
    /** height = width * ratio **/
    double ratio;
    inline QSize adjustSize(QSize size) const {
        return size.boundedTo(QSize(qIntCast(size.height()/ratio), qIntCast(size.width()*ratio)));
    }
};

#endif // ASPECTRATIOITEM_H
